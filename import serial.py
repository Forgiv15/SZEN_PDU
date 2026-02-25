import serial
import threading
import queue
import tkinter as tk
from tkinter import ttk
from tkinter import simpledialog
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from serial.tools import list_ports
from collections import deque
import time

# ================= CONFIG =================

SERIAL_PORT = "COM8"
BAUD_RATE = 921600

EFUSE_COUNT = 8
HISTORY_SECONDS = 5
UPDATE_RATE_HZ = 20
HISTORY_LENGTH = HISTORY_SECONDS * UPDATE_RATE_HZ
WATERFALL_MAX_LINES = 500

CAN_ID_EFUSE_BASE = 0x500
CAN_ID_EFUSE_LAST = CAN_ID_EFUSE_BASE + EFUSE_COUNT - 1
CAN_ID_MCU = 0x520
CAN_ID_ERR_DETAIL_BASE = 0x530
CAN_ID_ERR_DETAIL_LAST = CAN_ID_ERR_DETAIL_BASE + 7
CAN_ID_I2C_SCAN_BASE = 0x540
CAN_ID_I2C_SCAN_LAST = CAN_ID_I2C_SCAN_BASE + 13

PMBUS_CMD_NAMES = {
    0x79: "STATUS_WORD",
    0x8B: "READ_VOUT",
    0x89: "READ_IIN",
    0x97: "READ_PIN",
}

MCU_ERR_NAMES = {
    0: "OK",
    1: "NACK",
    2: "TIMEOUT",
    3: "PEC",
    4: "BUS",
    10: "CAN_TX",
    20: "ENABLE_FAIL",
    21: "SCAN_NO_ACK",
}

# ================= STATUS WORD BIT NAMES =================

TPS_STATUS_WORD_BITS = [
    "OUT_STATUS",       # 15
    "IOUT_STATUS",      # 14
    "INPUT_STATUS",     # 13
    "MFR_STATUS",       # 12
    "PGOODB",           # 11
    "RES10",            # 10
    "RES9",             # 9
    "UNKNOWN",          # 8
    "BUSY",             # 7
    "FET_OFF",          # 6
    "RES5",             # 5
    "RES4",             # 4
    "VIN_UV_FLT",       # 3
    "TEMP_FLT",         # 2
    "CML_ERR",          # 1
    "OTHER",            # 0
]

# ================= DATA STORAGE =================

data_queue = queue.Queue()

voltage = [0]*EFUSE_COUNT
current = [0]*EFUSE_COUNT
power   = [0]*EFUSE_COUNT
status_word = [0]*EFUSE_COUNT

current_history = [deque(maxlen=HISTORY_LENGTH) for _ in range(EFUSE_COUNT)]

mcu_shunt = 0
flt_bits = 0
system_flags = 0
mcu_dbg_stage = 0
mcu_dbg_error = 0
mcu_dbg_fail_channel = 0xFF
mcu_dbg_fail_command = 0

active_error_details = {}
i2c_scan_blocks = {}

system_flag_names = [
    "ENABLE_FAIL",
    "READ_FAIL",
    "PEC_FAIL",
    "TIMEOUT",
    "NACK_OR_BUS",
    "ZERO_TELEM",
    "CAN_TX_FAIL",
    "SCAN_NO_ACK",
]

selected_serial_port = SERIAL_PORT
active_serial_port = None
serial_connected = False
serial_error = "Not connected"
serial_instance = None
serial_state_lock = threading.Lock()


def list_available_ports():
    return [port.device for port in list_ports.comports()]


def set_target_port(port_name):
    global selected_serial_port
    with serial_state_lock:
        selected_serial_port = port_name


def disconnect_serial_port():
    global selected_serial_port, serial_instance
    with serial_state_lock:
        selected_serial_port = None
        if serial_instance is not None:
            try:
                serial_instance.close()
            except Exception:
                pass


def get_serial_state():
    with serial_state_lock:
        return serial_connected, active_serial_port, serial_error, selected_serial_port


def parse_bridge_can_line(line):
    parts = line.split(",", 4)
    if len(parts) < 5:
        return None

    try:
        timestamp_ms = int(parts[0].strip())
    except ValueError:
        return None

    frame_type = parts[1].strip().upper()
    if frame_type not in ("S", "E"):
        return None

    try:
        can_id = int(parts[2].strip(), 16)
        dlc = int(parts[3].strip())
    except ValueError:
        return None

    if dlc < 0 or dlc > 8:
        return None

    payload_str = parts[4].strip()
    payload_tokens = payload_str.split() if payload_str else []
    data_bytes = []

    for token in payload_tokens[:dlc]:
        try:
            data_bytes.append(int(token, 16))
        except ValueError:
            return None

    return {
        "timestamp_ms": timestamp_ms,
        "frame_type": frame_type,
        "can_id": can_id,
        "dlc": dlc,
        "data": data_bytes,
    }


def decode_can_frame(frame):
    global mcu_shunt, flt_bits, system_flags
    global mcu_dbg_stage, mcu_dbg_error, mcu_dbg_fail_channel, mcu_dbg_fail_command
    global active_error_details, i2c_scan_blocks

    can_id = frame["can_id"]
    data = frame["data"]

    if CAN_ID_EFUSE_BASE <= can_id <= CAN_ID_EFUSE_LAST:
        if len(data) < 8:
            return

        idx = can_id - CAN_ID_EFUSE_BASE
        voltage[idx] = data[0] | (data[1] << 8)
        current[idx] = data[2] | (data[3] << 8)
        power[idx] = data[4] | (data[5] << 8)
        status_word[idx] = data[6] | (data[7] << 8)
        current_history[idx].append(current[idx])

    elif can_id == CAN_ID_MCU:
        if len(data) < 4:
            return

        flt_bits = data[0]
        system_flags = data[1]
        mcu_shunt = data[2] | (data[3] << 8)

        if len(data) >= 8:
            mcu_dbg_stage = data[4]
            mcu_dbg_error = data[5]
            mcu_dbg_fail_channel = data[6]
            mcu_dbg_fail_command = data[7]

    elif CAN_ID_ERR_DETAIL_BASE <= can_id <= CAN_ID_ERR_DETAIL_LAST:
        if len(data) < 6:
            return

        slot = can_id - CAN_ID_ERR_DETAIL_BASE
        active = data[1] != 0

        if active:
            active_error_details[slot] = {
                "err": data[2],
                "channel": data[3],
                "command": data[4],
                "ttl": data[5],
            }
        else:
            if slot in active_error_details:
                del active_error_details[slot]

    elif CAN_ID_I2C_SCAN_BASE <= can_id <= CAN_ID_I2C_SCAN_LAST:
        if len(data) < 4:
            return

        slot = can_id - CAN_ID_I2C_SCAN_BASE
        i2c_scan_blocks[slot] = {
            "base": data[1],
            "mask": data[2],
            "found": data[3],
        }


def decode_legacy_csv(line):
    global mcu_shunt, flt_bits, system_flags

    parts = line.split(",")

    if parts[0] == "510" and len(parts) >= 6:
        idx = int(parts[1])
        if 0 <= idx < EFUSE_COUNT:
            voltage[idx] = int(parts[2])
            current[idx] = int(parts[3])
            power[idx] = int(parts[4])
            status_word[idx] = int(parts[5], 16)
            current_history[idx].append(current[idx])
        return True

    if parts[0] == "520" and len(parts) >= 4:
        mcu_shunt = int(parts[1])
        flt_bits = int(parts[2], 16)
        system_flags = int(parts[3], 16)
        return True

    return False

# ================= SERIAL THREAD =================

def serial_thread():
    global mcu_shunt, flt_bits, system_flags
    global serial_connected, active_serial_port, serial_error, serial_instance

    ser = None

    while True:
        with serial_state_lock:
            target_port = selected_serial_port

        if not target_port:
            if ser is not None:
                try:
                    ser.close()
                except Exception:
                    pass
                ser = None

            with serial_state_lock:
                serial_instance = None
                active_serial_port = None
                serial_connected = False
                serial_error = "Disconnected"

            time.sleep(0.2)
            continue

        if ser is None or not ser.is_open or ser.port != target_port:
            if ser is not None:
                try:
                    ser.close()
                except Exception:
                    pass
                ser = None

            try:
                ser = serial.Serial(target_port, BAUD_RATE, timeout=1)
                with serial_state_lock:
                    serial_instance = ser
                    active_serial_port = target_port
                    serial_connected = True
                    serial_error = ""
            except Exception as exc:
                with serial_state_lock:
                    serial_instance = None
                    active_serial_port = None
                    serial_connected = False
                    serial_error = str(exc)
                time.sleep(1.0)
                continue

        try:
            line = ser.readline().decode(errors="replace").strip()
            if not line:
                continue

            data_queue.put(line)

            frame = parse_bridge_can_line(line)
            if frame is not None:
                decode_can_frame(frame)
            else:
                try:
                    decode_legacy_csv(line)
                except (ValueError, IndexError):
                    pass

        except Exception as exc:
            if ser is not None:
                try:
                    ser.close()
                except Exception:
                    pass
                ser = None

            with serial_state_lock:
                serial_instance = None
                active_serial_port = None
                serial_connected = False
                serial_error = str(exc)

            time.sleep(0.3)

# ================= GUI =================

class PDUDashboard:

    def __init__(self, root):
        self.root = root
        root.title("Professional PDU Dashboard")

        self.page_index = 0
        self.serial_port_var = tk.StringVar(value=SERIAL_PORT)

        self.build_menu()
        self.build_serial_panel()

        self.build_top()
        self.build_mcu()
        self.build_plots()
        self.build_serial_waterfall()

        self.refresh_ports()

        self.update_gui()

    def build_menu(self):
        menu_bar = tk.Menu(self.root)
        serial_menu = tk.Menu(menu_bar, tearoff=0)
        self.ports_menu = tk.Menu(serial_menu, tearoff=0)

        serial_menu.add_cascade(label="Select COM Port", menu=self.ports_menu)
        serial_menu.add_command(label="Refresh Ports", command=self.refresh_ports)
        serial_menu.add_separator()
        serial_menu.add_command(label="Connect", command=self.connect_selected_port)
        serial_menu.add_command(label="Disconnect", command=self.disconnect_port)

        menu_bar.add_cascade(label="Serial", menu=serial_menu)
        self.root.config(menu=menu_bar)

    def build_serial_panel(self):
        serial_frame = tk.LabelFrame(self.root, text="Serial Connection")
        serial_frame.pack(fill="x", pady=5)

        ttk.Label(serial_frame, text="Port:").pack(side="left", padx=(8, 4))

        self.port_combo = ttk.Combobox(
            serial_frame,
            textvariable=self.serial_port_var,
            state="readonly",
            width=12,
        )
        self.port_combo.pack(side="left", padx=4, pady=4)

        ttk.Button(serial_frame, text="Refresh", command=self.refresh_ports).pack(
            side="left", padx=4
        )
        ttk.Button(serial_frame, text="Connect", command=self.connect_selected_port).pack(
            side="left", padx=4
        )
        ttk.Button(serial_frame, text="Disconnect", command=self.disconnect_port).pack(
            side="left", padx=4
        )
        ttk.Button(serial_frame, text="Serial Window", command=self.show_serial_window).pack(
            side="left", padx=4
        )

        self.serial_status_label = tk.Label(serial_frame, text="Status: Disconnected", fg="red")
        self.serial_status_label.pack(side="left", padx=10)

    def refresh_ports(self):
        ports = list_available_ports()

        self.port_combo["values"] = ports

        selected = self.serial_port_var.get()
        if ports:
            if selected not in ports:
                self.serial_port_var.set(ports[0])
        else:
            self.serial_port_var.set("")

        self.ports_menu.delete(0, "end")
        if ports:
            for port in ports:
                self.ports_menu.add_radiobutton(
                    label=port,
                    value=port,
                    variable=self.serial_port_var,
                    command=self.connect_selected_port,
                )
        else:
            self.ports_menu.add_command(label="No COM ports found")

    def connect_selected_port(self):
        port_name = self.serial_port_var.get().strip()
        if port_name:
            set_target_port(port_name)

    def disconnect_port(self):
        disconnect_serial_port()

    # ================= TOP EFUSE PANELS =================

    def build_top(self):
        self.efuse_frames = []

        top_frame = tk.Frame(self.root)
        top_frame.pack()

        for i in range(EFUSE_COUNT):
            frame = tk.LabelFrame(top_frame, text=f"eFuse {i}", padx=5, pady=5)
            frame.grid(row=i//4, column=i%4, padx=5, pady=5)

            v_label = tk.Label(frame, text="V: 0 mV")
            v_label.pack()

            i_label = tk.Label(frame, text="I: 0 mA")
            i_label.pack()

            p_label = tk.Label(frame, text="P: 0 (10mW)")
            p_label.pack()

            bit_frame = tk.Frame(frame)
            bit_frame.pack()

            bit_labels = []

            for b in range(16):
                lbl = tk.Label(bit_frame, text=TPS_STATUS_WORD_BITS[b],
                               width=12, relief="groove")
                lbl.grid(row=b//4, column=b%4)
                bit_labels.append(lbl)

            self.efuse_frames.append((v_label, i_label, p_label, bit_labels))

    # ================= MCU PANEL =================

    def build_mcu(self):
        mcu_frame = tk.LabelFrame(self.root, text="MCU Telemetry")
        mcu_frame.pack(fill="x", pady=5)

        self.shunt_label = tk.Label(mcu_frame, text="Shunt: 0 mA")
        self.shunt_label.pack()

        self.mcu_debug_label = tk.Label(
            mcu_frame,
            text="Stage:0  Err:0  FailCh:-  FailCmd:0x00",
        )
        self.mcu_debug_label.pack()

        self.mcu_debug_detail_label = tk.Label(
            mcu_frame,
            text="Error: OK",
        )
        self.mcu_debug_detail_label.pack()

        error_list_frame = tk.LabelFrame(mcu_frame, text="Active Errors (1s TTL)")
        error_list_frame.pack(fill="x", padx=4, pady=4)
        self.error_listbox = tk.Listbox(error_list_frame, height=6)
        self.error_listbox.pack(fill="x", padx=4, pady=4)

        i2c_scan_frame = tk.LabelFrame(mcu_frame, text="I2C ACK Scan")
        i2c_scan_frame.pack(fill="x", padx=4, pady=4)
        self.i2c_scan_label = tk.Label(i2c_scan_frame, text="ACK addresses: waiting for scan frames...")
        self.i2c_scan_label.pack(anchor="w", padx=4, pady=(2, 0))
        self.i2c_scan_listbox = tk.Listbox(i2c_scan_frame, height=3)
        self.i2c_scan_listbox.pack(fill="x", padx=4, pady=4)

        self.flt_labels = []
        flt_frame = tk.Frame(mcu_frame)
        flt_frame.pack()

        for i in range(2):
            lbl = tk.Label(flt_frame, text=f"FLT{i}", width=8, relief="groove")
            lbl.grid(row=0, column=i)
            self.flt_labels.append(lbl)

        self.sys_labels = []
        sys_frame = tk.Frame(mcu_frame)
        sys_frame.pack()

        for i in range(8):
            lbl = tk.Label(sys_frame, text=system_flag_names[i],
                           width=8, relief="groove")
            lbl.grid(row=0, column=i)
            self.sys_labels.append(lbl)

        rename_btn = tk.Button(mcu_frame, text="Rename Flags",
                               command=self.rename_flags)
        rename_btn.pack()

    def rename_flags(self):
        for i in range(8):
            new_name = simpledialog.askstring("Rename",
                        f"New name for FLAG{i}")
            if new_name:
                system_flag_names[i] = new_name
                self.sys_labels[i].config(text=new_name)

    # ================= PLOT SECTION =================

    def build_plots(self):
        plot_frame = tk.LabelFrame(self.root, text="Current History")
        plot_frame.pack(fill="both", expand=True)

        control_frame = tk.Frame(plot_frame)
        control_frame.pack()

        tk.Button(control_frame, text="Prev",
                  command=self.prev_page).pack(side="left")

        tk.Button(control_frame, text="Next",
                  command=self.next_page).pack(side="left")

        self.figure, self.ax = plt.subplots(2, 1, figsize=(8,5))
        self.canvas = FigureCanvasTkAgg(self.figure, master=plot_frame)
        self.canvas.get_tk_widget().pack(fill="both", expand=True)

    def build_serial_waterfall(self):
        self.waterfall_window = tk.Toplevel(self.root)
        self.waterfall_window.title("Serial Monitor")
        self.waterfall_window.geometry("900x400")
        self.waterfall_window.protocol("WM_DELETE_WINDOW", self.waterfall_window.withdraw)

        waterfall_frame = tk.LabelFrame(self.waterfall_window, text="Serial Waterfall")
        waterfall_frame.pack(fill="both", expand=True, padx=6, pady=6)

        self.waterfall_text = tk.Text(waterfall_frame, height=24, state="disabled")
        self.waterfall_text.pack(fill="both", expand=True)

    def show_serial_window(self):
        if self.waterfall_window.state() == "withdrawn":
            self.waterfall_window.deiconify()
        self.waterfall_window.lift()
        self.waterfall_window.focus_force()

    def append_waterfall_line(self, text_line):
        self.waterfall_text.configure(state="normal")
        self.waterfall_text.insert("end", text_line + "\n")

        line_count = int(self.waterfall_text.index("end-1c").split(".")[0])
        if line_count > WATERFALL_MAX_LINES:
            self.waterfall_text.delete("1.0", f"{line_count - WATERFALL_MAX_LINES + 1}.0")

        self.waterfall_text.see("end")
        self.waterfall_text.configure(state="disabled")

    def prev_page(self):
        self.page_index = (self.page_index - 1) % 4

    def next_page(self):
        self.page_index = (self.page_index + 1) % 4

    # ================= UPDATE LOOP =================

    def update_gui(self):

        # Serial status + waterfall
        connected, active_port, last_error, _ = get_serial_state()
        if connected and active_port:
            self.serial_status_label.config(text=f"Status: Connected ({active_port})", fg="green")
        else:
            if last_error and last_error != "Disconnected":
                self.serial_status_label.config(text=f"Status: Disconnected ({last_error})", fg="red")
            else:
                self.serial_status_label.config(text="Status: Disconnected", fg="red")

        drained = 0
        while drained < 200:
            try:
                message = data_queue.get_nowait()
            except queue.Empty:
                break
            self.append_waterfall_line(message)
            drained += 1

        # Update efuse panels
        for i in range(EFUSE_COUNT):
            v_lbl, i_lbl, p_lbl, bit_lbls = self.efuse_frames[i]

            v_lbl.config(text=f"V: {voltage[i]} mV")
            i_lbl.config(text=f"I: {current[i]} mA")
            p_lbl.config(text=f"P: {power[i]} (10mW)")

            for b in range(16):
                bit = (status_word[i] >> (15-b)) & 1
                bit_lbls[b].config(bg="red" if bit else "green")

        # MCU
        self.shunt_label.config(text=f"Shunt: {mcu_shunt} mA")

        fail_ch_text = "-" if mcu_dbg_fail_channel == 0xFF else str(mcu_dbg_fail_channel)
        err_name = MCU_ERR_NAMES.get(mcu_dbg_error, f"UNK_{mcu_dbg_error}")
        cmd_name = PMBUS_CMD_NAMES.get(mcu_dbg_fail_command, f"CMD_0x{mcu_dbg_fail_command:02X}")

        self.mcu_debug_label.config(
            text=f"Stage:{mcu_dbg_stage}  Err:{mcu_dbg_error}  FailCh:{fail_ch_text}  FailCmd:0x{mcu_dbg_fail_command:02X}"
        )
        self.mcu_debug_detail_label.config(
            text=f"Error:{err_name}  Command:{cmd_name}"
        )

        self.error_listbox.delete(0, tk.END)
        if active_error_details:
            for slot in sorted(active_error_details.keys()):
                entry = active_error_details[slot]
                err_code = entry["err"]
                ch = entry["channel"]
                cmd = entry["command"]
                ttl = entry["ttl"]

                err_name = MCU_ERR_NAMES.get(err_code, f"UNK_{err_code}")
                cmd_name = PMBUS_CMD_NAMES.get(cmd, f"CMD_0x{cmd:02X}")
                ch_text = "-" if ch == 0xFF else str(ch)

                self.error_listbox.insert(
                    tk.END,
                    f"ERR:{err_code}({err_name}) CH:{ch_text} CMD:0x{cmd:02X}({cmd_name}) TTL:{ttl*100}ms",
                )
        else:
            self.error_listbox.insert(tk.END, "No active errors")

        ack_addresses = []
        total_found = 0
        for slot in sorted(i2c_scan_blocks.keys()):
            block = i2c_scan_blocks[slot]
            base = block["base"]
            mask = block["mask"]
            total_found = max(total_found, block["found"])
            for bit in range(8):
                if (mask >> bit) & 1:
                    ack_addresses.append(base + bit)

        ack_addresses = sorted(set(ack_addresses))
        self.i2c_scan_listbox.delete(0, tk.END)
        if ack_addresses:
            self.i2c_scan_label.config(text=f"ACK addresses found: {len(ack_addresses)} (reported: {total_found})")
            self.i2c_scan_listbox.insert(tk.END, " ".join([f"0x{addr:02X}" for addr in ack_addresses]))
        else:
            self.i2c_scan_label.config(text="ACK addresses: none")
            self.i2c_scan_listbox.insert(tk.END, "No I2C ACKs in scan range")

        for i in range(2):
            active = (flt_bits >> i) & 1
            self.flt_labels[i].config(bg="red" if active else "green")

        for i in range(8):
            active = (system_flags >> i) & 1
            self.sys_labels[i].config(bg="red" if active else "green")

        # Plots
        self.ax[0].clear()
        self.ax[1].clear()

        base = self.page_index * 2
        idx1 = base
        idx2 = base + 1

        self.ax[0].plot(current_history[idx1])
        self.ax[0].set_title(f"eFuse {idx1} Current (mA)")

        self.ax[1].plot(current_history[idx2])
        self.ax[1].set_title(f"eFuse {idx2} Current (mA)")

        self.canvas.draw()

        self.root.after(int(1000/UPDATE_RATE_HZ), self.update_gui)

# ================= MAIN =================

threading.Thread(target=serial_thread, daemon=True).start()

root = tk.Tk()
app = PDUDashboard(root)
root.mainloop()
