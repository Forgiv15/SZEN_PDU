
# TPS25990 Firmware Reference (LLM / Copilot Optimized)

## Purpose
This document is a firmware-oriented reference for implementing a TPS25990 driver on a PIC32CM MCU.
It intentionally reorganizes the datasheet into software-centric topics.

---

# Device Overview

TPS25990 is a PMBus-controlled eFuse with:

- Integrated 0.79 mΩ MOSFET
- Up to 50 A RMS / 60 A peak
- PMBus telemetry and configuration
- Internal ADC and telemetry engine
- NVM configuration storage
- Blackbox fault logging
- GPIO subsystem
- DAC outputs
- Comparator subsystem
- Current limiting
- Circuit-breaker style overcurrent protection
- Fast-trip short-circuit protection
- Overtemperature protection
- Parallel eFuse synchronization

---

# Important Hardware Pins

## Power

| Pin | Function |
|------|------|
| VIN | Input power |
| VOUT | Output power |
| VDD | Controller supply |
| GND | Ground |

## Protection Configuration

| Pin | Function |
|------|------|
| ILIM | Startup current limit resistor |
| IMON | Current monitor + OC threshold resistor |
| IREF/DAC2 | Current limit reference DAC |
| DVDT | Startup slew-rate capacitor |
| EN/UVLO | Enable and UVLO input |

## PMBus

| Pin | Function |
|------|------|
| SDA | PMBus data |
| SCL | PMBus clock |
| SMBA# | SMBus alert (default GPIO4 function) |

## Telemetry

| Pin | Function |
|------|------|
| IMON | Analog current monitor |
| TEMP | Analog temperature monitor |
| AUX | External ADC channel |

---

# Firmware Architecture

Recommended driver layers:

```text
TPS25990_HAL
    |
TPS25990_PMBUS
    |
TPS25990_DRIVER
    |
PDU_APPLICATION
```

---

# Telemetry Channels

Internal ADC can sample:

1. VIN
2. VOUT
3. VIMON
4. VTEMP
5. VAUX
6. ADDR0
7. ADDR1

Notes:

- 10-bit ADC
- 460 kSPS normal mode
- 270 kSPS high-performance mode
- Internal 5 kHz anti-alias filter
- Background self-calibration

---

# High Performance ADC Mode

Enable:

ADC_HI_PERF = 1

Effects:

- Lower DNL
- Lower INL
- Better telemetry accuracy
- Lower sample rate

Recommended for PDU applications.

---

# Important Protection Functions

## Startup Current Limiting

Uses:

- ILIM resistor
- IREF DAC

Active only during startup.

## Steady-State Overcurrent

Uses:

- IMON resistor
- IREF DAC

Acts as circuit breaker.

## Fast Trip

Response:

~280 ns

Protects against severe short circuits.

## Thermal Shutdown

Typical:

- Shutdown ≈149°C
- Hysteresis ≈11°C

---

# Firmware Telemetry Polling

Recommended periodic rates:

| Signal | Rate |
|----------|----------|
| Current | 50-100 Hz |
| VIN | 10-20 Hz |
| VOUT | 10-20 Hz |
| Temperature | 2-10 Hz |
| Fault Registers | 10-50 Hz |

---

# Blackbox System

Stores:

- Fault type
- Relative timestamp
- Device state

Useful for:

- Field diagnostics
- Failure analysis
- Warranty returns

Recommended:

Read blackbox contents after every fault event before clearing status bits.

---

# GPIO Subsystem

Default assignments:

| GPIO | Default |
|--------|--------|
| GPIO1 | PG |
| GPIO2 | FLT |
| GPIO3 | SWEN |
| GPIO4 | SMBA# |

GPIOs are PMBus configurable.

---

# Startup Sequence

1. VIN valid
2. VDD valid
3. PMBus alive
4. EN asserted
5. Insertion delay
6. DVDT ramp
7. Current limit active
8. PG asserted
9. Steady-state mode

---

# Shutdown Sequence

1. Disable command or fault
2. FET off
3. QOD active (if configured)
4. Fault flags set
5. Blackbox updated

---

# Recommended PIC32CM Software Tasks

## 1 ms

- PMBus state machine

## 10 ms

- Read telemetry

## 100 ms

- Publish CAN messages

## Fault interrupt

- Read status registers
- Read blackbox
- Store event log

---

# CAN Mapping Suggestion

CAN ID 0x500

- VIN
- VOUT
- IOUT
- Temperature

CAN ID 0x501

- Status Word
- Fault Word

CAN ID 0x502

- Device specific status

---

# NVM Strategy

During production:

1. Configure device
2. Verify settings
3. Program NVM
4. Read back
5. CRC/validation

During runtime:

- Avoid frequent NVM writes.
- Treat NVM as factory configuration.

---

# Driver Functions

Recommended API:

```c
bool TPS25990_Init(void);
bool TPS25990_ReadTelemetry(void);
bool TPS25990_Enable(void);
bool TPS25990_Disable(void);
bool TPS25990_ClearFaults(void);
bool TPS25990_ReadStatus(void);
bool TPS25990_ReadBlackbox(void);
bool TPS25990_ProgramNVM(void);
```

---

# Notes For Copilot

When generating firmware:

- Prefer PMBus transaction wrappers.
- Keep register addresses centralized.
- Convert telemetry immediately into engineering units.
- Log raw PMBus values for debugging.
- Separate fault handling from telemetry polling.
- Never clear fault registers before logging them.
