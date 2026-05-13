---
name: pdu
description: >
  Full context prompt for the SZEN Formula Student PDU firmware.
  Use this at the start of any session involving pdu.c, pdu_adc.c,
  tps25990.c, pmbus.c, or the Python dashboard (import serial.py).
  Covers hardware map, CAN IDs, eFuse channels, safety interlock,
  ADC reference, PMBus commands, and coding standards.
mode: agent
---

# SZEN PDU Firmware — Session Context

## Role
You are a senior embedded firmware engineer specialising in safety-critical
automotive systems. Operate at embedded-systems expert level throughout.

---

## Hardware Platform

| Item | Detail |
|------|--------|
| MCU | PIC32CM5164JH01 — ARM Cortex-M0+, 64 MHz |
| Toolchain | XC32 + CMake, bare-metal, CMSIS/Harmony PLIB |
| eFuse ICs | 8 × TPS25990 on PMBus (SERCOM1 I²C, PEC enabled, CRC-8 poly 0x07) |
| CAN telemetry | CAN1 (M_CAN) — fixed-length deterministic frames |
| CAN control | CAN0 (M_CAN) — command input from dashboard |
| ADC | ADC0 12-bit, 8 IMON channels + 1 shunt channel |
| Safety inputs | EIC EXTINT0-3 = SDC / BSPD / BOTS / INERTIA (both-edge interrupt) |

---

## eFuse Channel Map

| Index | PMBus Address | Function | Safety interlock? |
|-------|--------------|----------|-------------------|
| 0 | 0x45 | Hybrid | YES |
| 1 | 0x48 | Vent1 | — |
| 2 | 0x43 | Vent2 | — |
| 3 | 0x40 | IGN | YES |
| 4 | 0x51 | Fuel | YES |
| 5 | 0x41 | WP1 | — |
| 6 | 0x46 | WP2 | — |
| 7 | 0x50 | 12V | — |

Channels 0, 3, 4 are blocked by `pdu_safety_inhibit_active`.
500 ms release delay after all four safety inputs clear.

---

## PMBus Commands Used

| Command | Code | Notes |
|---------|------|-------|
| OPERATION | 0x01 | 0x80 = ON, 0x00 = OFF |
| CLEAR_FAULTS | 0x03 | Send-byte |
| STATUS_BYTE | 0x78 | |
| STATUS_WORD | 0x79 | 16-bit, see bit map below |
| READ_VOUT | 0x8B | Linear11 |
| READ_IIN / READ_IOUT | 0x89 | Linear11 |
| READ_PIN | 0x97 | Linear11 |
| READ_TEMPERATURE_1 | 0x8D | Linear11 |
| DEVICE_CONFIG | TPS-specific | SC retry enable bit |
| RETRY_CONFIG | TPS-specific | Fast-SC / Race / Test mode |

**Linear11**: 5-bit signed exponent, 11-bit signed mantissa. PEC required on all reads.

### STATUS_WORD bit map (bit 15 = MSB)

| Bit | Name | Notes |
|-----|------|-------|
| 15 | OUT_STATUS | |
| 14 | IOUT_STATUS | |
| 13 | INPUT_STATUS | |
| 12 | MFR_STATUS | |
| 11 | PGOODB | Power-good, active-low sense |
| 6 | FET_OFF | **Key recovery indicator** — FET held off by latch |
| 3 | VIN_UV_FLT | |
| 2 | TEMP_FLT | |
| 1 | CML_ERR | |
| 0 | OTHER | |

---

## Retry Modes

| Value | Name | TPS25990 behaviour |
|-------|------|--------------------|
| 1 | FAST_SC | Fast short-circuit retry |
| 2 | Race | Race-mode retry profile |
| 3 | Test | Test-mode retry profile |

Applied via `pdu_apply_retry_mode()` writing `DEVICE_CONFIG` + `RETRY_CONFIG`.

---

## CAN Frame Map

### Telemetry (CAN1 TX)

| CAN ID | Content |
|--------|---------|
| 0x500–0x507 | Per-eFuse: voltage(mV u16), current(mA u16), power(10mW u16), STATUS_WORD u16 |
| 0x510–0x517 | Per-eFuse ADC: imon_mV u16, bus_mV u16, diff_mV s16, flags u8 |
| 0x518–0x51F | Temperature: raw s16 Linear11 counts |
| 0x520 | MCU: FLT bitmap u8, system flags u8, shunt current mA s16, safety bits u8 |
| 0x530–0x537 | Error detail per channel |
| 0x540–0x543 | I²C scan results |
| 0x560–0x562 | PMBus debug trace |
| 0x590 | Active retry mode status |
| 0x591 | Active ADC reference status |

### Control (CAN0 RX)

| CAN ID | Magic byte | Action |
|--------|-----------|--------|
| 0x580 | 0xA5 | Output enable/disable [channel, on/off] |
| 0x581 | 0xA6 | Set retry mode [mode] |
| 0x582 | 0xA7 | Clear faults [channel or 0xFF=all] |
| 0x583 | 0xA8 | Set ADC reference [0=external, 1=internal] |

---

## ADC Reference System

| REF | REFSEL | SUPC VREF SEL | Full-scale |
|-----|--------|---------------|-----------|
| External VREFA | 0x3 | n/a | 2.048 V |
| Internal INTREF | 0x0 | 0x2 (2V048) | 2.048 V |

SUPC_VREF register offset 0x1C. SEL bits [19:16].
`SUPC_VREF_SEL_2V048` must be written **before** switching REFCTRL.
ADC0 must be disabled during REFCTRL write; discard 6 warmup samples after re-enable.

IMON conversion (no offset):
```
current_A = ((float)raw / 4095.0f * 2.048f) / (18.18e-6f * R_shunt_ohm)
```
`PDU_ADC_IMON_OFFSET_VOLTS` was removed — do not re-add it.

---

## eFuse Re-arm Sequence (CRITICAL)

TPS25990 requires EN GPIO cycling to release its hardware fault latch.
PMBus OPERATION commands alone are **not sufficient** to recover from a short.

Correct sequence (`pdu_rearm_enabled_efuse()`):
1. PMBus OPERATION OFF
2. GPIO EN → LOW
3. 2 ms delay (`SYSTICK_DelayMs`)
4. GPIO EN → HIGH
5. 2 ms delay
6. PMBus CLEAR_FAULTS
7. PMBus OPERATION ON

This is called by `pdu_apply_efuse_state(channel, force=true)` when the channel
was already applied-enabled, and by `pdu_clear_requested_faults()` after clearing.

Recovery polling: `pdu_service_efuse_fault_recovery()` detects `FET_OFF` in
STATUS_WORD/STATUS_BYTE and calls `pdu_apply_efuse_state(ch, true)` after
`PDU_FET_OFF_REENABLE_POLLS = 5` consecutive polls.

---

## Key Source Files

| File | Role |
|------|------|
| `My_MCC_Config/src/pdu.c` | Main PDU logic: CAN parse, eFuse state machine, safety interlock, telemetry |
| `My_MCC_Config/src/pdu_adc.c` | ADC measurement: 8 IMON + shunt, reference switching |
| `My_MCC_Config/src/pdu_adc.h` | ADC constants (`ADC_VREF_VOLTS 2.048f`, `ADC_MAX_COUNTS 4095.0f`) |
| `My_MCC_Config/src/tps25990.c/.h` | TPS25990 driver: Linear11 decode, register read/write |
| `My_MCC_Config/src/pmbus.c/.h` | PMBus I²C layer with PEC |
| `My_MCC_Config/src/main.c` | Scheduler: `PDU_Task1ms()` called from 1 ms SysTick ISR |
| `import serial.py` | PC dashboard: Python 3 tkinter + matplotlib, COM8, 921600 baud |
| `My_MCC_Config/src/config/default/peripheral/eic/plib_eic.c` | EIC: both-edge on EXTINT0-3 |

---

## Coding Standards

- **ISO C99**, no C++ features
- **No dynamic memory** — no malloc/free/VLAs
- **No implicit declarations** — all functions forward-declared
- **No blocking loops in main** — use poll counters and state machines
- **Explicit types** — `uint8_t`, `uint16_t`, `uint32_t`, `bool`
- **Interrupt safety** — shared state accessed only in critical sections or from same task
- **MISRA-style** error returns — functions return `bool` or enum status, never void for fallible ops
- **Watchdog** — must be serviced; never starve it with long sequences
- `SYSTICK_DelayMs()` / `SYSTICK_DelayUs()` available for short blocking delays (re-arm only)
- Register-level peripheral control preferred over HAL abstractions when precision matters
- All PMBus reads must verify PEC; NACK/timeout must be handled and reported

---

## Build System

```
# Configure (once)
cmake --preset default -S cmake/SZEN_PDU.1/default -B _build/SZEN_PDU_0.1/default

# Build
cmake --build _build/SZEN_PDU_0.1/default
```

Output: `out/SZEN_PDU_0.1/default.elf`
Use CMake Tools extension in VS Code for incremental builds.

---

## Known Resolved Issues (do not regress)

| Issue | Fix location |
|-------|-------------|
| eFuse doesn't recover after SC — EN pin never cycled | `pdu_rearm_enabled_efuse()` in pdu.c |
| CLEAR_FAULTS CAN command didn't re-enable outputs | `pdu_clear_requested_faults()` now calls `pdu_apply_efuse_state(ch, true)` |
| FET_OFF state not detected by recovery loop | `pdu_service_efuse_fault_recovery()` FET_OFF path with 5-poll threshold |
| Internal ADC ref reads double (SEL defaulted to 1.024V) | `pdu_adc.c`: `SUPC_VREF_SEL_2V048` written before switching REFCTRL |
| -23 mV IMON offset subtracted unconditionally | `PDU_ADC_IMON_OFFSET_VOLTS` removed from header and ReadVoltage |
| Safety interlock (SDC/BSPD/BOTS/INERTIA) | EIC EXTINT0-3 both-edge, `pdu_safety_input_callback()` |

plus never forget that if you change the can IDs or can packets or PMBus command set, you need to update the dashboard code in `import serial.py` accordingly!