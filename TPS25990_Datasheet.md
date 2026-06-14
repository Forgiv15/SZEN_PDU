# TPS25990 Datasheet

## 2.9 V to 16 V, 0.79-mΩ, 60-A Stackable eFuse with PMBus® Digital Telemetry

## 1. Features
- Input operating voltage range: 2.9 V to 16 V
- 20-V absolute maximum at input. Withstands up to -1 V at output
- Integrated low on-resistance FET: 0.79 mΩ (typ.)
- Rated for 50 A RMS and 60 A peak current
- Can be used as a standalone eFuse or primary controller in parallel configuration
- Supports parallel connection of multiple eFuses for higher current support
- Active device state synchronization and load sharing during start-up and steady-state for unlimited scalability
- PMBus® interface for telemetry, control, configuration and debug
- PIN/EIN/VIN/OUT/IIN/temperature/fault monitoring
- Power cycle with a single command
- On-chip non-volatile configuration memory
- Blackbox fault recording of multiple events with relative time-stamp and option to store on an external EEPROM
- Robust overcurrent protection (Programmable overcurrent threshold: 7 A to 50 A with accuracy of ±5% max)
- Fast-trip response (280 ns) for short-circuit protection
- Programmable overtemperature protection (OTP)
- Fast overvoltage protection with programmable threshold
- Programmable output slew rate control (dVdt) and programmable insertion delay timer
- Programmable undervoltage lockout (UVLO)
- Analog die temperature monitor output (TEMP)
- Four configurable general purpose I/O pins
- Small footprint: QFN 4.5-mm x 5-mm, 0.6-mm pitch, 26-pin

## 2. Description
The TPS25990 is an integrated, high-current circuit protection and power management device in a small package. The device provides multiple protection modes using very few external components and is a robust defense against overloads, short circuits, and excessive inrush current. The integrated PMBus® interface allows a host controller to monitor, control and configure the system in real-time. Key system parameters can be read back by remote telemetry.

## 3. Pin Configuration and Functions

| Pin Name | Pin No. | Description |
|---|---|---|
| ADDR1 | 1 | PMBus device I2C address configuration pin (pin strap). |
| ADDR0 | 2 | PMBus device I2C address configuration pin (pin strap). |
| AUX | 3 | Auxiliary ADC input channel / analog input for fast comparator. |
| DVDT | 4 | Start-up output slew rate control pin. |
| TEMP/CMP | 5 | Die junction temp monitor analog output / analog input for fast comparator. |
| DAC1 | 6 | Programmable General Purpose DAC analog current output. |
| IMON | 7 | External resistor sets OCP threshold and fast-trip threshold. Acts as analog output load current monitor. |
| ILIM | 8 | External resistor sets current limit threshold and active current sharing threshold. |
| IREF/DAC2 | 9 | Programmable reference voltage for OCP/active current sharing OR programmable analog voltage output. |
| OUT | 10-13 | Power output. |
| GND | 14 | Device ground reference pin. |
| SDA | 15 | I2C data line for PMBus interface. |
| SCL | 16 | I2C clock line for PMBus interface. |
| GPIO4/SMBA#... | 17 | General purpose digital I/O. Default: SMBus Alert output. |
| EN/UVLO | 18 | Active high enable input. Connect resistor divider to set UVLO. |
| GPIO1/PG... | 19 | General purpose digital I/O. Default: Power-Good output (PG). |
| GPIO2/FLT... | 20 | General purpose digital I/O. Default: Fault output (FLT). |
| GPIO3/SWEN... | 21 | General purpose digital I/O. Default: SWEN (synchronize multiple eFuses). |
| VDD | 22 | Controller power input pin. |
| IN | 23-26 | Power input. |

## 4. Absolute Maximum Ratings

| Parameter | Pin | Min | Max | Unit |
|---|---|---|---|---|
| VINMAX | IN | -0.3 | 20 | V |
| VDDMAX | VDD | -0.3 | 20 | V |
| VOUTMAX | OUT | -1 | Min(20, VIN+0.3) | V |
| VENMAX | EN/UVLO | | 20 | V |
| IMAX | IN to OUT | | 50 (Cont), 60 (Peak) | A |
| TJMAX | | -40 | 125 | °C |

## 5. PMBus Interface and Addressing
The TPS25990 uses 7-bit I2C device addressing. Up to 25 different addresses can be generated using pin-strapping combinations on ADDR0 and ADDR1. Default (Open/Open) is 0x40. Supports 100 kHz, 400 kHz, and 1 MHz speeds. Supports SMBus Alert Response Address (ARA) and Packet Error Checking (PEC).

## 6. PMBus Commands List

| Command Name | Code | Type | Default | Description |
|---|---|---|---|---|
| OPERATION | 01h | R/W Byte | 0x80 | eFuse ON/OFF control |
| CLEAR_FAULTS | 03h | Send Byte | N/A | Clear all fault status bits and Blackbox RAM |
| RESTORE_FACTORY_DEFAULTS | 12h | Send Byte | N/A | Reset configuration registers to factory defaults |
| STORE_USER_ALL | 15h | Send Byte | N/A | Store configuration to NVM/EEPROM |
| RESTORE_USER_ALL | 16h | Send Byte | N/A | Initialize config from NVM/EEPROM |
| BB_ERASE | F5h | Send Byte | N/A | Erase Blackbox data in EEPROM |
| FETCH_BB_EEPROM | F6h | Send Byte | N/A | Fetch Blackbox EEPROM to shadow registers |
| POWER_CYCLE | D9h | Send Byte | N/A | Power down output and restart after delay |
| MFR_WRITE_PROTECT | F8h | R/W Byte | 0x00 | Enable/Disable write protection (Password: 0xA2 to unlock) |
| CAPABILITY | 19h | Read Byte | 0xD0 | Supported PMBus features |
| STATUS_BYTE | 78h | Read Byte | N/A | Status register lower byte |
| STATUS_WORD | 79h | Read Word | N/A | Status register word |
| STATUS_OUT | 7Ah | Read Byte | N/A | OUT bus status |
| STATUS_IOUT | 7Bh | Read Byte | N/A | OUT current status |
| STATUS_INPUT | 7Ch | Read Byte | N/A | IN bus status |
| STATUS_TEMP | 7Dh | Read Byte | N/A | Device temperature status |
| STATUS_CML | 7Eh | Read Byte | N/A | Communications, Memory, Logic status |
| STATUS_MFR_SPECIFIC | 80h | Read Byte | N/A | Manufacturer specific fault status |
| STATUS_MFR_SPECIFIC_2 | F3h | Read Word | N/A | Additional manufacturer specific fault status |
| READ_VIN | 88h | Read Word | N/A | Input voltage |
| READ_VOUT | 8Bh | Read Word | N/A | Output voltage |
| READ_IIN | 89h | Read Word | N/A | Input current |
| READ_TEMPERATURE_1 | 8Dh | Read Word | N/A | Device temperature |
| READ_VAUX | D0h | Read Word | N/A | Auxiliary analog input voltage |
| READ_PIN | 97h | Read Word | N/A | Instantaneous input power |
| READ_EIN | 86h | Block Read | N/A | Accumulated input energy (6 bytes) |
| READ_VIN_AVG | DCh | Read Word | N/A | Average input voltage |
| READ_VIN_MIN | D1h | Read Word | N/A | Minimum input voltage |
| READ_VIN_PEAK | D2h | Read Word | N/A | Peak input voltage |
| READ_VOUT_AVG | DDh | Read Word | N/A | Average output voltage |
| READ_VOUT_MIN | DAh | Read Word | N/A | Minimum output voltage |
| READ_IIN_AVG | DEh | Read Word | N/A | Average input current |
| READ_IIN_PEAK | D4h | Read Word | N/A | Peak input current |
| READ_TEMP_AVG | D6h | Read Word | N/A | Average device temp |
| READ_TEMP_PEAK | D7h | Read Word | N/A | Peak device temp |
| READ_PIN_AVG | DFh | Read Word | N/A | Average input power |
| READ_PIN_PEAK | D5h | Read Word | N/A | Peak input power |
| READ_SAMPLE_BUF | D8h | Block Read | N/A | ADC sample buffer (64 bytes) |
| READ_BB_RAM | FDh | Block Read | N/A | Blackbox RAM registers (7 bytes) |
| READ_BB_EEPROM | F4h | Block Read | N/A | Blackbox EEPROM content (16 bytes) |
| BB_TIMER | FAh | Read Byte | N/A | Blackbox tick timer |
| PMBUS_ADDR | FBh | R/W Byte | 0x40 | PMBus device address |
| VIN_UV_WARN | 58h | R/W Word | 0x0095 | Input undervoltage warning threshold |
| VIN_UV_FLT | 59h | R/W Word | 0x008D | Input undervoltage fault threshold |
| VIN_OV_WARN | 57h | R/W Word | 0x00A5 | Input overvoltage warning threshold |
| VIN_OV_FLT | 55h | R/W Word | 0x000E | Input overvoltage fault threshold |
| VOUT_UV_WARN | 43h | R/W Word | 0x0095 | Output undervoltage warning threshold |
| VOUT_PGTH | 5Fh | R/W Word | 0x008D | Output threshold for PGOOD de-assertion |
| OT_WARN | 51h | R/W Word | 0x007E | Overtemperature warning threshold |
| OT_FLT | 4Fh | R/W Word | 0x0085 | Overtemperature fault threshold |
| PIN_OP_WARN | 6Bh | R/W Word | 0x00FF | Input overpower warning threshold |
| IIN_OC_WARN | 5Dh | R/W Word | 0x00FF | Input overcurrent warning threshold |
| VIREF | E0h | R/W Byte | 0x32 | Reference voltage for overcurrent/current sharing |
| GPIO_CONFIG_12 | E1h | R/W Byte | 0x00 | GPIO1 & GPIO2 config |
| GPIO_CONFIG_34 | E2h | R/W Byte | 0x00 | GPIO3 & GPIO4 config |
| ALERT_MASK | DBh | R/W Word | 0x0100 | SMB Alert assertion mask |
| FAULT_MASK | E3h | R/W Word | 0x0000 | FLT assertion mask |
| DEVICE_CONFIG | E4h | R/W Word | 0x1400 | Device configuration |
| BB_CONFIG | E5h | R/W Byte | 0x00 | Blackbox configuration |
| OC_TIMER | E6h | R/W Byte | 0x14 | Transient overcurrent blanking timer |
| RETRY_CONFIG | E7h | R/W Byte | 0x84 | Auto-retry configuration |
| ADC_CONFIG_1 | E8h | R/W Byte | 0x00 | ADC Configuration 1 |
| ADC_CONFIG_2 | E9h | R/W Byte | 0x00 | ADC Configuration 2 |
| PK_MIN_AVG | EAh | R/W Byte | 0x00 | Peak/Min/Average configuration |
| VCMPxREF | EBh | R/W Byte | 0xFF | General purpose comparator reference thresholds |
| PSU_VOLTAGE | ECh | R/W Byte | 0x9D | PSU nominal voltage |
| CABLE_DROP | EDh | R/W Byte | 0xFF | Maximum cable voltage drop expected |
| GPDAC1 | F0h | R/W Byte | 0x00 | General purpose DAC1 output current |
| GPDAC2 | F1h | R/W Byte | 0x00 | General purpose DAC2 output voltage |
| INS_DLY | F9h | R/W Byte | 0x00 | Insertion delay |

## 7. Register Bit Definitions

### STATUS_BYTE (78h)
| Bits | Name | Description |
|---|---|---|
| 7 | BUSY | Device is busy |
| 6 | FET_OFF | FET gate driver disabled |
| 5:4 | Reserved | Reserved |
| 3 | VIN_UV_FLT | VIN undervoltage fault detected |
| 2 | STATUS_TEMP | Overtemperature fault (Active bits in STATUS_TEMP) |
| 1 | CML_ERR | Communications, Memory, or Logic error |
| 0 | NONE_OF_THE_ABOVE | An event other than bits 7:1 has occurred |

### STATUS_WORD (79h)
| Bits | Name | Description |
|---|---|---|
| 15 | OUT_STATUS | OUTPUT fault status |
| 14 | IOUT_STATUS | IOUT fault status |
| 13 | INPUT_STATUS | INPUT fault status |
| 12 | MFR_STATUS | Manufacturer specific fault status |
| 11 | PGOODB | Power Good de-asserted |
| 10:9 | Reserved | Reserved |
| 8 | UNKNOWN | Unknown fault occurred |
| 7:0 | STATUS_BYTE | Same as STATUS_BYTE |

### STATUS_INPUT (7Ch)
| Bits | Name | Description |
|---|---|---|
| 7 | VIN_OV_FLT | VIN overvoltage fault |
| 6 | VIN_OV_WARN | VIN overvoltage warning |
| 5 | VIN_UV_WARN | VIN undervoltage warning |
| 4 | VIN_UV_FLT | VIN undervoltage fault |
| 3 | Reserved | Reserved |
| 2 | OC_FLT | Overcurrent fault |
| 1 | OC_WARN | Overcurrent warning |
| 0 | IN_OP_WARN | Overpower warning |

### DEVICE_CONFIG (E4h)
| Bits | Name | Description |
|---|---|---|
| 15 | PG_DVDT_DLY | PG delay for discharging DVDT (1 = 38ms, 0 = 110µs) |
| 14 | DIS_VDSFLT | Disable FET D-S fault detection at start-up |
| 13 | SC_RETRY | Retry after short circuit (1 = retry once, 0 = latch off) |
| 12:11 | SPFAIL | Scalable fast-trip threshold (11=225%, 10=200%, 01=175%, 00=150%) |
| 10:9 | DVDT_CONFIG | DVDT current scaling (11=150%, 10=100%, 01=75%, 00=50%) |
| 8 | VIN_TRAN_DIS | Input transient blanking control (1=Disabled, 0=Enabled) |
| 7 | EXT_EEPROM | External EEPROM connected |
| 6 | IREF_DAC2_SEL | IREF/DAC2 pin output (1=DAC2, 0=IREF DAC) |
| 5 | CMP2_POL | COMP2 polarity (1=Active Low, 0=Active High) |
| 4 | CMP1_POL | COMP1 polarity (1=Active Low, 0=Active High) |
| 3 | ADC_HI_PERF | ADC performance mode (1=18µs, 0=11µs) |
| 2 | CMP1_IN_SEL | COMP1 input selection (1=TEMP pin, 0=IMON pin) |
| 1 | CMP1_FLT | COMP1 fault latched/unlatched |
| 0 | CMP2_FLT | COMP2 fault latched/unlatched |

### RETRY_CONFIG (E7h)
| Bits | Name | Description |
|---|---|---|
| 7:6 | RESPONSE | 10 = Shutdown and retry |
| 5:3 | RETRY_CNT | Retry count (111=Infinite, 110=64, 101=32, 100=16, 011=8, 010=4, 001=1, 000=0/Latch) |
| 2:0 | RETRY_DLY | Retry delay timer (111=7000ms ... 000=55ms) |

### ADC_CONFIG_1 (E8h)
| Bits | Name | Description |
|---|---|---|
| 7 | EOC | End of conversion (Active Low) |
| 6 | CONVST | Software conversion start control |
| 5:4 | MODE | ADC sampling mode (00=Continuous auto sequenced, 11=Continuous single) |
| 3:0 | CONV_CH_SEL | Channel selection (0000=VIN, 0001=VOUT, 0010=IIN, 0011=VTEMP, 0100=VAUX) |

## 8. PMBus DIRECT Format Conversion Coefficients
Use the PMBus DIRECT format equation to convert telemetry to real-world values:
`X = (1/m) * (Y * 10^-R - b)` where X is the real-world value, Y is the raw digital code.

| Parameter | m | b | R |
|---|---|---|---|
| READ_VIN, READ_VIN_PEAK, MIN, AVG | 5251 | 0 | -2 |
| VIN_UV_WARN, VIN_UV_FLT, VIN_OV_WARN, VOUT_UV_WARN, VOUT_PGTH | 13128 | 0 | -3 |
| VIN_OV_FLT | 10163 | -30081 | -4 |
| READ_VOUT, READ_VOUT_AVG, MIN | 5251 | 0 | -2 |
| READ_IIN, READ_IIN_AVG, PEAK | 9538 * RIMON | 0 | -3 |
| IIN_OC_WARN | 23.8 * RIMON | 0 | -4 |
| READ_TEMPERATURE_1, AVG, PEAK | 140 | 32100 | -2 |
| OT_WARN, OT_FLT | 35 | 8006 | -2 |
| READ_VAUX, VAUX_AVG | 5251 | 0 | -1 |
| READ_PIN, READ_PIN_PEAK, AVG | 4.901 * RIMON | 0 | -4 |
| PIN_OP_WARN | 12.217 * RIMON | 0 | -5 |
| READ_EIN | 38.22 * RIMON | 0 | -7 |
| VIREF | 7111 | -2133 | -2 |
| GPDAC1 | 1333 | -8000 | -3 |
| GPDAC2 | 7111 | -2133 | -2 |
| CMP2REF, CMP1REF | 10000 | -2000 | -3 |
| CABLE_VOLTAGE_DROP | 5263 | 0 | -2 |

## 9. Functional Overview & Application Details
### Stacking Multiple eFuses
For unlimited scalability, the TPS25990 can act as a primary controller while TPS25985x devices act as secondary devices. They actively share current by configuring the ILIM and IMON pins correctly and communicating over the SWEN pin. The IMON, IREF, IN, OUT, EN/UVLO, DVDT, and SWEN pins of all parallel eFuses are tied together.

### Protections & Diagnostics
- **Circuit-Breaker & Fast-Trip:** Active transient blanking prevents false trips on spikes.
- **Blackbox Fault Recording:** Stores the last 7 critical fault events in internal RAM and external I2C EEPROM. Time intervals and tick timers reconstruct sequence of events.
- **Digital Oscilloscope:** A high-speed ADC sampling buffer stores the last 64 telemetry samples prior to a fault.
---
*Extracted specifically to assist GitHub Copilot with firmware/driver development for PIC32CM MCU.*
