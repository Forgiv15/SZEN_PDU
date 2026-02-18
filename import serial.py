import serial
import threading
import queue
import tkinter as tk
from tkinter import simpledialog
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from collections import deque
import time

# ================= CONFIG =================

SERIAL_PORT = "COM8"
BAUD_RATE = 921600

EFUSE_COUNT = 8
HISTORY_SECONDS = 5
UPDATE_RATE_HZ = 20
HISTORY_LENGTH = HISTORY_SECONDS * UPDATE_RATE_HZ

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

system_flag_names = [f"FLAG{i}" for i in range(8)]

# ================= SERIAL THREAD =================

def serial_thread():
    global mcu_shunt, flt_bits, system_flags

    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)

    while True:
        try:
            line = ser.readline().decode().strip()
            if not line:
                continue

            parts = line.split(",")

            if parts[0] == "510":
                idx = int(parts[1])
                voltage[idx] = int(parts[2])
                current[idx] = int(parts[3])
                power[idx]   = int(parts[4])
                status_word[idx] = int(parts[5], 16)

                current_history[idx].append(current[idx])

            elif parts[0] == "520":
                mcu_shunt = int(parts[1])
                flt_bits = int(parts[2], 16)
                system_flags = int(parts[3], 16)

        except:
            pass

# ================= GUI =================

class PDUDashboard:

    def __init__(self, root):
        self.root = root
        root.title("Professional PDU Dashboard")

        self.page_index = 0

        self.build_top()
        self.build_mcu()
        self.build_plots()

        self.update_gui()

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

    def prev_page(self):
        self.page_index = (self.page_index - 1) % 4

    def next_page(self):
        self.page_index = (self.page_index + 1) % 4

    # ================= UPDATE LOOP =================

    def update_gui(self):

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
