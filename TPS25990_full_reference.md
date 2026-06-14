# TPS25990 Reference (Auto-extracted from PDF)

> Generated from the uploaded TPS25990 datasheet. Text was extracted page-by-page. Graphs are not reproduced as images.


---

## Page 1

TPS25990 2.9 V – 16 V, 0.79-mΩ, 60-A Stackable eFuse with PMBus® Digital Telemetry
1 Features
•
Input operating voltage range: 2.9 V to 16 V
–
20-V absolute maximum at input
–
Withstands up to –1 V at output
•
Integrated low on-resistance FET: 0.79 mΩ (typ.)
–
Rated for 50 A RMS and 60 A peak current
•
Can be used as a standalone eFuse or primary 
controller in parallel configuration
–
Supports parallel connection of multiple eFuses 
for higher current support
–
Active device state synchronization and load 
sharing during start-up and steady-state for 
unlimited scalability
•
PMBus® interface for telemetry, control, 
configuration and debug
–
PIN/EIN/VIN/VOUT/IIN/temperature/fault 
monitoring
–
Power cycle with a single command
–
On-chip non-volatile configuration memory
–
Blackbox fault recording of multiple events with 
relative time-stamp and option to store on an 
external EEPROM
•
Robust overcurrent protection
–
Programmable overcurrent threshold (IOCP): 7 A 
to 50 A with accuracy of ±5% (max.)
–
Circuit-breaker response during steady-state 
with a programmable transient blanking timer 
(OC_TIMER) to support peak load currents
–
Active current limit during start-up (ILIM)
•
Robust short-circuit protection
–
Fast-trip response (280 ns)
–
Programmable and fixed thresholds
–
Immune to supply line transients — no 
nuisance tripping
•
Programmable overtemperature protection (OTP)
–
Assured FET SOA: 8 W√s
•
Integrated FET health monitoring and reporting
•
Precise analog load current monitoring (IMON)
–
±2% accuracy
–
> 500-kHz analog bandwidth
•
Fast overvoltage protection with programmable
threshold
•
Programmable output slew rate control (dVdt)
•
Programmable insertion delay timer
•
Programmable undervoltage lockout (UVLO)
•
Analog die temperature monitor output (TEMP)
•
Four configurable general purpose I/O pins
•
Small footprint: QFN 4.5-mm × 5-mm, 0.6-mm 
pitch
–
29-mil clearance between power and GND pins
•
100% Pb Free
2 Applications
•
Server and high performance computing
•
Network interface cards
•
Graphics and hardware accelerator cards
•
Datacenter switches and routers
•
Input hotswap and hotplug
•
Fan trays
3 Description
The TPS25990 is an integrated, high-current circuit 
protection and power management device in a small 
package. The device provides multiple protection 
modes using very few external components and is a 
robust defense against overloads, short circuits, and 
excessive inrush current.
The integrated PMBus® interface allows a host 
controller to monitor, control and configure the system 
in real-time. Key system parameters can be read 
back by remote telemetry. Various protection, warning 
thresholds and coefficients can be configured through 
PMBus® or stored in non-volatile configuration 
memory. Blackbox fault recording feature helps in the 
debugging of field failures and returns.
The device can be used as a standalone eFuse, or 
connected as a primary controller in a parallel eFuse 
configuration for higher current support. All devices 
actively synchronize their operating state and share 
current during start-up and steady state to avoid over-
stressing some of the devices which can result in 
premature or partial shutdown of the parallel chain.
Package Information
PART NUMBER
PACKAGE(1)
PACKAGE SIZE
TPS25990ARQPR
RQP (QFN, 26)
4.50 mm × 5.00 mm
(1)
For all available packages, see the orderable addendum at 
the end of the data sheet.
EN/UVLO
EN/UVLO
EN/UVLO
FLT
FLT
FLT
IN
IN
OUT
IN
OUT
IMON
IMON
IMON
ILIM
ILIM
DVDT
DVDT
SUPPLY
LOAD
TPS25990x
TPS25985x
TPS25985x
TEMP
TEMP
IREF
TEMP/CMP
ILIM
DVDT
IREF/DAC2
IREF
VDD
VDD
VDD
PG
PG
PG
PG
FLT
SWEN
SWEN
SWEN
GND
GND
GND
IMON
OUT
ADDR1
AUX
SCL
SDA
SMBA#
SCL
SDA
SMBA#
ADDR0
MODE
MODE
EN
Simplified Schematic
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
An IMPORTANT NOTICE at the end of this data sheet addresses availability, warranty, changes, use in safety-critical applications, 
intellectual property matters and other important disclaimers. PRODUCTION DATA.



---

## Page 2

Table of Contents
1 Features............................................................................1
2 Applications.....................................................................1
3 Description.......................................................................1
4 Revision History.............................................................. 2
5 Description (continued).................................................. 3
6 Pin Configuration and Functions...................................4
7 Specifications.................................................................. 7
7.1 Absolute Maximum Ratings........................................ 7
7.2 ESD Ratings............................................................... 7
7.3 Recommended Operating Conditions.........................8
7.4 Thermal Information....................................................8
7.5 Electrical Characteristics.............................................9
7.6 Logic Interface DC Characteristics........................... 12
7.7 Telemetry.................................................................. 12
7.8 PMBus Interface Timing Characteristics...................14
7.9 External EEPROM Interface Timing 
Characteristics.............................................................14
7.10 Timing Requirements..............................................15
7.11 Switching Characteristics........................................16
7.12 Typical Characteristics............................................17
8 Detailed Description......................................................27
8.1 Overview...................................................................27
8.2 Functional Block Diagram.........................................28
8.3 Feature Description...................................................28
8.4 Device Functional Modes........................................116
9 Application and Implementation................................ 117
9.1 Application Information............................................117
9.2 Typical Application: 12-V, 4-kW Power Path 
Protection with PMBus® Interface in Datacenter 
Servers......................................................................122
9.3 Best Design Practices.............................................130
9.4 Power Supply Recommendations...........................131
9.5 Layout..................................................................... 132
10 Device and Documentation Support........................135
10.1 Documentation Support........................................ 135
10.2 Receiving Notification of Documentation Updates135
10.3 Support Resources............................................... 135
10.4 Trademarks...........................................................135
10.5 Electrostatic Discharge Caution............................135
10.6 Glossary................................................................135
11 Mechanical, Packaging, and Orderable 
Information.................................................................. 135
4 Revision History
NOTE: Page numbers for previous revisions may differ from page numbers in the current version.
Changes from Revision A (September 2022) to Revision B (June 2023)
Page
•
Changed device status from Advance Information to Production Data .............................................................1
•
Updated the device description.......................................................................................................................... 1
•
Revised the graphs and experimental waveforms in typical characteristics.....................................................17
•
Updated the functional block diagram.............................................................................................................. 28
•
Updated the feature description........................................................................................................................28
•
Deleted the WRITE_PROTECT (10h) register................................................................................................. 52
•
Added the MFR_WRITE_PROTECT (F8h) register......................................................................................... 52
•
Deleted the EEPROM_DET_CMD (F4h) register.............................................................................................52
•
Changed the STATUS_MFR_SPECIFIC_2 register command code from 7Fh to F3h ....................................52
•
Changed the SMBus transaction type of STATUS_MFR_SPECIFIC_2 register from Read Byte to Read Word 
..........................................................................................................................................................................52
•
Updated the default value of the MFR_REVISION (9Bh) register from 0x61 to 0x01 ..................................... 52
•
Changed the READ_BB_EEPROM register command code from BCh to F4h ...............................................52
•
Changed the CABLE_RESISTANCE register command name to CABLE_DROP ..........................................52
•
Deleted the MFR_SPECIFIC_RESERVED (B0h) register................................................................................52
•
Revised the bit definitions of the STATUS_BYTE (78h), STATUS_WORD (79h), STATUS_IN (7Ch), 
STATUS_IOUT (7Bh), STATUS_TEMP (7Dh), STATUS_MFR_SPECIFIC (80h), STATUS_MFR_SPECIFIC_2 
(F3h), STATUS_CML (7Eh), DEVICE_CONFIG (E4h), ADC_CONFIG_2 (E9h), ALERT_MASK (DBh)
registers............................................................................................................................................................52
•
Revised the Blackbox timestamp tick interval................................................................................................ 100
•
Revised the overcurrent blanking timer values...............................................................................................101
•
Revised the retry delay timer values.............................................................................................................. 102
•
Revised the insertion delay timer values.........................................................................................................110
•
Revised the ADC sampling frequency from 500 KSPS to 460 KSPS............................................................. 111
•
Added high performance ADC sampling mode...............................................................................................111
•
Updated the m, b, R coefficients used in DIRECT format conversion............................................................ 113
•
A minor modification to the application schematic..........................................................................................122
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
2
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 3

•
Revised the application performance plots.....................................................................................................129
5 Description (continued)
An integrated fast and accurate sense analog load current monitor facilitates predictive maintenance and 
advanced dynamic platform power management techniques such as Intel® PSYS and PROCHOT to maximize 
system throughput and power supply usage. This in conjunction with an integrated digital oscilloscope function 
and Blackbox, helps with predictive maintenance in critical systems.
The devices are characterized for operation over a junction temperature range of –40°C to +125°C.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
3
Product Folder Links: TPS25990



---

## Page 4

6 Pin Configuration and Functions
SCL
VIN
VIN
VIN
VIN
VOUT
VOUT
VOUT
VOUT
IREF/DAC2
ILIM
IMON
DAC1
GND
DVDT
TEMP/CMP
ADDR0
SDA
EN/UVLO
ADDR1
VDD
AUX
1
9
10
13
14
22
23
26
GPIO3/SWEN/COMP1/
COMP2/EEDATA/EECLK
GPIO1/PG/COMP1/
COMP2/EEDATA/EECLK
GPIO4/SMBA#/COMP1/
COMP2/EEDATA/EECLK
GPIO2/FLT/COMP1/
COMP2/EEDATA/EECLK
Figure 6-1. TPS25990 RQP Package 26-pin QFN Top View
Table 6-1. Pin Functions
PIN
TYPE
DESCRIPTION
NAME
NO.
ADDR1
1
O
PMBus device I2C address configuration pin. Pin strap options to generate 
different address combinations in conjunction with ADDR0. Refer to Section 
8.3.14.1 for more details.
ADDR0
2
O
PMBus device I2C address configuration pin. Pin strap options to generate 
different address combinations in conjunction with ADDR1. Refer to Section 
8.3.14.1 for more details.
AUX
3
I
Auxiliary ADC input channel which can be used to monitor external analog 
signal through PMBus. Also functions as analog input for fast comparator with 
internal programmable threshold.
DVDT
4
O
Start-up output slew rate control pin. Leave this pin open to allow fastest start-
up. Connect capacitor to ground to slow down the slew rate to manage inrush 
current. Refer to Section 8.3.4.1 for more details.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
4
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 5

Table 6-1. Pin Functions (continued)
PIN
TYPE
DESCRIPTION
NAME
NO.
TEMP/CMP
5
I/O
Dual function pin (digitally configurable)
1.
Die junction temperature monitor analog voltage output. Can be tied 
together with TEMP outputs of multiple devices in a parallel configuration to 
indicate the peak temperature of the chain. Refer to Section 8.3.8 for more 
details.
2.
Analog input for fast comparator with internal programmable threshold. 
Refer to Section 8.3.12 for more details.
DAC1
6
I/O
Programmable General Purpose DAC analog current output. Refer to Section 
8.3.14.9 for more details.
IMON
7
O
An external resistor from this pin to GND sets the overcurrent protection 
threshold and fast-trip threshold during steady-state. This pin also acts as a 
fast and accurate analog output load current monitor signal during steady-state. 
Do not leave floating. Refer to Section 8.3.6 for more details.
ILIM
8
O
An external resistor from this pin to GND sets the current limit threshold and 
fast-trip threshold during start-up. This also sets the active current sharing 
threshold during steady-state. Do not leave floating. Refer to Section 8.3.4.3 
for more details.
IREF/DAC2
9
I/O
Dual function pin (digitally configurable)
1.
Programmable reference voltage for overcurrent, short-circuit protection 
and active current sharing blocks. Generated using internal DAC. Refer to
Section 8.3.4.2 for more details.
2.
Programmable analog voltage output generated using internal general-
purpose DAC. Refer to Section 8.3.14.9 for more details.
OUT
10, 11, 12, 13
P
Power output. Must be soldered to output power plane uniformly to ensure 
proper heat dissipation and to maintain optimal current distribution through the 
device.
GND
14
G
Device ground reference pin. Connect to system ground.
SDA
15
I/O
I2C data line for PMBus interface. Refer to Section 8.3.14 for more details.
SCL
16
I/O
I2C clock line for PMBus interface. Refer to Section 8.3.14 for more details.
GPIO4/SMBA#/
COMP1/COMP2/ 
EEDATA/EECLK
17
I/O
General purpose digital I/O pin. Can be configured for various functions through 
PMBus. Refer to Section 8.3.14.7.1.59 register for more details. Default function 
is SMBus Alert output.
EN/UVLO
18
I
Active high enable input. Connect resistor divider from input supply to set the 
undervoltage threshold. Do not leave floating.
GPIO1/PG/
COMP1/COMP2/ 
EEDATA/EECLK
19
I/O
General purpose digital I/O pin. Can be configured for various functions through 
PMBus. Refer to Section 8.3.14.7.1.58 register for more details. Default function 
is Power-Good output (PG) indication. Refer to Section 8.3.10.2 for more 
details.
GPIO2/FLT/
COMP1/COMP2/ 
EEDATA/EECLK
20
I/O
General purpose digital I/O pin. Can be configured for various functions through 
PMBus. Refer to Section 8.3.14.7.1.58 register for more details. Default function 
is Fault output (FLT) indication. Refer to Section 8.3.10.1 for more details.
GPIO3/SWEN/
COMP1/COMP2/ 
EEDATA/EECLK
21
I/O
General purpose digital I/O pin. Can be configured for various functions through 
PMBus. Refer to Section 8.3.14.7.1.59 register for more details. Default pin 
function is set to SWEN, which is used to synchronize multiple eFuses in a 
parallel configuration. Refer to Section 8.3.10.3 for more details.
VDD
22
P
Controller power input pin. Can be used to power the internal control circuitry 
with a filtered and stable supply which is not affected by system transients. 
Connect this pin to VIN through a series resistor and add a decoupling capacitor 
to GND.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
5
Product Folder Links: TPS25990



---

## Page 6

Table 6-1. Pin Functions (continued)
PIN
TYPE
DESCRIPTION
NAME
NO.
IN
23, 24, 25, 26
P
Power input. Must be soldered to input power plane uniformly to ensure proper 
heat dissipation and to maintain optimal current distribution through the device.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
6
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 7

7 Specifications
7.1 Absolute Maximum Ratings
over operating free-air temperature range (unless otherwise noted)(1)
Parameter
Pin
MIN
MAX
UNIT
VINMAX
Maximum Input Voltage Range
IN
–0.3
20
V
VDDMAX
Maximum Supply Voltage Range
VDD
–0.3
20
V
VOUTMAX
Maximum Output Voltage Range
OUT
–1
Min(20, VIN + 0.3)
V
VENMAX
Maximum Enable Pin Voltage Range
EN/UVLO
20
V
VIREFMAX
Maximum IREF/DAC2 Pin Voltage Range
IREF/DAC2
5.5
V
IIREFMAX
Maximum IREF/DAC2 Pin Current
IREF/DAC2
10
mA
VAUXMAX
Maximum AUX Pin Voltage Range
AUX
5.5
V
VDVDTMAX
Maximum DVDT Pin Voltage Range
DVDT
Internally Limited
V
VI2CMAX
Maximum I2C Signal Pin Voltage Range
SCL, SDA
5.5
V
VGPIOMAX
Maximum GPIO Pin Voltage Range
GPIO1/2/3/4
5.5
V
IGPIOMAX
Maximum GPIO Pin Sink Current
GPIO1/2/3/4
10
mA
VDAC2MAX
Maximum DAC2 Output Voltage Range
IREF/DAC2
Internally Limited
V
VADDRMAX Maximum ADDR0/1 Pin Voltage Range
ADDR0/1
Internally Limited
V
IADDRMAX
Maximum ADDR0/1 Pin Sink Current 
ADDR0/1
Internally Limited
µA
IDAC1MAX
Maximum DAC1 Pin Current
DAC1
 
Internally Limited
mA
VTEMPMAX
Maximum TEMP/CMP Pin Voltage Range
TEMP/CMP
5.5
V
VILIMMAX
Maximum ILIM pin voltage
ILIM
Internally Limited
V
VIMONMAX
Maximum IMON pin voltage
IMON
Internally Limited
V
IMAX
Maximum Continuous Switch Current
IN to OUT
Internally Limited
A
TJMAX
Junction temperature
Internally Limited
°C
TLEAD
Maximum Soldering Temperature
300
°C
TSTG
Storage temperature
–65
150
°C
(1)
Operation outside the Absolute Maximum Ratings may cause permanent device damage. Absolute Maximum Ratings do not imply 
functional operation of the device at these or any other conditions beyond those listed under Recommended Operating Conditions. 
If used outside the Recommended Operating Conditions but within the Absolute Maximum Ratings, the device may not be fully 
functional, and this may affect device reliability, functionality, performance, and shorten the device lifetime.
7.2 ESD Ratings
VALUE
UNIT
V(ESD)
Electrostatic discharge
Human body model (HBM), per ANSI/ESDA/
JEDEC JS-001(1)
±2000
V
Charged device model (CDM), per ANSI/ESDA/
JEDEC JS-002(2)
±500
(1)
JEDEC document JEP155 states that 500-V HBM allows safe manufacturing with a standard ESD control process.
(2)
JEDEC document JEP157 states that 250-V CDM allows safe manufacturing with a standard ESD control process.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
7
Product Folder Links: TPS25990



---

## Page 8

7.3 Recommended Operating Conditions
over operating free-air temperature range (unless otherwise noted)
Parameter
Pin
MIN
MAX
UNIT
VIN
Input Voltage Range
IN
2.9
16
V
VDD
Supply Voltage Range (with in-system NVM programming 
support)
VDD
10
16
V
VDD
Supply Voltage Range (without in-system NVM 
programming support)
VDD
4.5
16
V
VOUT
Output Voltage Range
OUT
VIN
V
VEN/
UVLO
Enable Pin Voltage Range
EN/UVLO
Min(VDD + 1, VIN + 1)
V
VDVDT
DVDT Pin Cap Voltage Rating
DVDT
4
V
VI2C
I2C Pull-up Voltage Range
SCL, SDA
1.8
5
V
CI2C
I2C Parasitic Capacitance
SCL, SDA
200
pF
VGPIO
GPIOx Pin Pull-up Voltage Range
GPIO1/2/3/4
5
V
VIREF
IREF Pin Voltage Range
IREF/DAC2
0.3
1.2
V
VILIM
ILIM Pin Voltage Range
ILIM
0.4
V
VIMON
IMON Pin Voltage Range
IMON
1.2
V
VTEMPC
MP
TEMP/CMP Pin Voltage Range
TEMP/CMP
1.2
V
VAUX
AUX Pin Voltage Range
AUX
1.2
V
IMAX
RMS Switch Current, TJ ≤ 125 ℃
IN to OUT
50
A
IMAX, PLS Peak Output Current with 20% duty cycle, TJ ≤ 125 ℃
IN to OUT
60
A
TJ
Junction temperature
–40
125
°C
7.4 Thermal Information
THERMAL METRIC(1) (2)
TPS25990X
UNIT
RQP (QFN)
26 PINS
RθJA 
Junction-to-ambient thermal resistance
19.9
°C/W
ΨJT
Junction-to-top characterization parameter
0.2
°C/W
ΨJB
Junction-to-board characterization parameter
4.2
°C/W
(1)
For more information about traditional and new thermal metrics, see the Semiconductor and IC Package Thermal Metrics application 
report.
(2)
Based on simulations conducted with the device mounted on a JEDEC 8-layer PCB (4s4p)
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
8
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 9

7.5 Electrical Characteristics
(Test conditions unless otherwise noted) –40°C ≤ TJ ≤ 125°C, VIN = 12 V, VDD = 12 V, OUT = Open, VEN/UVLO = 2 V, SWEN 
= 10 kΩ pull-up to 5 V, RILIM = 550 Ω, RIMON = 1.1 kΩ, DVDT = Open, FLT = 10 kΩ pull-up to 5 V, PG = 10 kΩ pull-up to 5 V, 
TEMP = Open, ADDR0 = Open, ADDR1 = Open, SCL, SDA and SMBA# pulled up to 3.3 V. All voltages referenced to GND. 
PARAMETER
TEST CONDITIONS
MIN
TYP MAX UNIT
INPUT SUPPLY (VDD)
VDD
VDD input operating voltage range
4.5
16
V
IQON(VDD)
VDD ON state quiescent current
VVDD > VUVP(R), VEN ≥ VUVLO(R)
3.7
5.5
mA
IQOFF(VDD)
VDD OFF state current 
VSD(R) < VEN < VUVLO(F)
3.7
5.5
mA
ISD(VDD)
VDD shutdown current
VEN < VSD(F)
4
6
mA
VUVP(R)
VDD undervoltage protection threshold
VDD Rising
4
4.26
4.5
V
VUVP(F)
VDD undervoltage protection threshold
VDD Falling
3.9
4.07
4.4
V
INPUT SUPPLY (IN)
VIN
VIN input operating voltage range
2.9
16
V
VUVPIN(R)
VIN undervoltage protection threshold
2.71
2.81
2.91
V
VUVPIN(F)
VIN undervoltage protection threshold
2.59
2.59
2.60
V
VUVLOIN(R)
VIN undervoltage protection threshold
VIN Rising, VIN_UV_FLT = 0x8D (Default 
register value)
10.8
2 11.02 11.17
V
VUVLOIN(F)
VIN undervoltage protection threshold
VIN Falling, VIN_UV_FLT = 0x8D (Default 
register value)
10.5
2 10.78
10.9
7
V
IQON(IN)
IN ON state quiescent current
VEN ≥ VUVLO(R)
2.6
3.5
mA
IQOFF(IN)
IN OFF state current  
VSD(R) < VEN < VUVLO(F)
2.6
3.5
mA
ISD(IN)
IN shutdown current
VEN < VSD(F)
2.7
3.5
mA
ENABLE / UNDERVOLTAGE LOCKOUT (EN/UVLO)
VUVLO(R)
EN/UVLO pin voltage threshold for turning 
on, rising
EN/UVLO  Rising
1.12
1.2
1.28
V
VUVLO(F)
EN/UVLO pin voltage threshold for turning 
off and engaging QOD, falling
EN/UVLO Falling
1.02
1.1
1.18
V
VSD(F)
Shutdown threshold
EN/UVLO Falling
0.6
V
IENLKG
EN/UVLO pin leakage current
VEN < Min(VIN + 1 V, VDD + 1 V)
0.1
µA
OVERVOLTAGE PROTECTION (IN)
VOVP(R)
VIN overvoltage protection threshold (rising)
VIN_OV_FLT = 0x0E (Default setting), VIN 
rising
16.3
9 16.73
17.0
8
V
VOVP(F)
VIN overvoltage protection threshold (rising)
VIN_OV_FLT = 0x0E (Default setting), VIN 
falling
16.1 16.48
16.8
V
VOVP(R)
VIN overvoltage protection threshold (rising)
VIN_OV_FLT = 0x0B, VIN rising
13.3
2 13.74
14.1
5
V
VOVP(F)
VIN overvoltage protection threshold (falling) VIN_OV_FAULT = 0x0B, VIN falling
13.1 13.49
13.8
9
V
VOVP(R)
VIN overvoltage protection threshold (falling) VIN_OV_FAULT = 0x01, VIN rising
3.77
3.94
4.15
VOVP(F)
VIN overvoltage protection threshold (falling) VIN_OV_FAULT = 0x01. VIN falling
3.53
3.69
3.86
ON-RESISTANCE (IN - OUT)
RON
ON resistance
TJ = 25 ℃
0.79
1.05
mΩ
RON
ON resistance
TJ = –40 to 125 ℃
1.4
mΩ
OUTPUT CURRENT MONITOR AND OVERCURRENT PROTECTION (IMON)
GIMON
Current Monitor Gain (IMON:IOUT)
Device in steady state (PG asserted)
17.8
7 18.18
18.5
5 µA/A
ILKG(IMON)
IMON pin leakage/offset current
1.1
uA
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
9
Product Folder Links: TPS25990



---

## Page 10

7.5 Electrical Characteristics (continued)
(Test conditions unless otherwise noted) –40°C ≤ TJ ≤ 125°C, VIN = 12 V, VDD = 12 V, OUT = Open, VEN/UVLO = 2 V, SWEN 
= 10 kΩ pull-up to 5 V, RILIM = 550 Ω, RIMON = 1.1 kΩ, DVDT = Open, FLT = 10 kΩ pull-up to 5 V, PG = 10 kΩ pull-up to 5 V, 
TEMP = Open, ADDR0 = Open, ADDR1 = Open, SCL, SDA and SMBA# pulled up to 3.3 V. All voltages referenced to GND. 
PARAMETER
TEST CONDITIONS
MIN
TYP MAX UNIT
IOCP
Steady-state overcurrent protection (Circuit-
Breaker) threshold
RIMON = 1.1 kΩ, VIREF = 1 V
48.3
50
51.7
A
RIMON = 1.1 kΩ, VIREF = 0.5 V
24
25
26
A
RIMON = 1.1 kΩ, VIREF = 0.3 V
14.4
15
15.6
A
RIMON = 7.87 kΩ, VIREF = 0.1 V
6.72
7
7.28
A
CURRENT LIMIT (ILIM)
GILIM(LIN)
Current Monitor Gain (ILIM:IOUT) vs. IOUT.
Device in steady state (PG asserted)
17.8
7 18.18
18.5
5 µA/A
CLREF(SAT)
Ratio of start-up current limit reference 
to steady-state circuit-breaker reference 
threshold
VOUT > VFB, PG not asserted
23.33
%
ILIM
Start-up current limit regulation threshold 
RILIM = 314 Ω, VIREF = 1.182 V, VOUT > VFB
28
35
43.5
A
RILIM = 1.1 kΩ, VIREF = 1.182 V, VOUT > VFB
9.8
14
18.2
A
RILIM = 1.54 kΩ, VIREF = 1.182 V, VOUT > 
VFB
7
10
13
A
VFB
Foldback voltage
1.5
2.0
2.5
V
CURRENT LIMIT REFERENCE (IREF/DAC2)
VIREF
Current Limit Reference DAC output 
voltage
VIREF = 0x32 
(Default), DEVICE_CONFIG[6] = 0
0.99
1.0
1.01
V
VIREF = 0x00, DEVICE_CONFIG[6] = 0
0.29
0.3
0.31
V
VIREF = 0x3F, DEVICE_CONFIG[6] = 0
1.17 1.182
1.19
V
DAC2 OUTPUT (IREF/DAC2)
VDAC2
General purpose DAC 2 output voltage
GPDAC2 = 0x00, DEVICE_CONFIG[6] = 1
291
300
308
mV
GPDAC2 = 0x1F, DEVICE_CONFIG[6] = 1
725
733
742
mV
GPDAC2 = 0x3F, DEVICE_CONFIG[6] = 1
1174
1180
1189
mV
DAC1 OUTPUT
IDAC1
General purpose DAC 1 sink current
GPDAC1[6:0] = 0000000b
5.66
5.98
6.28
µA
GPDAC1[6:0] = 0011111b
27.7
2 29.21
30.5
7
µA
GPDAC1[6:0] = 0111111b
50.5
2 53.19
55.5
6
µA
GPDAC1[6:0] = 1xxxxxxb
0.05
µA
SHORT-CIRCUIT PROTECTION
IFFT
Fixed fast-trip threshold
PG asserted High 
90 113.2
158.
8
A
SFTREF(LIN)
Scalable fast-trip threshold (IMON) to 
overcurrent protection threshold reference 
(IREF) ratio during steady-state
DEVICE_CONFIG[12:11] = 11
225
%
DEVICE_CONFIG[12:11] = 10
200
%
DEVICE_CONFIG[12:11] = 01
175
%
DEVICE_CONFIG[12:11] = 00
150
%
SFTREF(SAT)
Scalable fast-trip threshold (ILIM) to 
overcurrent protection threshold reference 
(IREF) ratio during inrush
50
%
ACTIVE CURRENT SHARING
RON(ACS)
Maximum RON during steady-state active 
current sharing
VILIM > CLREF(ACS)% × VIREF
1
1.81
mΩ
GIMON(ACS)
IMON:IOUT ratio during active current 
sharing
PG asserted High,  VILIM > CLREF(ACS)% × 
VIREF
18.0 18.36
18.7
7 µA/A
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
10
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 11

7.5 Electrical Characteristics (continued)
(Test conditions unless otherwise noted) –40°C ≤ TJ ≤ 125°C, VIN = 12 V, VDD = 12 V, OUT = Open, VEN/UVLO = 2 V, SWEN 
= 10 kΩ pull-up to 5 V, RILIM = 550 Ω, RIMON = 1.1 kΩ, DVDT = Open, FLT = 10 kΩ pull-up to 5 V, PG = 10 kΩ pull-up to 5 V, 
TEMP = Open, ADDR0 = Open, ADDR1 = Open, SCL, SDA and SMBA# pulled up to 3.3 V. All voltages referenced to GND. 
PARAMETER
TEST CONDITIONS
MIN
TYP MAX UNIT
CLREF(ACS)
Ratio of active current sharing trigger 
threshold to steady state overcurrent 
protection threshold
PG asserted High
36.67
%
INRUSH CURRENT PROTECTION (DVDT)
IDVDT
dVdt pin charging current
DEVICE_CONFIG[10:9] = 11
2.38
3
4
µA
DEVICE_CONFIG[10:9] = 10
1.4
2
2.9
µA
DEVICE_CONFIG[10:9] = 01
1
1.5
2
µA
DEVICE_CONFIG[10:9] = 00
0.79
1
1.33
µA
GDVDT
dVdt gain
20.7
V/V
RDVDT
dVdt pin to GND discharge resistance
510
Ω
GHI
RON(GHI)
RON when PG is asserted
1
1.81
mΩ
QUICK OUTPUT DISCHARGE (QOD)
IQOD
Quick output discharge internal pull-down 
current on OUT
VSD(F) < VEN < VUVLO(F)
10.8
22.1
38
mA
OVERTEMPERATURE PROTECTION (OTP)
TSD
Thermal shutdown threshold
TJ Rising
149
°C
TSDHYS
Thermal shutdown hysteresis
TJ Falling
11
°C
TEMPERATURE SENSOR OUTPUT (TEMP/CMP)
GTMP
TEMP sensor gain
2.58
2.65
2.72
mV/
℃
VTMP
TEMP pin output voltage
TJ = 25 ℃
672
678
685
mV
ITMPSRC
TEMP pin sourcing current
75
93.4 115.6
µA
ITMPSNK
TEMP pin sinking current
7.6
10
14
µA
COMPARATORS (TEMP/CMP, AUX)
ICMPLKG
TEMP/CMP input leakage current
0 ≤ VTEMP/CMP ≤ 1.2 V, TEMP/CMP pin 
configured as comparator 1 input
1
µA
IAUXLKG
AUX input leakage current
0 ≤ VAUX ≤ 1.2 V
1
µA
VCMP1REF
Comparator 1 reference voltage
VCMPXREF[3:0] = 0000
176 199.5
224
mV
VCMPXREF[3:0] = 0011
476 501.8
524
mV
VCMPXREF[3:0] = 0111
876 900.4
923
mV
VCMPXREF[3:0] = 1111
1676 1700.
4 1722
mV
VCMP2REF
Comparator 2 reference voltage
VCMPXREF[7:4] = 0000
176 199.4
224
mV
VCMPXREF[7:4] = 0011
476 500.1
524
mV
VCMPXREF[7:4] = 0111
876 899.7
923
mV
VCMPXREF[7:4] = 1111
1677 1699.
2 1722
mV
FET HEALTH MONITOR
VDSFLT
FET D-S Fault Threshold
SWEN = L
0.35
0.49
0.59
V
ADDRESS SELECT (ADDR0/1)
IADDR
ADDR0 pin pull-up current
3.85
5.05
6.25
µA
ADDR1 pin pull-up current
3.85
5.05
6.25
µA
SINGLE POINT FAILURE (ILIM, IMON, IREF)
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
11
Product Folder Links: TPS25990



---

## Page 12

7.5 Electrical Characteristics (continued)
(Test conditions unless otherwise noted) –40°C ≤ TJ ≤ 125°C, VIN = 12 V, VDD = 12 V, OUT = Open, VEN/UVLO = 2 V, SWEN 
= 10 kΩ pull-up to 5 V, RILIM = 550 Ω, RIMON = 1.1 kΩ, DVDT = Open, FLT = 10 kΩ pull-up to 5 V, PG = 10 kΩ pull-up to 5 V, 
TEMP = Open, ADDR0 = Open, ADDR1 = Open, SCL, SDA and SMBA# pulled up to 3.3 V. All voltages referenced to GND. 
PARAMETER
TEST CONDITIONS
MIN
TYP MAX UNIT
IOC_BKP(LIN)
Back-up overcurrent protection threshold 
(steady -state)
65
90
131
A
IOC_BKP(SAT)
Back-up overcurrent protection threshold 
(start-up)
55
90
112
A
7.6 Logic Interface DC Characteristics
over operating free-air temperature range (unless otherwise noted)
PARAMETER
TEST CONDITIONS
MIN
TYP
MAX
UNIT
GPIOx
VOL
GPIOx output logic low
Pin configured as output, de-asserted 
Low. Sink current = 20 mA.
0.27
V
VOH
GPIOx output logic high 
Pin configured as output, asserted 
high
1.7
V
VIH
GPIOx input logic high
Pin configured as input
1.65
V
VIL
GPIOx input logic low
Pin configured as input
0.75
V
RGPIO
GPIOx pin pull-down resistance 
Pin configured as output, de-asserted 
Low
13
Ω
IGPIOLKG
GPIOx pin leakage current
Pin configured as output, asserted 
high
1
µA
PMBus (SCL/SDA)
CPMB-BUS
PMBus Bus Capacitance
400
pF
CPMB-PIN
PMBus Pin Capacitance - SCL
10
pF
CPMB-PIN
PMBus Pin Capacitance - SDA
10
pF
VPULLUP_PMBus
PMBus interface pull ups
1.62
3.63
V
VIL_PMBus
SDA Input logic low
0.85
V
VIL_PMBus
SCL Input logic low
0.85
V
VIH_PMBus
SCL Input logic high
1.35
V
VIH_PMBus
SDA Input logic high
1.35
V
VOL_PMBus
Low-level output voltage - SCL
IOL = -20 mA
0.4
V
VOL_PMBus
Low-level output voltage - SDA
IOL = -20 mA
0.4
V
7.7 Telemetry
over operating free-air temperature range (unless otherwise noted)
PARAMETER
TEST CONDITIONS
MIN
TYP
MAX
UNIT
Telemetry
ADC Resolution
10
bits
ADC Voltage reference (VREF)
1.95
V
Analog Input Range
0
VREF
V
Sampling rate
ADC normal mode (Default)
460
KHz
ADC high performance mode 
(DEVICE_CONFIG[3] = 1)
270
KHz
DNL
ADC normal mode (Default)
4
LSB
ADC high performance mode 
(DEVICE_CONFIG[3] = 1)
0.75
LSB
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
12
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 13

7.7 Telemetry (continued)
over operating free-air temperature range (unless otherwise noted)
PARAMETER
TEST CONDITIONS
MIN
TYP
MAX
UNIT
INL
ADC normal mode (Default)
6
LSB
ADC high performance mode 
(DEVICE_CONFIG[3] = 1)
2.9
LSB
VAUX Absolute error
ADC normal mode (Default), VAUX = 1.95 V 
(Full-scale), 1 sample
–1.5
1.5
%FS
ADC high performance mode 
(DEVICE_CONFIG[3] = 1), VAUX = 1.95 V 
(Full-scale), 1 sample
–1
1
%FS
ADC normal mode (Default), VAUX = 1.95 V 
(Full-scale), 128 sample average
–1
1
%FS
ADC high performance mode 
(DEVICE_CONFIG[3] = 1), VAUX = 1.95 V 
(Full-scale), 128 sample average
–0.5
0.5
%FS
VIN Absolute error
ADC high performance mode 
(DEVICE_CONFIG[3] = 1), VIN = 12 V, 1 
sample
–1.5
1.5
%FS
ADC high performance mode 
(DEVICE_CONFIG[3] = 1), VIN = 12 V, 128 
sample average
–0.75
0.75
%FS
VOUT Absolute error
ADC high performance mode 
(DEVICE_CONFIG[3] = 1), VOUT = 12 V, 1 
sample
–1.5
1.5
%FS
ADC high performance mode 
(DEVICE_CONFIG[3] = 1), VOUT = 12 V, 
128 sample average
–0.75
0.75
%FS
VTEMP Absolute error
ADC high performance mode 
(DEVICE_CONFIG[3] = 1), VTEMP = 1.95 V 
(Full-scale) , 1 sample
–10
10
℃
ADC high performance mode 
(DEVICE_CONFIG[3] = 1), VTEMP = 1.95 V 
(Full-scale), 128 sample average
–8
8
℃
IMON Absolute error
ADC high performance mode 
(DEVICE_CONFIG[3] = 1), VIMON = 0.8 V, 
1 sample
–1
1
%FS
ADC high performance mode 
(DEVICE_CONFIG[3] = 1), VIMON = 0.8 V, 
128 sample average
–0.5
0.5
%FS
PIN Absolute error
ADC high performance mode 
(DEVICE_CONFIG[3] = 1), VIN = 12 V, 
VIMON = 1.95 V (Full-scale), 1 sample
–2
2
%FS
ADC high performance mode 
(DEVICE_CONFIG[3] = 1), VIN = 12 V, 
VIMON = 1.95 V (Full-scale) , 128 sample 
average
–1.25
1.25
%FS
EIN absolute error
ADC high performance mode 
(DEVICE_CONFIG[3] = 1), Accumulated 
energy over 5 ms interval, VIN = 12 V, 
VIMON = 0.8 V
–2.5
2.5
%
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
13
Product Folder Links: TPS25990



---

## Page 14

7.8 PMBus Interface Timing Characteristics
over operating free-air temperature range (unless otherwise noted)
 
PARAMETER
TEST CONDITIONS
MIN
TYP
MAX
UNIT
PMBus Timing Characteristics
PMBCLKR
PMBus clock frequency range
PMBus Clock Requirements
0.05
1.2
MHz
tPMB-BUF
PMBus Free time between STOP and 
START conditions
0.5
µs
tPMB-HD-STA
Hold time after Repeated Start Condition
0.26
µs
tPMB-SU-STO
Stop condition Setup time
0.26
µs
tPMB-HD-DAT
SDA Hold Time
0
µs
tPMB-SU-DAT
SDA Setup Time
50
ns
tPMB-TIMEOUT
SCLK low timeout
25
35
ms
tPMB-LOW
SCLK low time
0.5
µs
tPMB-HIGH
SCLK high time
0.26
50
µs
tR-PMB
SDA/SCLK rise time
(VIL(MAX)-150 mV to VIH(MIN)+150 mV)
100 kHz Class
300
ns
400 kHz Class
300
ns
1000 kHz Class
120
ns
tF-PMB
SDA/SCLK fall time,
(VIH(MIN)+150 mV to VIL(MAX) + 150 mV)
100 kHz Class
1000
ns
400 kHz Class
300
ns
1000 kHz Class
120
ns
7.9 External EEPROM Interface Timing Characteristics
over operating free-air temperature range (unless otherwise noted)
 
PARAMETER
TEST CONDITIONS
MIN
TYP
MAX
UNIT
EE Interface Timing Characteristics
EECLKR
EECLK clock frequency range
0.4
MHz
tEE-SU-STO
Stop condition Setup time
0.26
µs
tEE-HD-DAT
EEDATA Hold Time
0
µs
tEE-SU-DAT
EEDATA Setup Time
50
ns
tHD-STA
Hold time after (REPEATED) START 
Condition
0.6
µs
tEE-LOW
EECLK low time
0.5
µs
tEE-HIGH
EECLK high time
0.26
50
µs
tR-EE
EEDATA/EECLK rise time
(VIL(MAX)-150 mV to VIH(MIN)+150 mV)
400 kHz Class
300
ns
tF-EE
EEDATA/EECLK fall time,
(VIH(MIN)+150 mV to VIL(MAX) + 150 mV)
400 kHz Class
300
ns
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
14
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 15

7.10 Timing Requirements
PARAMETER
TEST CONDITIONS
MIN
TYP
MAX
UNIT
tOVP
Overvoltage protection response time
VIN > VOVP(R) to SWEN↓ 
1.2
µs
tInsdly
Insertion delay
VDD > VUVP(R) to SWEN↑, INS_DLY = 
0x00
14
ms
VDD > VUVP(R) to SWEN↑, INS_DLY = 
0x07
560
ms
tFFT
Fixed Fast-Trip response time Hard 
Short
IOUT > 1.3 × IFFT to IOUT↓
267
ns
tSFT
Scalable Fast-Trip response time
IOUT > 3 × IOCP to IOUT↓
343
ns
tCMP1
TEMP/CMP pin comparator (COMP1) 
response time
VCMP1THR = 1 V, VTEMP/CMP > 1.2 × 
VCMP1THR to CMP1OUT↑ 
377
ns
tCMP2
AUX pin comparator (COMP2) 
response time
VCMP2THR = 1 V, VAUX > 1.2 × 
VCMP1THR to CMP2OUT↑
377
ns
tOC_TIMER
Overcurrent blanking interval 
IOUT = 1.3 × IOCP, OC_TIMER = 0x00
0
ms
IOUT = 1.3 × IOCP, OC_TIMER = 0x14 
(Default)
2.1
ms
IOUT = 1.3 × IOCP, OC_TIMER = 0xFF
27.3
ms
tRETRY
Auto-Retry Interval
RETRY_CONFIG[2:0] = 000
55
ms
RETRY_CONFIG[2:0] = 111
6940
ms
tEN(DG)
EN/UVLO de-glitch time
12.2
µs
tSU_TMR
Start-up timeout interval
SWEN↑ to FLT↓  
232
ms
tQOD
QOD enable timer
VSD(F) < VEN/UVLO < VUVLO(F)
4.38
ms
tDischarge
QOD discharge time (90% to 10% of 
VOUT)
VSD(F) < VEN/UVLO < VUVLO(F), VIN = 12 
V, COUT = 1 mF
488
ms
tPGA
PG assertion delay
DEVICE_CONFIG[15] = 0, Device in 
steady state, VOUT > VOUT_PGTH to 
PG↑
98
µs
tPGA
PG assertion delay
DEVICE_CONFIG[15] = 1, Device in 
steady state, VOUT > VOUT_PGTH to 
PG↑
36.6
ms
tPGD
PG De-assertion de-glitch
Device in steady state, VOUT < 
VOUT_PGTH to PG↓
34
µs
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
15
Product Folder Links: TPS25990



---

## Page 16

7.11 Switching Characteristics
The output rising slew rate is internally controlled and constant across the entire operating voltage range to ensure the 
turn on timing is not affected by the load conditions. The rising slew rate can be adjusted by adding capacitance from 
the dVdt pin to ground. As CdVdt is increased it will slow the rising slew rate (SR). See Slew Rate and Inrush Current 
Control (dVdt) section for more details. The Turn-Off Delay and Fall Time, however, are dependent on the RC time constant 
of the load capacitance (COUT) and Load Resistance (RL). The Switching Characteristics are only valid for the power-up 
sequence where the supply is available in steady state condition and the load voltage is completely discharged before the 
device is enabled. Typical values are taken at TJ = 25°C unless specifically noted otherwise. VIN = 12 V, ROUT = 500 Ω, COUT 
= 1 mF 
PARAMETER
CdVdt = 22 nF, 
DEVICE_CONF
IG[10:9] = 10
CdVdt = 22 nF, 
DEVICE_CONF
IG[10:9] = 00
CdVdt = 22 nF, 
DEVICE_CONF
IG[10:9] = 11
CdVdt = 33 nF, 
DEVICE_CONF
IG[10:9] = 10
CdVdt = 33 nF, 
DEVICE_CONF
IG[10:9] = 00
CdVdt = 33 nF, 
DEVICE_CONF
IG[10:9] = 11
UNITS
SRON
Output rising 
slew rate
1.99
0.96
2.92
1.34
0.66
2.01
V/ms
tD,ON 
Turn on delay
1.47
2.99
0.98
2.19
4.37
1.42
ms
tR
Rise time
5.07
10.36
3.41
7.40
15.2
4.94
ms
tON
Turn on time
6.55
13.36
4.39
9.53
19.57
6.36
ms
tD,OFF
Turn off delay
1.1
1.1
1.1
1.1
1.1
1.1
ms
tF
Fall time
Depends on ROUT and COUT
ms
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
16
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 17

7.12 Typical Characteristics
TA (C)
RON ()
-40
-20
0
20
40
60
80
100
120
140
600
650
700
750
800
850
900
950
1000
1050
1100
VIN (V)
3.3
12
16
Figure 7-1. ON Resistance Across Temperature
TA (C)
VUVP (V)
-40
-20
0
20
40
60
80
100
120
140
0
0.5
1
1.5
2
2.5
3
3.5
4
4.5
Rising
Falling
Hysteresis
Figure 7-2. VDD Undervoltage Thresholds Across Temperature
TA (C)
VUVPIN (V)
-40
-20
0
20
40
60
80
100
120
140
0
0.3
0.6
0.9
1.2
1.5
1.8
2.1
2.4
2.7
3
Rising
Falling
Hysteresis
Figure 7-3. VIN Undervoltage Thresholds Across Temperature
TA (C)
VUVLOIN (V)
-40
-20
0
20
40
60
80
100
120
140
0
0.5
1
1.5
2
2.5
3
3.5
4
4.5
5
Rising
Falling
Hysteresis
Figure 7-4. VIN Undervoltage Thresholds Across Temperature 
(VIN_UV_FLT = 0x38)
Figure 7-5. VIN Undervoltage Thresholds Across Temperature 
(VIN_UV_FLT = 0x8D)
TA (C)
VOVP (V)
-40
-20
0
20
40
60
80
100
120
140
0
2
4
6
8
10
12
14
16
18
Rising
Falling
Hysteresis
Figure 7-6. VIN Overvoltage Protection Threshold Across 
Temperature (VIN_OV_FLT = 0x0E (Default))
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
17
Product Folder Links: TPS25990



---

## Page 18

7.12 Typical Characteristics (continued)
TA (C)
VOVP (V)
-40
-20
0
20
40
60
80
100
120
140
0
0.5
1
1.5
2
2.5
3
3.5
4
Rising
Falling
Hysteresis
Figure 7-7. VIN Overvoltage Protection Threshold Across 
Temperature (VIN_OV_FLT = 0x01)
TA (C)
VOVP (V)
-40
-20
0
20
40
60
80
100
120
140
0
2
4
6
8
10
12
14
Rising
Falling
Hysteresis
Figure 7-8. VIN Overvoltage Protection Threshold Across 
Temperature (VIN_OV_FLT = 0x0B)
TA (C)
VUVLO (V)
-40
-20
0
20
40
60
80
100
120
140
0
0.2
0.4
0.6
0.8
1
1.2
1.4
Rising
Falling
Hysteresis
Figure 7-9. EN/UVLO Based Turn-off Thresholds Across 
Temperature
TA (C)
VSD (V)
-40
-20
0
20
40
60
80
100
120
140
0.78
0.8
0.82
0.84
0.86
0.88
0.9
0.92
Rising
Falling
Figure 7-10. EN/UVLO Based Shutdown Thresholds Across 
Temperature
TA (C)
GIMON (A/A)
-40
-20
0
20
40
60
80
100
120
140
18.1
18.13
18.16
18.19
18.22
18.25
18.28
18.31
IOUT (A)
15
20
35
Figure 7-11. IMON Gain Across Load and Temperature
IOUT (A)
GIMON Error (%)
14
16
18
20
22
24
26
28
30
32
34
36
-2
-1.5
-1
-0.5
0
0.5
1
1.5
2
2.5
Max
Typ
Min
Figure 7-12. IMON Gain Accuracy Across Process, Voltage and 
Temperature Corners
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
18
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 19

7.12 Typical Characteristics (continued)
VIREF Decimal Code
VIREF (V)
0
5
10
15
20
25
30
35
40
45
50
55
60 63
0.3
0.4
0.5
0.6
0.7
0.8
0.9
1
1.1
1.2
TA (C)
-40
25
125
Figure 7-13. VIREF DAC Transfer Function
IOCP (A)
IOCP Error (%)
5
10
15
20
25
30
35
40
45
50
-6
-4
-2
0
2
4
6
Min
Typ
Max
Figure 7-14. Steady-state Overcurrent Protection Threshold 
(Circuit-Breaker) Accuracy
TA (C)
GILIM (A/A)
-40
-20
0
20
40
60
80
100
120
140
18
18.03
18.06
18.09
18.12
18.15
18.18
18.21
18.24
18.27
18.3
Figure 7-15. ILIM Gain Across Load and Temperature
ILIM (A)
ILIM Error (%)
5
10
15
20
25
30
35
40
45
-35
-30
-25
-20
-15
-10
-5
0
5
10
15
20
25
30
35
Min
Typ
Max
Figure 7-16. Startup Overcurrent Protection Threshold (Current 
Limit) Accuracy
TA (C)
SFTREF(LIN)
-40
-20
0
20
40
60
80
100
120
140
1
1.5
2
2.5
3
3.5
4
DEVICE_CONFIG[12:11]
11
10
01
00
Figure 7-17. Scalable Fast-trip Threshold Ratio Across 
Temperature (Steady-state)
TA (C)
SFTREF(SAT)
-40
-20
0
20
40
60
80
100
120
140
0.49
0.491
0.492
0.493
0.494
0.495
0.496
0.497
0.498
0.499
0.5
Figure 7-18. Scalable Fast-trip Threshold Ratio Across 
Temperature (Startup)
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
19
Product Folder Links: TPS25990



---

## Page 20

7.12 Typical Characteristics (continued)
TA (C)
IFFT (A)
-40
-20
0
20
40
60
80
100
120
140
108
109
110
111
112
Figure 7-19. Fixed Fast-trip Threshold Across Temperature
Figure 7-20. Backup Overcurrent Protection Threshold (Startup) 
Accuracy
TA (C)
IOC_BKP(LIN) (A)
-40
-20
0
20
40
60
80
100
120
140
88
88.5
89
89.5
90
90.5
91
91.5
92
Figure 7-21. Backup Overcurrent Protection Threshold (Steady-
state) Accuracy
TA (C)
IDVDT (A)
-40
-20
0
20
40
60
80
100
120
140
1
1.25
1.5
1.75
2
2.25
2.5
2.75
3
3.25
DEVICE_CONFIG[10:9]
11
10
01
00
Figure 7-22. DVDT Pin Charging Current Across Temperature
TA (C)
GDVDT (V/V)
-40
-20
0
20
40
60
80
100
120
140
20.66
20.68
20.7
20.72
20.74
20.76
20.78
20.8
Figure 7-23. DVDT Gain Across Temperature
ADC Digital Code
INL (LSB)
0
128
256
384
512
640
768
896
1024
-3
-2.5
-2
-1.5
-1
-0.5
0
0.5
1
ADC high performance mode (DEVICE_CONFIG[3] = 1)
Figure 7-24. ADC INL
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
20
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 21

7.12 Typical Characteristics (continued)
ADC Output Code
Code Occurrence
0
1000
2000
3000
4000
5000
6000
7000
8000
9000
10000
507
508
509
510
511
512
513
514
515
ADC Sampling Mode
Normal Mode No Averaging
Normal Mode 128 Sample Averaging
High Performance Mode No Averaging
High Performance Mode 128 Sample Averaging
Figure 7-25. ADC Histogram (Mid-scale Analog Input)
GPDAC1 Decimal Code
IDAC1 (A)
0
5
10
15
20
25
30
35
40
45
50
55
60
65
5
10
15
20
25
30
35
40
45
50
55
TA (C)
-40
25
125
Figure 7-26. General Purpose DAC1 Transfer Function
GPDAC2 Decimal Code
VDAC2 (V)
0
5
10
15
20
25
30
35
40
45
50
55
60 63
0.3
0.4
0.5
0.6
0.7
0.8
0.9
1
1.1
1.2
TA (C)
-40
25
125
Figure 7-27. General Purpose DAC2 Transfer Function
VCMPXREF Decimal Code
VCMPxREF (V)
0
2
4
6
8
10
12
14
16
0
0.2
0.4
0.6
0.8
1
1.2
1.4
1.6
1.8
TA (C)
-40
25
125
Figure 7-28. General Purpose Comparators Reference DAC 
Transfer Function
TA (C)
General Purpose Input Logic Levels (V)
-40
-20
0
20
40
60
80
100
120
140
0.5
0.75
1
1.25
1.5
1.75
2
VIL
VIH
Figure 7-29. SWEN/General Purpose Input Pin Logic Thresholds 
Across Temperature
TA (C)
VOL (V)
-40
-20
0
20
40
60
80
100
120
140
0.12
0.14
0.16
0.18
0.2
0.22
0.24
Figure 7-30. PGOOD/FLT/General Purpose Output Pin Logic 
Level Across Temperature
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
21
Product Folder Links: TPS25990



---

## Page 22

7.12 Typical Characteristics (continued)
TA (C)
IQOD (mA)
-40
-20
0
20
40
60
80
100
120
140
16
18
20
22
24
26
28
30
Figure 7-31. QOD Sink Current Across Temperature
Load Current (A)
TJ (C)
40
42
44
46
48
50
52
54
56
40
50
60
70
80
90
100
110
120
130
TA (C)
70
55
25
Figure 7-32. Junction Temperature vs Load Current (No Air-
Flow)
Load Current (A)
TJ (C)
40
42
44
46
48
50
52
54
56
58
60
35
40
45
50
55
60
65
70
75
80
Airflow (LFM)
100
200
400
Figure 7-33. Junction Temperature vs Load Current (With Air-
Flow)
EN held high, IN supply ramped up to 12 V. COUT = 18 mF, 
CdVdt = 33 nF
Figure 7-34. Power Up Using Supply
IN hot-plugged to 12 V supply. COUT = 18 mF, CdVdt = 33 nF, 
Insertion Delay programmed to 25 ms (INS_DLY = 0x01)
Figure 7-35. Input Hot Plug
IN hot-plugged to 12 V supply. COUT = 18 mF, CdVdt = 33 nF, 
Insertion Delay programmed to 560 ms (INS_DLY = 0x07)
Figure 7-36. Input Hot Plug
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
22
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 23

7.12 Typical Characteristics (continued)
IN supply held steady at 12 V, EN pin held high, PMBus 
OPERATION OFF Command. COUT = 18 mF, CdVdt = 33 nF
Figure 7-37. Power Down Using PMBus Command
IN supply held steady at 12 V, EN pin held high, PMBus 
OPERATION ON Command. COUT = 18 mF, CdVdt = 33 nF
Figure 7-38. Power Up Using PMBus Command
IN supply held steady at 12 V, EN pin held high, PMBus 
POWER_CYCLE Command. COUT = 18 mF, CdVdt = 33 nF, 
Default delay setting (RETRY_CONFIG[2:0] = 000b)
Figure 7-39. Power Cycle Using PMBus Command
IN supply held steady at 12 V, EN pin toggled from low to high. 
COUT = 18 mF, CdVdt = 33 nF
Figure 7-40. Power Up Using EN
IN supply held steady at 12 V, EN pin toggled from high to low. 
COUT = 18 mF, CdVdt = 33 nF, ILOAD = 50 A
Figure 7-41. Power Down Using EN
IN supply held steady at 12 V, EN pin toggled from high to low. 
COUT = 18 mF, CdVdt = 33 nF, ILOAD = 0 A
Figure 7-42. Power Down Using EN Without Output Discharge
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
23
Product Folder Links: TPS25990



---

## Page 24

7.12 Typical Characteristics (continued)
IN supply held steady at 12 V, EN pin pulled down to 1 V for > 
5 ms. COUT = 18 mF, CdVdt = 33 nF, ILOAD = 0 A
Figure 7-43. Power Down Using EN With Output Discharge
VIN Undervoltage falling threshold programmed to 10.8 V 
(VIN_UV_FLT = 0x8D), EN held high, IN supply ramped down 
from 12 V to 10.5 V and then ramped up again to 12 V. COUT = 
18 mF, CdVdt = 33 nF
Figure 7-44. Input Undervoltage Protection
VIN Overvoltage rising threshold programmed to 13.78 V 
(VIN_OV_FLT = 0x0B), EN held high, IN supply ramped up 
from 12 V to 15 V and then ramped down again to 12 V. COUT 
= 18 mF, CdVdt = 33 nF
Figure 7-45. Input Overvoltage Protection
VIN Overvoltage rising threshold programmed to 13.78 V 
(VIN_OV_FLT = 0x0B), EN held high, IN supply ramped up 
from 12 V to 15 V and then ramped down again to 12 V. COUT 
= 18 mF, CdVdt = 33 nF
Figure 7-46. Input Overvoltage Protection
IN supply held steady at 12 V, EN toggled from low to high. 
COUT = 18 mF, CdVdt = 33 nF, DVDT scaling at 100 % (default, 
DEVICE_CONFIG[10:9] = 10b)
Figure 7-47. Inrush Current Control
IN supply held steady at 12 V, EN toggled from low to 
high. COUT = 18 mF, CdVdt = 33 nF, DVDT scaling at 50 % 
(DEVICE_CONFIG[10:9] = 00b)
Figure 7-48. Inrush Current Control
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
24
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 25

7.12 Typical Characteristics (continued)
IN supply held steady at 12 V, EN toggled from low to high. 
COUT = 18 mF, CdVdt = 33 nF, Default PG delay setting 
(DEVICE_CONFIG[15] = 0b)
Figure 7-49. Power Good Assertion
IN supply held steady at 12 V, EN toggled from low to high. 
COUT = 18 mF, CdVdt = 33 nF, Higher PG delay setting 
(DEVICE_CONFIG[15] = 1b)
Figure 7-50. Power Good Assertion
Device in steady-state, Load current ramped up from 50 A 
to 70 A for 10 ms and then ramped down to 50 A. OCP 
threshold set to 55 A, Overcurrent blanking delay set to 15 ms 
(OC_TIMER = 0x89)
Figure 7-51. Transient Overcurrent Blanking
Device in steady-state, Load current ramped up from 50 A to 
70 A for > 15 ms. OCP threshold set to 55 A, Overcurrent 
blanking delay set to 15 ms (OC_TIMER = 0x89)
Figure 7-52. Overcurrent Protection
Device in steady-state, Load current ramped up from 50 A to 
70 A for > 15 ms. OCP threshold set to 55 A, Overcurrent 
blanking delay set to 15 ms (OC_TIMER = 0x89), Latch-off 
configuration (Default, RETRY_CONFIG[5:3] = 000b)
Figure 7-53. Fault Response - Latch-off
Device in steady-state, Load current ramped up from 50 A 
to 70 A for 100 ms. OCP threshold set to 55 A, Overcurrent 
blanking delay set to 15 ms (OC_TIMER = 0x89), Auto-retry 1 
times configuration (RETRY_CONFIG[5:3] = 001b), Auto-retry 
delay set to 55 ms (RETRY_CONFIG[2:0] = 000b)
Figure 7-54. Fault Response - Auto-retry
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
25
Product Folder Links: TPS25990



---

## Page 26

7.12 Typical Characteristics (continued)
Device in steady-state, Load current ramped up from 50 A 
to 70 A for 100 ms and then ramped down to 0 A. OCP 
threshold set to 55 A, Overcurrent blanking delay set to 15 
ms (OC_TIMER = 0x89), Auto-retry 4 times configuration 
(RETRY_CONFIG[5:3] = 010b), Auto-retry delay set to 55 ms 
(RETRY_CONFIG[2:0] = 000b)
Figure 7-55. Fault Response Followed By Recovery With Auto-
retry 
OUT shorted to GND. IN supply held steady at 12 V, EN pin 
toggled from low to high.
Figure 7-56. Power Up into Short-Circuit Protection
Device in steady-state, OUT shorted to GND. OCP threshold 
set to 55 A, Short-circuit fast recovery disabled (Default, 
DEVICE_CONFIG[13] = 0b)
Figure 7-57. Short-Circuit Protection During Steady-state
Device in steady-state, OUT shorted to GND. OCP threshold 
set to 55 A, Short-circuit fast recovery disabled (Default, 
DEVICE_CONFIG[13] = 0b)
Figure 7-58. Short-Circuit Protection During Steady-state
Device in steady-state, OUT shorted to GND. OCP threshold 
set to 55 A, Short-circuit fast recovery enabled (Default, 
DEVICE_CONFIG[13] = 1b)
Figure 7-59. Short-Circuit Protection During Steady-state With 
Fast Recovery Enabled
Sudden step in input supply voltage during steady-state 
causes output current spike without triggering a false fast-trip.
Figure 7-60. Input Line Transient Response
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
26
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 27

8 Detailed Description
8.1 Overview
The TPS25990 is an eFuse with integrated power switch to manage load voltage and load current. The device is 
equipped with a PMBus compatible digital interface which allows a host to control, configure, monitor and debug 
the device. The device starts its operation by monitoring the VDD and IN bus. When VDD and VIN exceed the 
respective Undervoltage Protection (UVP) thresholds, the device waits for the insertion delay timer duration to 
wait for the supply to stabilize before starting up. Next the device samples the EN/UVLO pin and SWEN pins. A 
high level on both these pins enables the internal MOSFET to start conducting and allows current to flow from IN 
to OUT. When either EN/UVLO or SWEN is held low, the internal MOSFET is turned off.
After a successful start-up sequence, the TPS25990 device now actively monitors its load current and input 
voltage, and controls the internal FET to ensure that the programmed overcurrent threshold is not exceeded 
and input overvoltage spikes are cut off. This action keeps the system safe from harmful levels of voltage and 
current. At the same time, a user-programmable overcurrent blanking timer allows the system to pass transient 
peaks in the load current profile without tripping the eFuse. Similarly, voltage transients on the supply line are 
intelligently masked to prevent nuisance trips. This feature ensures a robust protection solution against real 
faults which is also immune to transients, thereby ensuring maximum system uptime.
The TPS25990 allows the host to monitor various system parameters and status over the PMBus interface. It 
is also possible to change the device configuration over the PMBus interface to control device behavior as per 
system needs. This includes various warning/fault thresholds, timers and pin functions. The configuration values 
can also be stored in the internal non-volatile OTP memory or an external EEPROM so that the device can start 
up with some pre-defined configuration without host intervention at every power-up.
The TPS25990 also provides advanced telemetry features such as high speed ADC sample buffering ("digital 
oscilloscope") and Blackbox fault recording which simplify system design and debugging and facilitate predictive 
maintenance.
The device has an integrated high accuracy and high bandwidth analog load current monitor, which allows 
the system to precisely monitor the load current in steady state as well as during transients. This feature 
facilitates the implementation of advanced dynamic platform power management techniques such as Intel PSYS 
to maximize system power usage and throughput without sacrificing safety and reliability.
For systems needing higher load current support, the TPS25990 can be connected in parallel with other high 
current eFuses like TPS25985x. The TPS25990 acts as a primary controller and enables control, telemetry and 
configuration of the whole chain over PMBus.
All devices share current during start-up as well as steady-state to avoid over-stressing some of the devices 
more than others which can result in premature or partial shutdown of the parallel chain. The devices 
synchronize their operating states to ensure graceful start-up, shutdown and response to faults. This makes the 
whole chain function as a single very high current eFuse rather than a bunch of independent eFuses operating 
asynchronously.
The device has integrated protection circuits to ensure device safety and reliability under recommended 
operating conditions. The internal FET SOA is protected at all times using a thermal shutdown mechanism, 
which turns off the FET whenever the junction temperature (TJ) becomes too high for the FET to operate safely.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
27
Product Folder Links: TPS25990



---

## Page 28

8.2 Functional Block Diagram
Driver/Controller
MUX
VIN_SNS
VOUT_SNS
AUX
VTEMP
VIMON
ADC
ADDR0
22
IN
VDD
19
21
3
2
CP
4
7
8
9
OUT
IMON
ILIM
IREF/DAC2
OC_IMON
+
-
6
DVDT
DAC1
Temperature Sense and 
Overtemperature protection
5
TEMP/CMP
GPIO3/SWEN/COMP1/
COMP2/EEDATA/EECLK
18
EN/UVLO
14
GND
TPS25990
17
20
GPIO2/FAULTB/COMP1/
COMP2/EEDATA/EECLK
1
ADDR1
GPIO1/PG/COMP1/COMP2/
EEDATA/EECLK
GPIO4/SMBA#/COMP1/
COMP2/EEDATA/EECLK
VTEMP
+
-
VIMON
+
-
+
-
OVP
VOV
+
-
+
-
VUVLO
VUVP
VSD
VINT
÷10
UVLO
SD
QOD_EN
+
-
+
-
DAC
DAC
DAC
VIN_SNS
÷10
VOUT_SNS
DEVICE_CONFIG[12:11]
TSD
SWEN_SNS
GHI
FFT
FB
UVP
DEVICE_CONFIG[6]
+
-
10
11
12
13
23 
24 
25 
26
DAC
DAC
VOV
RETRY_DLY
OC_TIMER
BB_TIMER
ADC 
CTRL
DAC
VCMP2REF
VCMP2REF
CMPOUT2
Computation
/Logic Block
Telemetry
Basic 
Parameters
Extended
Telemetry
Computed 
Parameters
Configuration
Registers
Telemetry
Status  
BB_RAM
BB Shadow 
RAM
BB  
CTRL
PMBus Digital Engine
 EEPROM I2C Controller
GPIO 
Driver
Configuration 
NVM
STORE
RESTORE
OPERATION
VIREF
CMPOUT1
VCMP1REF
IDAC1
VDAC2
STORE
RESTORE
CLEAR_FAULTS
POWER_CYCLE
VIN 
TRAN
SFT
SWEN_SNS
SWEN_INT
FLT_GLBL
Control
GND
VREF
WRITE_PROTECT
Back-up 
OC 
detector
OC_ILIM
CMPOUT1
CMPOUT2
IADDR
IADDR
REF GEN
GHI
FB
STORE
RESTORE
16
15
SDA
SCL
GPDAC1[6]
4
4
6
6
6
4
10
FET_FLT
QOD_EN
INS_DLY
SFTREF
IREFLIN
IREFSAT
WRITE PROTECT
OC_IMON
FLT_GLBL
UVP
PG_INT
WRITE_PROTECT
VREF
18.18 
µA/A  
18.18 
µA/A  
DEVICE_CONFIG[2]
DEVICE_CONFIG[10:9]
OVP
UVP
22.1 mA
Figure 8-1. TPS25990 Functional Block Diagram
8.3 Feature Description
The TPS25990 eFuse is a highly integrated, advanced power management device that provides monitoring, 
detection, protection and reporting in the event of system faults.
8.3.1 Undervoltage Protection
The TPS25990 implements undervoltage lockout on VDD and VIN in case the applied voltage becomes too low 
for the system or device to properly operate. The undervoltage lockout has a default internal threshold (VUVP) on 
VDD and programmable threshold (VUVLOIN) on VIN. Alternatively, the UVLO comparator on the EN/UVLO pin 
allows the undervoltage protection threshold to be externally adjusted to a user defined value. Figure 8-2 and 
Equation 1 show how a resistor divider can be used to set the UVLO set point for a given voltage supply.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
28
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 29

IN
EN/UVLO
GND
Power 
Supply
R1
R2
Figure 8-2. Adjustable Undervoltage Protection
VIN UV = VUVLO R
R1 + R2
R2
(1)
The VIN UVLO fault threshold can also be programmed using PMBus® writes to VIN_UV_FLT register.
The EN/UVLO pin implements a bi-level threshold and can be used to control the device from an external host.
1.
VEN > VUVLO(R): Device is fully ON.
2.
VSD(F) < VEN < VUVLO(F): The FET along with most of the controller circuitry is turned OFF, except for some 
critical bias and digital circuitry. Holding the EN/UVLO pin in this state for a duration greater than tQOD 
activates the Output Discharge function.
3.
VEN < VSD(F): All active circuitry inside the part is turned OFF and it retains no digital state memory. It also 
resets latched faults, status flags and configuration values written to the registers through PMBus® writes.
8.3.2 Insertion Delay
The TPS25990 implements insertion delay at start-up to ensure the supply has stabilized before the device tries 
to turn on the power to the load. This is helpful in hotswap applications where a card is hot-plugged into a live 
backplane and can have some contact bounce before the card is firmly plugged into the connector. The device 
initially waits for the VDD supply to rise above the VUVP threshold and all the internal bias voltages to settle. After 
that, the device remains off for an additional delay of tINSDLY irrespective of the EN/UVLO pin condition. This 
action helps to prevent any unexpected behavior in the system if the device tries to turn on before the card has 
made firm contact with the backplane or if there is any supply ringing or noise during start-up.
The insertion delay can be changed by programming the INS_DLY register value in the Non-volatile memory/
EEPROM using PMBus®.
8.3.3 Overvoltage Protection
The TPS25990 implements overvoltage lockout to protect the load from input overvoltage conditions. If the 
input voltage on IN exceeds the OVP rising threshold, the power FET is turned OFF within tOVP. The OVP 
comparator on the IN pin uses a default internal overvoltage protection threshold of VOVP(R), which can be 
changed by programming the non-volatile configuration memory or dynamically through PMBus® register writes 
to the VIN_OV_FLT register. The OVP comparator has in-built hysteresis for improved noise immunity. After the 
voltage on IN falls below the OVP falling threshold (VOVP(F)), the FET is turned ON in a dVdt controlled manner.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
29
Product Folder Links: TPS25990



---

## Page 30

IN
0
Time
OUT
0
SWEN
VL
0
tOVP
Input Overvoltage Event
Input Overvoltage Removed
dVdt limited Start-up
VOVP(R)
(1)
  
VOVP(F)
VIN
PG
VL
0
FLT
VL
0
(1)
 Depends on VIN_OV_FLT register setting
Figure 8-3. Input Overvoltage Protection Response
8.3.4 Inrush Current, Overcurrent, and Short-Circuit Protection
TPS25990 incorporates four levels of protection against overcurrent:
1.
Adjustable slew rate (dVdt) for inrush current control
2.
Active current limit with an adjustable threshold (ILIM) for overcurrent protection during start-up
3.
Circuit-breaker with an adjustable threshold (IOCP) and blanking timer (tOC_TIMER) for overcurrent protection 
during steady-state
4.
Fast-trip response to severe overcurrent faults with a programmable threshold to quickly protect against 
severe short-circuits under all conditions, as well as a fixed threshold (IFFT) during steady state
8.3.4.1 Slew rate (dVdt) and Inrush Current Control
During hot-plug events or while trying to charge a large output capacitance, there can be a large inrush current. 
If the inrush current is not managed properly, it can put excessive stress on the system power supply causing it 
to droop and even damage the input connectors. This action can lead to unexpected restarts elsewhere in the 
system. The inrush current during turn-on is directly proportional to the load capacitance and rising slew rate. 
Equation 2 can be used to find the slew rate (SR) required to limit the inrush current (IINRUSH) for a given load 
capacitance (CLOAD):
SR 
V
ms
=
IINRUSH  mA
COUT  µF
(2)
A capacitor can be added to the DVDT pin to control the rising slew rate and lower the inrush current during 
turn-on. This is also a function of the dVdt rate scaling factor which can be digitally programmed through 
PMBus® writes to the DEVICE_CONFIG register. The required CdVdt capacitance to produce a given slew rate 
can be calculated using Equation 3.
CdVdt  pF = 42000  ×  k
SR 
V
ms
(3)
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
30
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 31

where k = 1, if DEVICE_CONFIG[10:9] = 10 (Default)
k = 0.5, if DEVICE_CONFIG[10:9] = 00
k = 0.75, if DEVICE_CONFIG[10:9] = 01
k = 1.5, if DEVICE_CONFIG[10:9] = 11
The fastest output slew rate is achieved by leaving the dVdt pin open and setting DEVICE_CONFIG[10:9] = 11.
Note
High turn-on slew rates in combination with high input power path inductance can result in oscillations 
during start-up. This can be mitigated using one or more of the following steps:
1.
Reduce the input inductance.
2.
Increase the capacitance on VIN pin.
3.
Increase the DVDT pin capacitor value or change the DVDT scaling factor using 
DEVICE_CONFIG[10:9] register bits to reduce the slew rate or increase the start-up time. TI 
recommends using a minimum start-up time of 5 ms.
8.3.4.1.1 Start-Up Timeout
If the start-up is not completed, that is, the FET is not fully turned on within a certain timeout interval 
(tSU_TMR) after SWEN is asserted, the device registers it as a fault. The fault status is reported in the 
STATUS_MFR_SPECIFIC register Bit[6]. FLT is asserted low and the device goes into latch-off or auto-retry 
mode depending on the RETRY_CONFIG register setting.
8.3.4.2 Steady-State Overcurrent Protection (Circuit-Breaker)
The TPS25990 responds to output overcurrent conditions during steady-state by performing a circuit-breaker 
action after a user-adjustable transient fault blanking interval. This action allows the device to support a higher 
peak current for a short user-defined interval but also ensures robust protection in case of persistent output 
faults.
The device constantly senses the output load current and provides an analog current output (IIMON) on the IMON 
pin which is proportional to the load current, which in turn produces a proportional voltage (VIMON) across the 
IMON pin resistor (RIMON) as per Equation 4.
VIMON = IOUT × GIMON × RIMON
(4)
Where GIMON is the current monitor gain (IIMON : IOUT)
The overcurrent condition is detected by comparing this voltage against the voltage on the IREF pin as a 
reference. The reference voltage (VIREF) can be controlled in two ways, which sets the overcurrent protection 
threshold (IOCP) accordingly.
•
The reference voltage (VIREF) can be generated using internal DAC and can be changed by programming the 
non-volatile configuration memory or dynamically through PMBus® writes to the VIREF register.
•
It is also possible to drive the IREF pin from an external low impedance precision reference voltage source.
The overcurrent protection threshold during steady-state (IOCP) can be calculated using Equation 5.
IOCP =
VIREF
GIMON × RIMON
(5)
Note
TI recommends to add a 1 nF capacitor from IREF pin to GND for improved noise immunity.
After an overcurrent condition is detected, that is the load current exceeds the programmed current limit 
threshold (IOCP), but stays lower than the short-circuit threshold (ISCP), the device starts running the internal 
overcurrent blanking digital timer (OC_TIMER). If the load current drops below the current limit threshold before 
the OC_TIMER expires, the circuit-breaker action is not engaged. This action allows short overload transient 
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
31
Product Folder Links: TPS25990



---

## Page 32

pulses to pass through the device without tripping the circuit. At the same time, the OC_TIMER is reset so that 
it is at its default state before the next overcurrent event. This ensures the full blanking timer interval is provided 
for every overcurrent event.
If the overcurrent condition persists, the OC_TIMER continues to run and after it expires, the circuit-breaker 
action turns off the FET immediately.
Equation 6 can be used to calculate the RIMON value for the desired overcurrent threshold.
RIMON =
VIREF
GIMON × IOCP
(6)
The duration for which transients are allowed can be programmed using OC_TIMER register setting through 
PMBus® writes.
Figure 8-4 illustrates the overcurrent response for TPS25990 eFuse. After the part shuts down due to a circuit-
breaker fault, it either stays latched off or restarts automatically based on the RETRY_CONFIG register setting.
IOUT
IOCP
0
Time
OUT
VIN
0
TJ
TSD
TJ
tOC_TIMER (1)
Load transient
OC_TIMER expired
Persistent output overload
TSDHYS
Circuit-Breaker 
operation
PG
VL
0
FLT
0
VL
2 × IOCP
IMON
VIREF
0
SWEN
VL
0
OC_TIMER starts
OC_TIMER starts
(1)  Depends on the OC_TIMER register setting
Figure 8-4. Steady-state Overcurrent (Circuit-Breaker) Response
When a transient overcurrent condition (the load current exceeds the programmed current limit threshold but the 
OC_TIMER does not expire) is detected, the device:
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
32
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 33

•
sets the OC_DET bit in the STATUS_MFR_SPECIFIC_2 register
•
fills-up one of the Blackbox RAM registers (if available to write) writing the event identifier as OC_DET and 
relative time stamp information
•
increases the Blackbox RAM address pointer in the BB_TIMER register by one (1) if it was previously less 
than six (6), otherwise resets to zero (0). This change in the address pointer only occurs if one of the 
Blackbox RAM registers is available to write.
Note
It is assumed that the VIN_UV_WARN , VIN_OV_WARN, and VOUT_UV_WARN events are not 
triggered because of a step load transient.
When a persistent overcurrent condition (the load current exceeds the programmed current limit threshold and 
the OC_TIMER expires) is detected, the device:
•
sets the FET_OFF and NONE_OF_THE_ABOVE/UNKNOWN bits in the STATUS_BYTE register
•
sets the OUT_STATUS, INPUT_STATUS, PGOODB, and NONE_OF_THE_ABOVE/UNKNOWN bits in the 
upper byte of the STATUS_WORD register
•
sets the VOUT_UV_WARN bit in the STATUS_OUT register
•
sets the OC_FLT bit in the STATUS_INPUT register
•
sets the PGOODB bit in the STATUS_MFR_SPECIFIC_2 register
•
notifies the host by asserting SMBA, if it is not masked setting the STATUS_IN, PGOODB, and 
STATUS_OUT bits in the ALERT_MASK register and the GPIO4 pin is configured as SMBA Output in the 
GPIO_CONFIG_34 register
•
deasserts the external PG signal, if the GPIO1 pin is configured as PGOOD Output in the GPIO_CONFIG_12 
register
•
asserts the FLT signal, if it is not masked setting the OC_FLT bit high in the FAULT_MASK register and the 
GPIO2 pin is configured as FLT Output in the GPIO_CONFIG_12 register
Note
It is assumed that the VIN_UV_WARN and VIN_OV_WARN events are not triggered because of a 
step load transient.
8.3.4.3 Active Current Limiting During Start-Up
The TPS25990 responds to output overcurrent conditions during start-up by actively limiting the current. The 
device constantly senses the current flowing through the device (IDEVICE) and provides an analog current output 
(IILIM) on the ILIM pin, which in turn produces a proportional voltage (VILIM) across the ILIM pin resistor (RILIM) as 
per Equation 7.
VILIM = IDEVICE × GILIM × RILIM
(7)
Where GILIM is the current monitor gain (IILIM : IDEVICE)
The overcurrent condition is detected by comparing this voltage against a threshold which is a scaled voltage 
(CLREFSAT) derived from the reference voltage (VIREF) on the IREF pin as presented in Equation 8.
CLREFSAT =
0.7 × VIREF
3
(8)
The reference voltage (VIREF) can be controlled in two ways, which sets the overcurrent protection threshold 
(ILIM) accordingly.
•
The reference voltage (VIREF) can be generated using internal DAC and can be changed by programming the 
non-volatile configuration memory or dynamically through PMBus® writes to the VIREF register.
•
It is also possible to drive the IREF pin from an external low impedance precision reference voltage source.
The active current limit (ILIM) threshold during start-up can be calculated using Equation 9.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
33
Product Folder Links: TPS25990



---

## Page 34

IILIM =
CLREFSAT
GILIM × RILIM
(9)
When the load current during start-up exceeds ILIM, the device tries to regulate and hold the load current at ILIM.
During current regulation, the output voltage drops, resulting in increased device power dissipation across the 
FET. If the device internal temperature (TJ) exceeds the thermal shutdown threshold, the FET is turned off. After 
the part shuts down due to a TSD fault, it either stays latched off or restarts automatically after a delay based 
on the RETRY_CONFIG register setting. See Overtemperature protection section for more details on device 
response to overtemperature.
Note
The active current limit block employs a foldback mechanism during start-up based on the output 
voltage (VOUT). When VOUT is below the foldback threshold (VFB), the current limit threshold is further 
lowered.
8.3.4.4 Short-Circuit Protection
During an output short-circuit event, the current through the device increases very rapidly. When an output 
short-circuit is detected, the internal fast-trip comparator triggers a fast protection sequence to prevent the 
current from building up further and causing any damage or excessive input supply droop. This action enables 
the user to adjust the fast-trip threshold as per system rating, rather than using a high fixed threshold which may 
not be suitable for all systems. The fast-trip comparator employs a scalable threshold (ISFT) which is a function 
of the circuit-breaker threshold (IOCP) and a digitally programmable scaling factor. The default fast-trip threshold 
is equal to 2 × IOCP during steady-state and 1.5 × ILIM during inrush. The scaling factor for steady-state fast-trip 
threshold can be programmed to a different value using the DEVICE_CONFIG[12:11] register bits. Available 
programming options are 1.5 ×, 2 ×, 1.75 × and 2.25 ×. After the current exceeds the fast-trip threshold, the 
TPS25990 turns off the FET within tSFT.
The device also employs a higher fixed fast-trip threshold (IFFT) to provide fast protection against hard 
short-circuits during steady-state (FET in linear region). After the current exceeds IFFT, the FET is turned off 
completely within tFFT.
The device response after a fast-trip event can be configured using the SC_RETRY bit in the DEVICE_CONFIG 
register through PMBus® register writes or non-volatile configuration memory. There are 2 programming options 
available:
1.
SC_RETRY = 0 (Default setting): The device latches a fault and remains off till a restart is triggered either 
externally or through internal auto-retry mechanism as per the RETRY_CONFIG register setting.
When a short-circuit fault occurs with the SC_RETRY bit in the DEVICE_CONFIG register low, the device:
•
sets the FET_OFF and NONE_OF_THE_ABOVE/UNKNOWN bits in the STATUS_BYTE register
•
sets the OUT_STATUS, PGOODB, and NONE_OF_THE_ABOVE/UNKNOWN bits in the upper byte of 
the STATUS_WORD register
•
sets the VOUT_UV_WARN bit in the STATUS_OUT register
•
sets the PGOODB and SC_FLT bits in the STATUS_MFR_SPECIFIC_2 register
•
notifies the host by asserting SMBA#, if it is not masked setting the PGOODB and STATUS_OUT bits in 
the ALERT_MASK register and the GPIO4 pin is configured as SMBA# Output in the GPIO_CONFIG_34 
register
•
deasserts the external PG signal, if the GPIO1 pin is configured as PGOOD Output in the 
GPIO_CONFIG_12 register
•
asserts the FLT signal, if it is not masked setting the SC_FLT bit high in the FAULT_MASK register and 
the GPIO2 pin is configured as 'FLT Output' in the GPIO_CONFIG_12 register
2.
SC_RETRY = 1: The device attempts to turn the FET back ON fully after a short de-glitch interval (30 
μs). This allows the FET to try and recover quickly after a transient overcurrent event and minimizes 
the output voltage droop. However, if the fault is persistent, the device enters current limit causing the 
junction temperature to rise and eventually enter thermal shutdown. The device latches a fault and 
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
34
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 35

remains off till a restart is triggered either externally or through internal auto-retry mechanism as per 
the RETRY_CONFIG register setting. See Overtemperature Protection section for details on the device 
response to overtemperature.
When a short-circuit fault occurs with the SC_RETRY bit in the DEVICE_CONFIG register high, the device:
•
sets the FET_OFF, STATUS_TEMP, and NONE_OF_THE_ABOVE/UNKNOWN bits in the 
STATUS_BYTE register
•
sets the OUT_STATUS, MFR_STATUS, PGOODB, and NONE_OF_THE_ABOVE/UNKNOWN bits in the 
upper byte of the STATUS_WORD register
•
sets the VOUT_UV_WARN bit in the STATUS_OUT register
•
sets the OT_FLT bit in the STATUS_TEMP register
•
sets the SOA_FLT bit in the STATUS_MFR_SPECIFIC register
•
sets the PGOODB bit in the STATUS_MFR_SPECIFIC_2 register
•
notifies the host by asserting SMBA#, if it is not masked setting the PGOODB, MFR_STATUS, 
STATUS_TEMP, and STATUS_OUT bits in the ALERT_MASK register and the GPIO4 pin is configured 
as SMBA# Output in the GPIO_CONFIG_34 register
•
deasserts the external PG signal, if the GPIO1 pin is configured as PGOOD Output in the 
GPIO_CONFIG_12 register
•
asserts the FLT signal, if it is not masked setting the SOA_FLT and TEMP_FLT bits high in the 
FAULT_MASK register and the GPIO2 pin is configured as 'FLT Output' in the GPIO_CONFIG_12 
register
Figure 8-5 illustrates the short-circuit response for TPS25990 eFuse.
In some of the systems, for example blade servers and telecom equipment which house multiple hot-pluggable 
blades or line cards connected to a common supply backplane, there can be transients on the supply due to 
switching of large currents through the inductive backplane. This can result in current spikes on adjacent cards 
which can potentially be large enough to trigger the fast-trip comparator of the eFuse. The TPS25990 uses a 
proprietary algorithm to avoid nuisance tripping in such cases thereby facilitating uninterrupted system operation.
Note
•
The VIN_TRAN status bit in STATUS_MFR_SPECIFIC_2 register is set to indicate if an input line 
transient event was detected and masked.
•
The input line transient masking feature can be optionally disabled by setting the VIN_TRAN_DIS 
bit high in the DEVICE_CONFIG register.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
35
Product Folder Links: TPS25990



---

## Page 36

IOUT
IOCP
0
Time
OUT
VIN
0
PG
0
TJ
TSD
TSDHYS
Thermal Shutdown
IN
0
2 × IOCP (4)
Transient Severe Overcurrent
Persistent Severe Overcurrent Fault
Fault Removed
tSFT
tSFT
VL
FLT
0
VL
(1) Fast recovery enabled using DEVICE_CONFIG[13] bit setting
(2) Fast recovery disabled using DEVICE_CONFIG[13] bit setting
(3) Device configured for auto-retry response using RETRY_CONFIG register setting
(4) Default SFT threshold using DEVICE_CONFIG[12:11] bit setting
IFFT
VIN
dVdt limited 
start-up
Retry Timer Elapsed (2)(3)
Or 
Power/Enable Cycled
IMON
VIREF
0
2 × VIREF (4)
ILIM
0.23 × VIREF
0
0.5 × VIREF
SWEN
0
VL
Retry Timer Elapsed (3)
Or 
Power/Enable Cycled
dVdt limited 
Start-up
Retry Timer Elapsed (3)
Or 
Power/Enable Cycled
ILIM
Current limited 
Start-up
Transient Severe Overcurrent
tSFT
tPGD
Fast Recovery (1)
Current limited recovery
Figure 8-5. Short-Circuit Response
8.3.5 Single Point Failure Mitigation
The TPS25990 relies on the proper component connections and biasing on the IMON, ILIM and IREF pins along 
with the appropriate threshold digital configurations to provide overcurrent and short-circuit protection under all 
circumstances. As an added safety measure, the device uses the following mechanisms to ensure that the 
device provides some form of overcurrent protection even if any of these pins are not connected correctly in 
the system or the associated components have a failure in the field or if the configuration registers are not 
programmed correctly.
8.3.5.1 IMON Pin Single Point Failure
•
IMON pin open: In this case, the IMON pin voltage is internally pulled up to a higher voltage and exceeds 
the threshold (VIREF), causing the part to perform a circuit-breaker action even if there is no significant current 
flowing through the device.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
36
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 37

•
IMON pin shorted to GND directly or through a very low resistance: In this case, the IMON pin voltage 
is held at a low voltage and is not allowed to exceed the threshold (VIREF) even if there is significant current 
flowing through the device, thereby rendering the primary overcurrent protection mechanism ineffective. 
The device relies on an internal overcurrent sense mechanism to provide some protection as a backup. 
If the device detects that the backup current sense threshold (IOC_BKP) is exceeded but at the same time 
the primary overcurrent detection on IMON pin fails, it triggers single point failure detection and latches 
a fault. The FET is turned off and the FLT pin is asserted. At the same time, the SPFAIL status bit in 
STATUS_MFR_SPECIFIC_2 register is set and the SMBA# signal is asserted.
8.3.5.2 ILIM Pin Single Point Failure
•
ILIM pin open: In this case, the ILIM pin voltage is internally pulled up to a higher voltage and exceeds the 
VIREF threshold, causing the part to engage the current limit even if there is no significant current flowing 
through the device.
•
ILIM pin shorted to GND directly or through a very low resistance: In this case, the ILIM pin voltage 
is held at a low voltage and is not allowed to exceed the start-up current limit threshold even if there 
is significant current flowing through the device, thereby rendering the primary current limit mechanism 
ineffective during start-up. The device relies on an internal overcurrent detection mechanism to provide some 
protection as a backup. If the device detects that the load current exceeds the backup overcurrent threshold 
(IOC_BKP) but at the same time the primary overcurrent detection on ILIM pin fails, it triggers single point 
failure detection and latches a fault. The FET is turned off and the FLT pin is asserted. At the same time, the 
SPFAIL status bit in STATUS_MFR_SPECIFIC_2 register is set and the SMBA# signal is asserted.
8.3.5.3 IREF Pin Single Point Failure
•
IREF DAC set incorrectly or externally forced to higher voltage: In this case, the IREF pin (VIREF) is 
pulled up internally or externally to a voltage which is higher than the target value as per the recommended 
IOCP or ILIM calculations, preventing the primary circuit-breaker, active current limit, and short-circuit protection 
from getting triggered even if there is significant current flowing through the device. The device relies on an 
internal overcurrent detection mechanism to provide some protection as a backup. If the device detects that 
the load current exceeds backup overcurrent threshold (IOC_BKP) but at the same the primary overcurrent 
or short-circuit detection on ILIM or IMON pin fails, it triggers single point failure detection and latches 
a fault. The FET is turned off and the FLT pin is asserted. At the same time, the SPFAIL status bit in 
STATUS_MFR_SPECIFIC_2 register is set and the SMBA# signal is asserted.
•
IREF pin shorted to GND: In this case, the VIREF threshold is set to 0 V, causing the part to perform active 
current limit or circuit-breaker action even if there is no significant current flowing through the device.
8.3.6 Analog Load Current Monitor (IMON)
The TPS25990 allows the system to monitor the output load current accurately by providing an analog current on 
the IMON pin which is proportional to the current through the FET. The benefit of having a current output is that 
the signal can be routed across a board without adding significant errors due to voltage drop or noise coupling 
from adjacent traces. The current output also allows the IMON pins of multiple eFuse devices (TPS25990 or 
TPS25985x) to be tied together to get the total current in a parallel configuration. The IMON signal can be 
converted to a voltage by dropping it across a resistor at the point of monitoring. The user can sense the voltage 
(VIMON) across the RIMON to get a measure of the output load current using Equation 10.
IOUT =
VIMON
GIMON × RIMON
(10)
The TPS25990 IMON circuit is designed to provide high bandwidth and high accuracy across load and 
temperature conditions, irrespective of board layout and other system operating conditions. This design allows 
the IMON signal to be used for advanced dynamic platform power management techniques such as Intel PSYS 
or PROCHOT to maximize system power usage and platform throughput without sacrificing safety or reliability.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
37
Product Folder Links: TPS25990



---

## Page 38

Figure 8-6. Analog Load Current Monitor Response
Note
1.
The IMON pin provides load current monitoring information only during steady-state. During 
inrush, the IMON pin reports zero load current.
2.
The ILIM pin reports the individual device load current at all times and can also be used as an 
analog load current monitor for each individual device.
3.
TI recommends adding a 22 pF capacitor from IMON pin to GND for noise filtering purposes.
4.
Care must be taken to minimize parasitic capacitance on the ILIM pin to avoid any impact on the 
overcurrent and short-circuit protection timing during start-up.
8.3.7 Overtemperature Protection
The TPS25990 employs an internal thermal shutdown mechanism to protect itself when the internal FET 
becomes too hot to operate safely. When the TPS25990 detects thermal overload, it shuts down. Thereafter 
it either remains latched-off until the device is power cycled or re-enabled, or restarts automatically after delay 
based on the device Auto-retry configuration.
The overtemperature threshold has a default threshold (TSD) which can be digitally programmed to a lower 
value using the OT_FLT register based on system needs.
Table 8-1. Overtemperature Protection Summary
Auto-Retry 
Configuration
Enter TSD
Exit TSD
Latch-Off
VTEMP ≥ OT_FLT threshold or TJ ≥ TSD
VTEMP < OT_FLT - OTHys or TJ < TSD – TSDHYS
VDD cycled to 0 V and then above VUVP(R) or EN/
UVLO toggled below VSD(F)
Auto-Retry
VTEMP ≥ OT_FLT threshold or TJ ≥ TSD
VTEMP < OT_FLT - OTHys or TJ < TSD – TSDHYS
Retry Timer expired or VDD cycled to 0 V and then 
above VUVP(R) or EN/UVLO toggled below VSD(F)
8.3.8 Analog Junction Temperature Monitor (TEMP)
The TPS25990 allows the system to monitor the junction temperature (TJ) accurately by providing an analog 
voltage on the TEMP pin which is proportional to the temperature of the die. This voltage is sensed by an 
ADC input and reported using the READ_TEMPERATURE_1 PMBus® command for digital telemetry. In a 
multi-device parallel configuration involving TPS25990 and TPS25985x , the TEMP outputs of all devices can be 
tied together. In this configuration, the TEMP signal reports the temperature of the hottest device in the chain.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
38
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 39

Note
1.
The TEMP pin voltage is used only for external monitoring and does not interfere with the 
overtemperature protection scheme of each individual device which is based purely on the internal 
temperature monitor.
2.
TI recommends to add a capacitance of 22 pF on the TEMP pin to filter out glitches during system 
transients.
8.3.9 FET Health Monitoring
The TPS25990 can detect and report certain conditions which are indicative of a failure of the power path FET. If 
undetected or unreported, these conditions can compromise system performance either by not providing power 
to the load correctly or the necessary level of protection. After a FET failure is detected, the TPS25990 tries 
to turn off the internal FET by pulling the gate low and asserts the FLT pin. The specific FET fault type is also 
reported in the STATUS_MFR_SPECIFIC status register.
•
D-S short: D-S short can result in a constant uncontrolled power delivery path formed from source to load, 
either due to a board assembly defect or due to internal FET failure. This condition is detected at start-up 
by checking if VIN-OUT < VDSFLT before the FET is turned ON. If yes, the device engages the internal output 
discharge to try and discharge the output. If the VOUT doesn’t discharge below VFB within a certain allowed 
interval, the device asserts the FLT pin and sets the FET_FAULT_DS bit in the STATUS_MFR_SPECIFIC 
status register.
Note
There is an option to disable the D-S fault detection digitally by setting the DIS_VDSFLT bit in the 
DEVICE_CONFIG register. This allows the device start-up into a pre-charged output without triggering 
the D-S fault.
•
G-D short: The TPS25990 detects this kind of FET failure at all times by checking if the gate voltage is 
close to VIN even when the internal control logic is trying to hold the FET in OFF condition. If this condition is 
detected, the device asserts the FLT pin and sets the FET_FAULT_GD bit in the STATUS_MFR_SPECIFIC 
status register.
•
G-S short: The TPS25990 detects this kind of FET failure during start-up by checking if the FET G-S voltage 
fails to reach the necessary overdrive voltage within a certain timeout period (tSU_TMR) after the gate driver is 
turned ON. While in steady-state, if the G-S voltage becomes low before the controller logic has signaled to 
the gate driver to turn off the FET, it is latched as a fault. If this condition is detected, the device asserts the 
FLT pin and sets the FET_FAULT_GS bit in the STATUS_MFR_SPECIFIC status register.
8.3.10 General Purpose Digital Input/Output Pins
The TPS25990 has four (4) general purpose digital input/output pins which can be configured for different 
functions as per system needs.
1.
General Purpose Digital Input
2.
General Purpose Digital Output
3.
Fault (FLT) Indication Output
4.
Power Good (PG) Indication Output
5.
SWEN Input/Output
6.
SMBus Alert (SMBA#) Indication Output
7.
General Purpose Comparator-1 Output
8.
General Purpose Comparator-2 Output
9.
External EEPROM I2C Clock (EECLK)
10. External EEPROM I2C Data (EEDATA)
8.3.10.1 Fault Response and Indication (FLT)
Table 8-2 summarizes the device response to various fault conditions.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
39
Product Folder Links: TPS25990



---

## Page 40

Table 8-2. Fault Summary
Event or Condition
Device Response
Fault Latched 
Internally
FLT Pin Status
Pin Indication 
Masking Option
Delay
Steady-state
None
N/A
H
N/A
Inrush
None
N/A
H
N/A
Overtemperature
Shutdown
Y
L
Y
Undervoltage (EN/UVLO)
Shutdown
N
H
N/A
Undervoltage (VDD UVP)
Shutdown
N
H
N/A
Undervoltage (VIN UVP)
Shutdown
N
H
N/A
Overvoltage (VIN OVP)
Shutdown
N
H
N/A
Transient overcurrent
None
N
H
N/A
Persistent overcurrent 
(steady-state)
Circuit-Breaker
Y
L
Y
tITIMER
Persistent overcurrent 
(start-up)
Current Limit
N
H
N/A
Output short-circuit
Fast-trip
Y
L
Y
tFT
Output short-circuit (Fast 
recovery configuration)
Fast-trip followed by 
current limited Start-up
N
H
N/A
ILIM pin open (start-up)
Shutdown
Y
L
Y
ILIM pin short (start-up)
Shutdown (if IOUT > 
IOC_BKP)
Y
L
Y
ILIM pin open (steady-
state)
Active current sharing 
loop always active
N
H
N/A
ILIM pin short (steady-
state)
Active current sharing 
loop disabled
N
H
N/A
IMON pin open (steady-
state)
Shutdown
Y
L
Y
IMON pin short (steady-
state)
Shutdown (If IOUT > 
IOC_BKP)
Y
L
Y
45 μs
IREF pin open (start-up)
Shutdown (If IOUT > 
IOC_BKP)
Y
L
Y
IREF pin open (steady-
state)
Shutdown (if IOUT > 
IOC_BKP)
Y
L
Y
tITIMER
IREF pin short (steady-
state)
Shutdown
Y
L
Y
IREF pin short (start-up)
Shutdown
Y
L
Y
Start-up timeout
Shutdown
Y
L
N
tSU_TMR
FET health fault (G-S)
Shutdown
Y
L
Y
10 μs
FET health fault (G-D)
Shutdown
Y
L
Y
FET health fault (D-S)
Shutdown
N
L
Y
tSU_TMR
External fault (SWEN 
pulled low externally while 
device is not in UV or OV)
Shutdown
Y
L
Y
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
40
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 41

Table 8-2. Fault Summary (continued)
Event or Condition
Device Response
Fault Latched 
Internally
FLT Pin Status
Pin Indication 
Masking Option
Delay
Comparator-1 fault
Configurable through 
DEVICE_CONFIG 
register
Y
L
Y
Comparator-2 fault
Configurable through 
DEVICE_CONFIG 
register
Y
L
Y
Note
GPIO2 pin is configured as FLT by default to provide an active low fault indication. FLT is an open-
drain pin and must be pulled up to an external supply. Refer to GPIO_CONFIG_12 register for more 
details and configuration options.
The device response after a fault varies based on the RETRY_CONFIG register setting. The device latches 
a fault as per the table above and thereafter follows an auto-retry or latch-off response. For auto-retry 
configuration, the latched faults also trigger the start of the Auto-Retry Timer, while keeping the FLT pin pulled 
low. On expiry of the timer period (tRETRY), the FLT pin pull-down is released and the device is ready to restart 
automatically. When the device turns on again, it follows the usual DVDT limited start-up sequence.
The only exception to this is during Short-circuit fault when the device is configured for fast recovery using the 
SC_RETRY bit in the DEVICE_CONFIG register. In this case, the device turns off quickly and then automatically 
turns back on in a current limited manner. This allows the system to try and recover quickly from any transient 
faults. See Short-Circuit Protection section for more details.
For faults that are latched internally, power cycling the part or pulling the EN/UVLO pin voltage below VSD(F) 
clears the fault and the FLT pin is de-asserted. This action also clears the Auto-retry timer. Pulling the EN/UVLO 
just below the UVLO threshold has no impact on the device in this condition. This is true in case of latch-off and 
auto-retry configurations.
In a parallel eFuse configuration involving TPS25990 and TPS25985x, the fault response is determined by the 
TPS25990 as the primary device. However, if the primary device fails to register a fault, there is a fail-safe 
mechanism in the secondary device to take control and turn off the entire chain by pulling the SWEN pin low 
and enter a latch-off condition. Thereafter, the device can be turned on again only by power cycling VDD below 
VUVP(F) or by cycling EN/UVLO pin below VSD(F).
8.3.10.2 Power Good Indication (PG)
Power Good is an active high digital output which is asserted high to indicate when the device is in steady-state 
and capable of delivering maximum power.
Table 8-3. PG Indication Summary
Event or Condition
FET Status
PG Pin Status
PG Delay
Device disabled ( VEN < VUVLO)
OFF
L
tPGD
VIN Undervoltage (VIN < VUVP or 
VIN < VIN_UV_FLT)
OFF
L
VDD Undervoltage (VDD < VUVP
)
OFF
L
VIN Overvoltage (VIN > 
VIN_OV_FLT)
OFF
L
tPGD
Steady-state
ON
H
tPGA
Inrush
ON
L
tPGA
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
41
Product Folder Links: TPS25990



---

## Page 42

Table 8-3. PG Indication Summary (continued)
Event or Condition
FET Status
PG Pin Status
PG Delay
Transient overcurrent
ON
H
N/A
Circuit-breaker (persistent 
overcurrent followed by 
OC_TIMER expiry)
OFF
L
tOC_TIMER + tPGD
Fast-trip
OFF
L (VOUT < VOUT_PGTH)
H (VOUT > VOUT_PGTH)
tPGD
N/A
Overtemperature
Shutdown
L
tPGD
Note
GPIO1 pin is configured as PG output by default. Refer to GPIO_CONFIG_12 register for more details 
and configuration options.
After power up, PG is pulled low initially. The device initiates an inrush sequence in which the gate driver circuit 
starts charging the gate capacitance from the internal charge pump. When the FET gate voltage reaches the 
full overdrive indicating that the inrush sequence is complete and the device is capable of delivering full power, 
the PG pin is asserted high after a de-glitch time (tPGA). The PG assertion delay can be optionally increased by 
setting the PG_DVDT_DLY bit in the DEVICE_CONFIG register.
The PG is de-asserted if the output voltage falls below a threshold at any point during normal operation or the 
device detects a fault (except short-circuit). The PG de-assertion threshold can be digitally programmed through 
the VOUT_PGTH register. The PG de-assertion de-glitch time is tPGD.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
42
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 43

IN
0
Time
OUT
0
PG
VPG
0
VHGate
VOUT + 2.8 V
0
EN/UVLO
VUVLO(R)
0
Slew rate (dVdt) controlled 
startup/Inrush current limiting
VIN
Overload Event
IOCP
IINRUSH
0
tOC_TIMER
IOUT
Circuit-breaker action
tPGA
0
dVdt
Device Enabled
Overcurrent blanking timer expired
SWEN
0
VPGTH
(1)
  
(1)
 Depends on VOUT_PGTH register setting
tPGD
Figure 8-7. TPS25990 PG Timing Diagram
The PG is an open-drain pin and must be pulled up to an external supply.
Note
When there is no supply to the device, the PG pin is expected to stay low. However, there is no active 
pulldown in this condition to drive this pin all the way down to 0 V. If the PG pin is pulled up to an 
independent supply which is present even if the device is unpowered, there can be a small voltage 
seen on this pin depending on the pin sink current, which is a function of the pullup supply voltage and 
resistor. Minimize the sink current to keep this pin voltage low enough not to be detected as a logic 
HIGH by associated external circuits in this condition.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
43
Product Folder Links: TPS25990



---

## Page 44

8.3.10.3 Parallel Device Synchronization (SWEN)
The SWEN pin is a signal which is driven high when the FET must be turned ON. When the SWEN pin is driven 
low (internally or externally), it signals the driver circuit to turn OFF the FET. This pin serves both as a control 
and handshake signal and allows multiple devices in a parallel configuration to synchronize their FET ON and 
OFF transitions.
Table 8-4. SWEN Summary
Device State
FET Driver Status
SWEN
Steady-state
ON
H
Inrush
ON
H
Overtemperature shutdown
OFF
L
Auto-retry timer running
OFF
L
Device disabled ( VEN < VUVLO)
OFF
L
VIN Undervoltage (VIN < VUVP or VIN < 
VIN_UV_FLT)
OFF
L
VDD Undervoltage (VDD < VUVP)
OFF
L
Insertion delay
OFF
L
VIN Overvoltage (VIN > VIN_OV_FLT)
OFF
L
Transient overcurrent
ON
H
Circuit-breaker (persistent overcurrent 
followed by OC_TIMER expiry)
OFF
L
Fast-trip
OFF
L
Fast-trip response mono-shot running 
(DEVICE_CONFIG[13] = 1)
OFF
L
Fast-trip response mono-shot running 
(DEVICE_CONFIG[13] = 1)
ON
H
FET health fault
OFF
L
External fault (SWEN pulled low by 
secondary device in parallel chain)
OFF
L (held low by TPS25990 even if secondary 
device releases the pull down after some 
time)
The SWEN is an open-drain pin and must be pulled up through a 100 kΩ resistance to an external supply 
generated using the input voltage to the eFuse.
Note
1.
GPIO3 pin is configured as SWEN by default. Refer to GPIO_CONFIG_34 register for more 
details and configuration options.
2.
The SWEN pullup supply needs to be powered up before the eFuse is turned on. TI recommends 
to use a system standby rail which is derived from the input of the eFuse and is powered up 
before the eFuse. The exception to this is when TPS25990 is used as a standalone device and 
the GPIO3 pin is digitally configured for some function other than SWEN.
In a primary and secondary parallel configuration, the SWEN pin is used by the primary device to control the ON 
and OFF transitions of the secondary devices. At the same time, it allows the secondary devices to communicate 
any faults or other conditions which can prevent it from turning on the primary device.
To maintain state machine synchronization, the devices rely on SWEN level transitions as well as timing for 
handshakes. This ensures all the devices turn ON and OFF synchronously and in the same manner (for 
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
44
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 45

example, dVdt controlled or current limited start-up). There are also fail-safe mechanisms in the SWEN control 
and handshake logic to ensure the entire chain is turned off safely even if the primary device is unable to take 
control in case of a fault.
Note
TI recommends to keep the parasitic loading on the SWEN pin to a minimum to avoid synchronization 
timing issues.
8.3.11 Stacking Multiple eFuses for Unlimited Scalability
For systems needing higher current than supported by a single TPS25990, it is possible to connect TPS25990 
in parallel with one or more TPS25985x devices to deliver the desired total system current. Conventional eFuses 
do not share current evenly between themselves during steady-state due to mismatches in their path resistances 
(which includes the individual device RDSON variation from part to part, as well as the parasitic PCB trace 
resistance). This fact can lead to multiple problems in the system:
1.
Some devices always carry higher current as compared to other devices, which can result in accelerated 
failures in those devices and an overall reduction in system operational lifetime.
2.
As a result, thermal hotspots form on the board, devices, traces, and vias carrying higher current, leading 
to reliability concerns for the PCB. In addition, this problem makes thermal modeling and board thermal 
management more challenging for designers.
3.
The devices carrying higher current can hit their individual circuit-breaker threshold prematurely even while 
the total system load current is lower than the overall circuit-breaker threshold. This action can lead to false 
tripping of the eFuse chain during normal operation. This has the effect of lowering the current-carrying 
capability of the parallel chain. In other words, the current rating of the parallel eFuse chain needs to be 
de-rated as compared to the sum of the current ratings of the individual eFuses. This de-rating factor is 
a function of the path resistance mismatch, the number of devices in parallel, and the individual eFuse 
circuit-breaker accuracy.
The need for de-rating has an adverse impact on the system design. The designer is forced to make one of 
these trade-offs:
1.
Limit the operating load current of the system to below the derated overcurrent threshold of the eFuse chain. 
Essentially, it means lower platform capabilities than are supported by the power supply (PSU).
2.
Increase the overall circuit-breaker threshold to allow the desired system load current to pass through 
without tripping. As a consequence, the power supply (PSU) must be oversized to deliver higher currents 
during faults to account for the degradation of the overall circuit-breaker accuracy.
In either case, the system suffers from poor power supply utilization, which can mean sub-optimal system 
throughput or increased installation and operating costs, or both.
The TPS25990 and TPS25985x devices use a proprietary technique to address these problems and provide 
unlimited scalability of the solution by paralleling as many eFuses as needed. This is incorporated without 
significant current imbalance or any degradation in accuracy.
For this scheme to work correctly, the devices must be connected in the following manner:
•
The SWEN pins of all the devices are connected together.
•
The IMON pins of all the devices need to be connected together. The RIMON resistor value on the combined 
IMON pin can be calculated using Equation 11.
RIMON =
VIREF
GIMON × IOCP TOTAL
(11)
•
The IREF pins of all the devices need to be connected together. The TPS25990 generates the VIREF 
reference voltage for the whole chain using its internal DAC which can be programmed using PMBus® writes 
to the VIREF register. This allows the overcurrent protection thresholds to be dynamically adjusted during 
system operation. It is also possible to drive the IREF pin using a low impedance external precision voltage 
reference.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
45
Product Folder Links: TPS25990



---

## Page 46

•
The start-up current limit and active current sharing threshold for each device is set independently using the 
ILIM pin. The RILIM value for the TPS25990 must be selected based on the following equation.
RILIM 25990   =
1.1  × 4N −1 × RIMON 
9 
(12)
The RILIM value for each TPS25985x must be selected based on the following equation.
RILIM 25985   =
1.1  × 4N −1 × RIMON 
12 
(13)
Where N = Number of devices in parallel chain (1 × TPS25990 + (N - 1) × TPS25985)
Note
1.
The active current sharing scheme is engaged when the current through any eFuse while in 
steady-state exceeds the individual current sharing threshold set by the RILIM based on Equation 
14.
RILIM =
1.1 × VIREF
3 × GILIM × ILIM ACS
(14)
2.
The active current sharing scheme is disengaged when the total system current exceeds the 
system overcurrent (circuit-breaker) threshold (IOCP(TOTAL)).
8.3.11.1 Current Balancing During Start-Up
The TPS25990 implements a proprietary current balancing mechanism during start-up, which allows TPS25990 
and TPS25985x devices connected in parallel to share the inrush current and distribute the thermal stress 
across all the devices. This feature helps to complete a successful start-up with all the devices and avoid a 
scenario where some of the eFuses hit thermal shutdown prematurely. This in effect increases the inrush current 
capability of the parallel chain. The improved inrush performance makes it possible to support very large load 
capacitors on high current platforms without compromising the inrush time or system reliability.
8.3.12 General Purpose Comparators
The device has two (2) general purpose comparators (CMP1 and CMP2) whose inputs, thresholds and outputs 
can be digitally configured. This allows the user complete flexibility to use these comparators as per system 
needs.
Comparator-1:
•
The positive input of the comparator can be connected to either the TEMP/CMP pin, or internally to the IMON 
pin. Refer to the DEVICE_CONFIG register for more details and configuration options.
•
The comparator threshold can be digitally configured using an internal DAC (CMP1REF). Refer to the 
VCMPxREF register for more details and configuration options.
•
The comparator output can be digitally configured to be an output on one of the GPIO pins or used to trigger 
a fault which controls the FET ON/OFF status internally. Also, the comparator output polarity can be digitally 
configured. Refer to the GPIO_CONFIG_12, GPIO_CONFIG_34, and DEVICE_CONFIG registers for more 
details and configuration options.
Comparator-2:
•
The comparator's positive input is internally connected to the AUX pin.
•
The comparator threshold can be digitally configured using an internal DAC (CMP2REF). Refer to the 
VCMPxREF register for more details and configuration options.
•
The comparator output can be digitally configured to be an output on one of the GPIO pins or used to trigger 
a fault which controls the FET ON/OFF status internally. Also, the comparator output polarity can be digitally 
configured. Refer to the GPIO_CONFIG_12, GPIO_CONFIG_34, and DEVICE_CONFIG registers for more 
details and configuration options.
These comparators can be used for various purposes. Here is one such example:
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
46
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 47

•
Programmable fast overcurrent detect (PROCHOT#): Comparator-1 is configured to take IMON pin as 
the input and an appropriate reference voltage is set using the internal DAC (CMP1REF) in the VCMPxREF 
register. The comparator output is configured to be brought out on one of the General Purpose I/O pins. This 
pin is connected to the PROCHOT# pin of the processor. When the load current crosses the set threshold, 
the GPIOx goes low and signals the processor to throttle down immediately.
IMON
+
-
+
-
VIMON
CMPOUT1
DEVICE_CONFIG
VCMP1REF
4
CMPXREF
GPIOx
DEVICE_CONFIG
GPIOxx_CONFIG
Figure 8-8. Programmable Fast Overcurrent (PROCHOT#) Detect Using Internal Comparator and General 
Purpose I/O
Figure 8-9. PROCHOT# Response Using Internal Comparator
8.3.13 Output Discharge
The TPS25990 has an integrated output discharge function which discharges the capacitors on the OUT pin 
using an internal constant current (IQOD) sink path to GND. The output discharge function is activated when the 
EN/UVLO is held low (VSD(F) < VEN < VUVLO(F)) for a minimum interval (tQOD). The output discharge function 
helps to rapidly remove the residual charge left on large output capacitors and prevents the bus from staying at 
some undefined voltage for extended periods of time. The output discharge is disengaged when VOUT < VFB or if 
the device detects a fault.
The output discharge function can result in excessive power dissipation inside the device leading to an increase 
in junction temperature (TJ). The output discharge is disabled if the junction temperature (TJ) crosses the device 
overtemperature threshold (TSD) to avoid long-term degradation of the part.
Note
In a primary and secondary parallel eFuse configuration, TI recommends to hold EN/UVLO voltage 
below the VUVLO(F) threshold of the secondary eFuse to activate output discharge for all the eFuses in 
the chain.
8.3.14 PMBus® Digital Interface
The TPS25990 is a PMBus® target device with an embedded digital telemetry controller block. This enables 
bi-directional communication with a host controller using a pre-defined set of commands to control, configure, 
monitor and debug the system.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
47
Product Folder Links: TPS25990



---

## Page 48

The TPS25990 is compliant with PMBus® specifications version 1.3 Part I and Part II.
8.3.14.1 PMBus® Device Addressing
The TPS25990 uses 7-bit I2C device addressing. Up to 25 different addresses can be generated using different 
pin-strapping combinations on the ADDR0 and ADDR1 pins as shown in Table 8-5. This allows multiple devices 
to be connected to the same I2C bus.
Table 8-5. TPS25990 PMBus® Address Decoding
ADDR0 Pin
ADDR1 Pin
PMBus® Device Address
Open
Open
0x40 (Default). Can be overwritten with 
a user defined address programmed into 
PMBUS_ADDR register in the Config NVM 
space.
Open
GND
0x41
Open
75 kΩ to GND
0x42
Open
150 kΩ to GND
0x43
Open
267 kΩ to GND
0x44
GND
Open
0x45
GND
GND
0x46
GND
75 kΩ to GND
0x47
GND
150 kΩ to GND
0x48
GND
267 kΩ to GND
0x49
75 kΩ to GND
Open
0x4A
75 kΩ to GND
GND
0x4B
75 kΩ to GND
75 kΩ to GND
0x4C
75 kΩ to GND
150 kΩ to GND
0x4D
75 kΩ to GND
267 kΩ to GND
0x4E
150 kΩ to GND
Open
0x50
150 kΩ to GND
GND
0x51
150 kΩ to GND
75 kΩ to GND
0x52
150 kΩ to GND
150 kΩ to GND
0x53
150 kΩ to GND
267 kΩ to GND
0x54
267 kΩ to GND
Open
0x55
267 kΩ to GND
GND
0x56
267 kΩ to GND
75 kΩ to GND
0x57
267 kΩ to GND
150 kΩ to GND
0x58
267 kΩ to GND
267 kΩ to GND
0x59
Note
1.
TI recommends using low tolerance resistors on ADDR0 and ADDR1 to avoid address decoding 
errors.
2.
TI recommends connecting 10 pF capacitors in parallel with resistors on ADDR0 and ADDR1 pins 
to improve noise immunity for correct address decoding.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
48
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 49

8.3.14.2 SMBus™ Protocol
TPS25990 PMBus® interface is implemented over SMBus protocol using an I2C physical interface (SCL, SDA) 
for robust link. The following features are supported:
•
Fast mode support (up to 1 MHz I2C clock speed)
•
Bus timeout
•
Support for Byte, Word and Block Read/Write with and without PEC
•
Group command support
•
SMBus Alert output pin (SMBA#) to alert/interrupt the host during certain system warning/fault events.
•
Alert Response Address (ARA) support
8.3.14.3 SMBus™ Message Formats
TPS25990 supports the following SMBus message formats.
Note
All these commands can be used with or without the optional PEC byte.
S
Target Address
A
Data Byte
W
P
A
S
Target Address
A
Data Byte
W
A
PEC Byte
P
A
Controller to Target
Target to Controller
S = START, P = STOP, A = ACK,  W = WRITE
Figure 8-10. Send Byte
S
Target Address
A
Data Byte
R
P
N
S
Target Address
A
Data Byte
R
A
PEC Byte
P
N
Controller to Target
Target to Controller
S = START, P = STOP, A = ACK, N = NACK, R = READ
Figure 8-11. Receive Byte
S
Target Address
A
Data Byte
W
P
A
S
Target Address
A
Data Byte
W
A
PEC Byte
P
A
Controller to Target
Target to Controller
S = START, P = STOP, A = ACK,  W = WRITE
Command ID
A
Command ID
A
Figure 8-12. Write Byte
S
Target Address
A
Data Byte
R
P
N
S
Target Address
PEC Byte
P
N
Controller to Target
Target to Controller
S = START, RS = REPEATED START, P = STOP, A = ACK, N = NACK, R = READ, W = WRITE 
A
W
Command ID
A
RS
Target Address
A
Data Byte
R
A
A
W
Command ID
A
RS
Target Address
Figure 8-13. Read Byte
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
49
Product Folder Links: TPS25990



---

## Page 50

S
Target Address
A
Low Data Byte
W
P
A
S
Target Address
A
Low Data Byte
W
A
PEC Byte
P
A
Controller to Target
Target to Controller
S = START, P = STOP, A = ACK,  W = WRITE
Command ID
A
Command ID
A
High Data Byte
A
High Data Byte
A
Figure 8-14. Write Word
S
Target Address
A
Low Data Byte
R
P
A
S
Target Address
PEC Byte
P
N
Controller to Target
Target to Controller
S = START, RS = REPEATED START, P = STOP, A = ACK, N = NACK, R = READ, W = WRITE
A
W
Command ID
A
RS
Target Address
A
R
A
W
Command ID
A
RS
Target Address
High Data Byte
N
YXXX
Low Data Byte
A
High Data Byte
A
YXXX
Figure 8-15. Read Word
S
Target Address
A
Data Byte 1
R
P
A
S
Target Address
PEC Byte
P
N
Controller to Target
Target to Controller
S = START, RS = REPEATED START, P = STOP, A = ACK, N = NACK, R = READ, W = WRITE
A
W
Command ID
A
RS
Target Address
A
R
A
W
Command ID
A
RS
Target Address
Data Byte N
N
YXXX
YXXX
Byte Count (N)
A
Data Byte 2
A YXXX
Data Byte 1
A
Data Byte N
A
Byte Count (N)
A
Data Byte 2
A YXXX
Figure 8-16. Block Read
8.3.14.4 Packet Error Checking
TPS25990 supports optional PEC for all SMBus transactions.
When using packet error checking, an additional byte is added before the stop bit in each transaction.
For reads, the PEC byte is read from the target and the controller compares it to its own PEC byte calculation. 
For writes, the PEC byte is sent to the target from the controller, and the target compares it to its own PEC byte 
calculation.
After the comparison, if the PEC bytes differ, the target detects a PEC error. Thereafter, it takes the following 
actions as per the PMBus® Specification:
•
Does not respond to or act upon the command
•
Flushes the command code and any received data
•
Sets the CML_ERR bit in the STATUS_BYTE register
•
Sets the INV_PEC bit in the STATUS_CML register
and
•
Notifies the controller of a fault condition by pulling the SMBA# line low
8.3.14.5 Group Commands
As required by PMBus® specification, TPS25990 supports the Group Command Protocol. The Group Command 
Protocol is used to send commands to more than one PMBus® target device. The commands are sent in 
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
50
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 51

one continuous transmission. When the target devices detect the STOP condition that ends the sending of 
commands, they all begin executing the command they received.
It is not necessary that all target devices receive the same command.
No more than one command can be sent to any one device in one Group Command packet.
The Group Command Protocol must not be used with commands that require the receiving device to respond 
with data, such as the STATUS_BYTE command.
The Group Command Protocol uses REPEATED START conditions to separate commands for each device. 
The Group Command Protocol begins with the START condition, followed by the seven bit address of the first 
target device to receive a command and then by the write bit zero (0). The secondary device ACKs and the host 
controller sends a command with the associated data byte or bytes.
After the last data byte is sent to the first device, the host controller does NOT send a STOP condition. Instead, 
it sends a REPEATED START condition, followed by the seven bit address of the second device to receive a 
command, a write bit and the command code and the associated data bytes.
If, and only if, this is the last target device to receive a command, the host controller sends a STOP condition. 
Otherwise, the host controller sends a REPEATED START condition and starts transmitting the address of the 
third device to receive a command.
This process continues until all target devices have received their command codes, data bytes, and if used and 
supported, PEC byte. Then when all target devices have received their information, the host controller sends a 
STOP condition.
If PEC is used, then each target device’s sub-packet has its own PEC byte, computed only for that device’s 
sub-packet, including that target device’s address.
When the target devices who have received a command through this protocol detect the STOP condition, they 
are to begin execution immediately of the received command.
When using Packet Error Checking with the Group Command Protocol, the PEC byte is calculated using only 
the address, command and data bytes for each target device. For example, PEC 1 is calculated using Device 
Address 1 including the Write bit, Command Code 1, and the data associated with Command Code 1. PEC 1 
need only be calculated by the device at Device Address 1.
Similarly, PEC Byte 2 is calculated using Device Address 2 including the Write bit, Command Code 2, and 
the data associated with Command Code 2. Device 1 must not continue calculating PEC 1 after it sees the 
Repeated Start.
8.3.14.6 SMBus™ Alert Response Address (ARA)
When there are multiple target devices on the bus with their SMBA# pins also tied together, if one or more target 
devices assert the SMBA#, the host controller needs a way to identify those target devices on the bus. It does so 
using the ARA mechanism, which is initiated by sending a read command to the ARA broadcast address 0x0C.
S
ARA (0x0C)
A
Target Address
R
N
X
PEC Byte
P
N
Controller to Target
Target to Controller
S = START, P = STOP, A = ACK, N = NACK, R = READ
P
S
ARA (0x0C)
A
Target Address
R
A
X
Figure 8-17. ARA Message Protocol
The ARA Automatic Mask is a mask that is set in response to a successful ARA read. An ARA read operation 
returns the PMBus® address of the lowest addressed target device on the bus that has its SMBA# asserted. A 
successful ARA read means that this target device was the one that returned its address. When a target device 
responds to the ARA read, it releases the SMBA# signal. When the last target device on the bus that has an 
SMBA# set has successfully reported its address, the SMBA# signal will de-asserted.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
51
Product Folder Links: TPS25990



---

## Page 52

The way that the TPS25990 releases the SMBA# signal is by setting the ARA Automatic mask bit for all fault 
conditions present at the time of the ARA read. All status registers will still show the fault condition, but it will 
not generate an SMBA# alert on that fault again until the ARA Automatic mask is cleared by the host issuing the 
CLEAR_FAULTS command to this part. This must be done as a routine part of servicing an SMBA# condition on 
a part, even if the ARA read is not done.
8.3.14.7 PMBus® Commands
Table 8-6 shows the list of PMBus® commands supported by the TPS25990 eFuse.
Table 8-6. TPS25990 PMBus® Commands List
Command Name
Code
Type
Description
PMBus®Transaction
Default 
Value
Stored in 
On-chip 
Non-
volatile 
Memory
Stored in 
EEPROM
OPERATION
01h
Control
eFuse ON/OFF control
Read/Write byte w/ PEC
0x80
N/A
N/A
CLEAR_FAULTS
03h
Control
Clear all fault status bits and 
Blackbox RAM
Send byte w/ PEC
N/A
N/A
N/A
RESTORE_FACT
ORY_DEFAULTS
12h
Control
Initialize/Reset all 
configuration registers to their 
factory default values
Send byte w/ PEC
N/A
N/A
N/A
STORE_USER_A
LL
15h
Control
Store configuration values to 
NVM/EEPROM
Send byte w/ PEC
N/A
N/A
N/A
RESTORE_USER
_ALL
16h
Control
Initialize all configuration 
registers with the user 
programmed values stored in 
NVM/EEPROM
Send byte w/ PEC
N/A
N/A
N/A
BB_ERASE
F5h
Control
Erase Blackbox data in 
external EEPROM
Send byte w/ PEC
N/A
N/A
N/A
FETCH_BB_EEP
ROM
F6h
Control
Fetch Blackbox EEPROM 
contents into internal shadow 
registers
Send byte w/ PEC
N/A
N/A
N/A
POWER_CYCLE
D9h
Control
Power down output and 
restart after a delay 
programmed through the 
RETRY_CONFIG register
Send byte w/ PEC
N/A
N/A
N/A
MFR_WRITE_PR
OTECT
F8h
Control
Enable/Disable write 
protection for OPERATION & 
POWER_CYCLE commands, 
configuration registers, NVM, 
and EEPROM
Read/write byte w/ PEC
0x00
N/A
N/A
CAPABILITY
19h
Telemetry
Supported PMBus® features
Read byte w/ PEC
0xD0
Y
N
STATUS_BYTE
78h
Telemetry
Status register lower byte
Read byte w/ PEC
Undefined
N
N
STATUS_WORD
79h
Telemetry
Status register word
Read word w/ PEC
Undefined
N
Y
STATUS_OUT
7Ah
Telemetry
OUT bus status
Read byte w/ PEC
Undefined
N
N
STATUS_IOUT
7Bh
Telemetry
OUT current status
Read byte w/ PEC
Undefined
N
N
STATUS_INPUT
7Ch
Telemetry
IN bus status
Read byte w/ PEC
Undefined
N
Y
STATUS_TEMP
7Dh
Telemetry
Device temperature status
Read byte w/ PEC
Undefined
N
N
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
52
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 53

Table 8-6. TPS25990 PMBus® Commands List (continued)
Command Name
Code
Type
Description
PMBus®Transaction
Default 
Value
Stored in 
On-chip 
Non-
volatile 
Memory
Stored in 
EEPROM
STATUS_CML
7Eh
Telemetry
Communications, Memory, 
Logic status
Read byte w/ PEC
Undefined
N
N
STATUS_MFR_S
PECIFIC
80h
Telemetry
Manufacturer specific fault 
status
Read byte w/ PEC
Undefined
N
Y
STATUS_MFR_S
PECIFIC
_2
F3h
Telemetry
Additional manufacturer 
specific fault status
Read word w/ PEC
Undefined
N
N
PMBUS_REVISIO
N
98h
Telemetry
PMBus® Specifications Part I 
and II rev
1.3
Read byte w/ PEC
0x33
Y
N
MFR_ID
99h
Telemetry
Manufacturer name
Block read 2 bytes w/ 
PEC
"TI"
Y
N
MFR_MODEL
9Ah
Telemetry
Device name
Block read 8 bytes w/ 
PEC
"TPS25990" Y
N
MFR_REVISION
9Bh
Telemetry
Device revision
Block read 1 byte w/ 
PEC
0x01
Y
N
READ_VIN
88h
Telemetry
Input voltage
Read word w/ PEC
Undefined
N
N
READ_VOUT
8Bh
Telemetry
Output voltage
Read word w/ PEC
Undefined
N
N
READ_IIN
89h
Telemetry
Input current
Read word w/ PEC
Undefined
N
N
READ_TEMPERA
TURE_1
8Dh
Telemetry
Device temperature
Read word w/ PEC
Undefined
N
N
READ_VAUX
D0h
Telemetry
Auxiliary analog input voltage
Read word w/ PEC
Undefined
N
N
READ_PIN
97h
Telemetry
Instantaneous input power
Read word w/ PEC
Undefined
N
N
READ_EIN
86h
Telemetry
Accumulated input energy
Block read 6 bytes w/ 
PEC
Undefined
N
N
READ_VIN_AVG
DCh
Telemetry
Average input voltage
Read word w/ PEC
Undefined
N
N
READ_VIN_MIN
D1h
Telemetry
Minimum input voltage
Read word w/ PEC
Undefined
N
N
READ_VIN_PEAK D2h
Telemetry
Peak input voltage
Read word w/ PEC
Undefined
N
Y
READ_VOUT_AV
G
DDh
Telemetry
Average output voltage
Read word w/ PEC
Undefined
N
N
READ_VOUT_MI
N
DAh
Telemetry
Minimum output voltage
Read word w/ PEC
Undefined
N
N
READ_IIN_AVG
DEh
Telemetry
Average input current
Read word w/ PEC
Undefined
N
N
READ_IIN_PEAK
D4h
Telemetry
Peak input current
Read word w/ PEC
Undefined
N
Y
READ_TEMP_AV
G
D6h
Telemetry
Average device temperature
Read word w/ PEC
Undefined
N
N
READ_TEMP_PE
AK
D7h
Telemetry
Peak device temperature
Read word w/ PEC
Undefined
N
Y
READ_PIN_AVG
DFh
Telemetry
Average input power
Read word w/ PEC
Undefined
N
N
READ_PIN_PEAK D5h
Telemetry
Peak input power
Read word w/ PEC
Undefined
N
N
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
53
Product Folder Links: TPS25990



---

## Page 54

Table 8-6. TPS25990 PMBus® Commands List (continued)
Command Name
Code
Type
Description
PMBus®Transaction
Default 
Value
Stored in 
On-chip 
Non-
volatile 
Memory
Stored in 
EEPROM
READ_SAMPLE_
BUF
D8h
Telemetry
ADC sample buffer
Block read 64 bytes w/ 
PEC
Undefined
N
N
READ_BB_RAM
FDh
Telemetry
Blackbox RAM registers
Block read 7 bytes w/ 
PEC
Undefined
N
Y
READ_BB_EEPR
OM
F4h
Telemetry
Blackbox EEPROM content
Block read 16 bytes w/ 
PEC
Undefined
N
Y
BB_TIMER
FAh
Telemetry
Blackbox tick timer
Read byte w/ PEC
Undefined
N
Y
PMBUS_ADDR
FBh
Configuration
PMBus® device address for 
ADDR0 = Open and ADDR1 
= Open setting
Read/write byte w/ PEC
0x40
Y
Y
VIN_UV_WARN
58h
Configuration
Input undervoltage warning 
threshold
Read/write word w/ PEC 0x0095
N
N
VIN_UV_FLT
59h
Configuration
Input undervoltage fault 
threshold
Read/write word w/ PEC 0x008D
Y
Y
VIN_OV_WARN
57h
Configuration
Input overvoltage warning 
threshold
Read/write word w/ PEC 0x00A5
N
N
VIN_OV_FLT
55h
Configuration
Input overvoltage fault 
threshold
Read/write word w/ PEC 0x000E
Y
Y
VOUT_UV_WARN 43h
Configuration
Output undervoltage warning 
threshold
Read/write word w/ PEC 0x0095
N
N
VOUT_PGTH
5Fh
Configuration
Output threshold for Power 
Good de-assertion
Read/write word w/ PEC 0x008D
Y
Y
OT_WARN
51h
Configuration
Overtemperature warning 
threshold
Read/write word w/ PEC 0x007E
N
N
OT_FLT
4Fh
Configuration
Overtemperature fault 
threshold
Read/write word w/ PEC 0x0085
Y
Y
PIN_OP_WARN
6Bh
Configuration
Input overpower warning 
threshold
Read/write word w/ PEC 0x00FF
N
N
IIN_OC_WARN
5Dh
Configuration
Input overcurrent warning 
threshold
Read/write word w/ PEC 0x00FF
N
N
VIREF
E0h
Configuration
Reference voltage for current 
regulation and protection 
blocks
Read/write byte w/ PEC
0x32
Y
Y
GPIO_CONFIG_1
2
E1h
Configuration
GPIO1 & GPIO2 configuration Read/write byte w/ PEC
0x00
Y
Y
GPIO_CONFIG_3
4
E2h
Configuration
GPIO3 & GPIO4 configuration Read/write byte w/ PEC
0x00
Y
Y
ALERT_MASK
DBh
Configuration
SMB Alert assertion mask
Read/write word w/ PEC 0x0100
N
N
FAULT_MASK
E3h
Configuration
FLT assertion mask
Read/write word w/ PEC 0x0000
Y
Y
DEVICE_CONFIG E4h
Configuration
Device configuration
Read/write word w/ PEC 0x1400
Y
Y
BB_CONFIG
E5h
Configuration
Blackbox configuration
Read/write byte w/ PEC
0x00
Y
Y
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
54
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 55

Table 8-6. TPS25990 PMBus® Commands List (continued)
Command Name
Code
Type
Description
PMBus®Transaction
Default 
Value
Stored in 
On-chip 
Non-
volatile 
Memory
Stored in 
EEPROM
OC_TIMER
E6h
Configuration
Transient overcurrent 
blanking timer
Read/write byte w/ PEC
0x14
N
N
RETRY_CONFIG
E7h
Configuration
Auto-retry configuration
Read/write byte w/ PEC
0x84
Y
Y
ADC_CONFIG_1
E8h
Configuration
ADC Configuration
Read/write byte w/ PEC
0x00
N
N
ADC_CONFIG_2
E9h
Configuration
ADC Configuration
Read/write byte w/ PEC
0x00
N
N
PK_MIN_AVG
EAh
Configuration
Peak/Min/Average 
configuration
Read/write byte w/ PEC
0x00
N
N
VCMPxREF
EBh
Configuration
General purpose comparator 
reference thresholds
Read/write byte w/ PEC
0xFF
Y
Y
PSU_VOLTAGE
ECh
Configuration
PSU nominal voltage
Read/write byte w/ PEC
0x9D
N
N
CABLE_DROP
EDh
Configuration
Maximum cable voltage drop 
expected
Read/write byte w/ PEC
0xFF
N
N
GPDAC1
F0h
Configuration
General purpose DAC1 
output current
Read/write byte w/ PEC
0x00
Y
Y
GPDAC2
F1h
Configuration
General purpose DAC1 
output voltage
Read/write byte w/ PEC
0x00
Y
Y
INS_DLY
F9h
Configuration
Insertion delay
Read/write byte w/ PEC
0x00
Y
Y
8.3.14.7.1 Detailed Descriptions of PMBus® Commands
8.3.14.7.1.1 OPERATION (01h, Read/Write Byte)
OPERATION is a PMBus® standard command that controls the FET inside the eFuse in conjunction with the 
input from the EN/UVLO pin. This command may be used to switch the eFuse ON and OFF under host control. It 
is also used to re-enable the eFuse after a fault-triggered shutdown.
This command uses the PMBus® read or write byte protocol.
Table 8-7. OPERATION Command Description
Bit
Name
Value
Description
Default
Access
7
ON
Enable
Read/Write
1
eFuse output enabled
1
0
eFuse output disabled
6:0
RESERVED
0000000
N/A
0000000
Note
•
This command should be preceded by the MFR_WRITE_PROTECT command to unlock the 
device first to prevent accidental/spurious writes.
•
Writing an OFF command followed by an ON command will clear all the fault and warning bits in 
the status registers. Writing only an ON command after a fault-triggered shutdown will not clear the 
status registers.
•
OFF command engages quick output discharge (QOD).
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
55
Product Folder Links: TPS25990



---

## Page 56

8.3.14.7.1.2 CLEAR_FAULTS (03h, Send Byte)
CLEAR_FAULTS is a standard PMBus® command that resets all latched warning/fault/status flags and de-
asserts the SMBA# signal. If a fault or warning condition still exists when the CLEAR_FAULTS command 
is executed, the SMBA# signal may re-assert almost immediately or may not de-assert at all. Issuing the 
CLEAR_FAULTS command alone will not cause the eFuse to switch back ON in the event of a turn-off due to 
any fault. That must be done by issuing an OPERATION OFF command followed by OPERATION ON command 
or a POWER_CYCLE command after the fault condition is cleared, or through an auto-retry sequence. This 
command also clears the BB_RAM contents and resets the BB_TIMER register to zero (0). This command has 
no effect on Blackbox EEPROM memory contents.
This command uses the PMBus® send byte protocol. There is no data byte for this command. This command is 
write only.
Note
TI recommends sending the CLEAR_FAULTS command after every successful power-up of the 
device to clear the warning and fault bits set in the status registers during initialization, if any. This also 
ensures the SMBA# is de-asserted.
8.3.14.7.1.3 RESTORE_FACTORY_DEFAULTS (12h, Send Byte)
RESTORE_FACTORY_DEFAULTS is a standard PMBus® command that initializes or resets all 
the configuration RAM registers to their hardware defaults. Read the INIT_DONE bit in the 
STATUS_MFR_SPECIFIC_2 register to check if initialization was completed successfully.
This command uses the PMBus® send byte protocol. There is no data byte for this command. This command is 
write only.
Note
This command should be preceded by the MFR_WRITE_PROTECT command to unlock the device 
first to prevent accidental/spurious writes.
8.3.14.7.1.4 STORE_USER_ALL (15h, Send Byte)
STORE_USER_ALL is a standard PMBus® command that writes the contents of the certain Configuration RAM 
registers to their respective non-volatile configuration memory (NVM) or EEPROM locations. The TPS25990 
has two (2) one-time programmable banks in the NVM which are available to the users to store their custom 
configurations. This command will try to write to NVM Bank-1 first if it’s not programmed yet. If NVM Bank-1 is 
already programmed, it will attempt to write to NVM Bank-2 if it’s not programmed. If NVM Bank-2 is already 
programmed, it will attempt to write to Page-2 of an external EEPROM if available and configured.
This command uses the PMBus® send byte protocol. There is no data byte for this command. This command is 
write only.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
56
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 57

Note
•
This command should be preceded by the MFR_WRITE_PROTECT command to unlock the 
device first to prevent accidental/spurious writes.
•
The external EEPROM needs to be enabled by setting the EXT_EEPROM bit in the 
DEVICE_CONFIG register. In addition, it is done by configuring two (2) of the four (4) GPIOs 
as EECLK and EEDATA appropriately in the GPIO_CONFIG_12 and GPIO_CONFIG_34 registers. 
Make sure those two (2) selected GPIO pins are physically connected to the EEPROM clock and 
data pins respectively on the board.
•
The MEMORY_FLT bit in the STATUS_CML register gets set if the STORE_USER_ALL 
command is unsuccessful. TI recommends reading the STATUS_CML register after sending the 
STORE_USER_ALL command to verify whether it was successful or not.
•
The NVM inside the TPS25990x eFuse only has two (2) one-time programmable banks available 
for user programming. If an external EEPROM is not used, before sending the STORE_USER_ALL 
command the user should ensure that at least one bank of internal NVM is available for 
programming by reading the CONFIG_NVM_STAT bit in the STATUS_MFR_SPECIFIC_2 register.
8.3.14.7.1.5 RESTORE_USER_ALL (16h, Send Byte)
RESTORE_USER_ALL is a standard PMBus® command that initializes certain configuration RAM registers to 
their user programmed values from NVM or EEPROM.
This command uses the PMBus® send byte protocol. There is no data byte for this command. This command is 
write only.
The device follows the following sequence in response to the command:
•
If NVM Bank-2 is programmed, the device will read from Bank-2. If the computed checksum matches the 
saved original checksum, the NVM configuration values will be loaded into the respective registers.
•
Next, if an external EEPROM is connected as described in Section 8.3.14.7.1.4, and there is a valid 
configuration file in Page-2 of the connected EEPROM, the device will try to read from EEPROM Page-2. 
If the calculated checksum matches the stored checksum, the configuration values from EEPROM will be 
transferred into the device configuration registers.
•
If NVM Bank-2 is not programmed, the device reads NVM Bank-1. If the calculated checksum matches the 
stored checksum, NVM configuration values will be loaded into the configuration registers. If NVM Bank-1 is 
not programmed, factory default values will be retained in the registers.
Note
•
This command should be preceded by the MFR_WRITE_PROTECT command to unlock the 
device first to prevent accidental/spurious writes.
•
Read the MEMORY_FLT bit in the STATUS_CML register and the INIT_DONE bit in the 
STATUS_MFR_SPECIFIC_2 register to check if initialization was completed successfully.
8.3.14.7.1.6 BB_ERASE (F5h, Send Byte)
BB_ERASE is a manufacturer specific command which fills the EEPROM Page-0 (where Blackbox information is 
stored) with all zeroes (0).
This command uses the PMBus® send byte protocol. There is no data byte for this command. This command is 
write only.
Note
This command should be preceded by the MFR_WRITE_PROTECT command to unlock the device 
first to prevent accidental accidental/spurious writes.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
57
Product Folder Links: TPS25990



---

## Page 58

8.3.14.7.1.7 FETCH_BB_EEPROM (F6h, Send Byte)
FTECH_BB_EEPROM is a manufacturer specific command which loads the Blackbox contents from the external 
EEPROM (Page-0) into the Blackbox shadow registers internal to the device.
Those values can then be read back through PMBus® using the READ_BB_EEPROM command.
This command uses the PMBus® send byte protocol. There is no data byte for this command. This command is 
write only.
8.3.14.7.1.8 POWER_CYCLE (D9h, Send Byte)
POWER_CYCLE is a manufacturer specific command used to power down the output and power ON after a 
delay. The delay can be configured using the RETRY_CONFIG register.
This command uses the PMBus® send byte protocol. There is no data byte for this command. This command is 
write only.
Note
•
This command should be preceded by the MFR_WRITE_PROTECT command to unlock the 
device first to prevent accidental/spurious writes.
•
If the device is turned OFF due a fault, issuing a POWER_CYCLE command alone doesn't alter 
the state of the device. This command should be preceded by a CLEAR_FAULTS command.
•
This command only attempts to reset the power path. Device state and register contents are 
preserved.
•
This command also engages quick output discharge (QOD) to discharge the output load and 
checks if the output is fully discharged before starting again.
8.3.14.7.1.9 MFR_WRITE_PROTECT (F8h, Read/Write Byte)
MFR_WRITE_PROTECT is a manufacturer specific command used to lock or unlock access to the 
configuration registers, NVM and EEPROM to prevent accidental/spurious PMBus® writes from altering 
the device configuration. It also blocks access to the OPERATION, RESTORE_FACTORY_DEFAULTS, 
STORE_USER_ALL, RESTORE_USER_ALL, BB_ERASE, and POWER_CYCLE commands to prevent 
accidental/spurious PMBus® writes from altering the device state. The device is locked by default after power up 
or enable recycling.
This command uses the PMBus® read or write byte protocol.
A valid unlock command contains a data byte with Bit[7] equal to one (1) followed by a 7-bit password that 
matches a predefined pattern of 0x0100010. Writing 0xA2h in the MFR_WRITE_PROTECT register unlocks the 
device. Writing 0x00h in the MFR_WRITE_PROTECT register locks the device.
Note
Writing a data byte other than 0xA2h or 0x00h in the MFR_WRITE_PROTECT register will not change 
the lock status of the device, but will generate a CML error and set the INV_DATA bit in STATUS_CML 
register.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
58
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 59

Table 8-8. MFR_WRITE_PROTECT Command Description
Bit
Name
Value
Description
Default
Access
7
UNLOCK
Lock Bit
Read/Write
0
Configuration 
register/NVM space 
locked
0
1
Configuration 
register/NVM space 
unlocked
6:0
PWD
Password
0000000
Configuration 
register/NVM space 
locked
0000000
0100010
Configuration 
register/NVM space 
unlocked
8.3.14.7.1.10 CAPABILITY (19h, Read Byte)
CAPABILITY is a standard PMBus® command that allows a host system to determine some key capabilities of a 
PMBus® device.
This command uses the PMBus® read byte protocol. There is one data byte formatted as shown in Table 8-9.
Table 8-9. CAPABILITY Register Description
Bit
Name
Value
Description
Default
Access
7
PEC Support
Packet Error 
Correction (PEC) 
support
Read
1
PEC supported
1
0
PEC not supported
6:5
Bus Speed
Maximum bus 
interface speed
00
100 kHz
10
01
400 kHz
10
1 MHz
11
Reserved for future 
use
4
SMBA/ARA
SMB Alert/Alert 
Response Address 
support
1
SMBA/ARA 
supported
1
0
SMBA/ARA not 
supported
3:0
Reserved
0000
Reserved
0000
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
59
Product Folder Links: TPS25990



---

## Page 60

8.3.14.7.1.11 STATUS_BYTE (78h, Read Byte)
The TPS25990 implements all PMBus® status registers relevant to an eFuse/Hot-swap power controller. Figure 
8-18 shows a bit map of the TPS25990 status register.
STATUS_BYTE is a standard PMBus® command that returns one byte of information with a summary of the 
most critical faults.
This command uses the PMBus® read byte protocol.
To clear bits in this register, the underlying faults must be removed and the CLEAR_FAULTS command must be 
issued by the host controller.
Table 8-10. STATUS_BYTE Register Description
Bit
Name
Value
Description
Default
Access
7
BUSY
Device busy status
Read
1
Device is busy
0
0
Device is not busy
6
FET_OFF
FET drive status
1
FET gate driver 
disabled
0
0
FET gate drive 
enabled
5:4
Reserved
00
Reserved
00
3
VIN_UV_FLT
VIN undervoltage
1
VIN UV fault detected
0
0
VIN UV fault not 
detected
2
STATUS_TEMP
Overtemperature fault
1
Active bits set 
in STATUS_TEMP 
register
0
0
No active bits set 
in STATUS_TEMP 
register
1
CML_ERR
Communication, 
Memory or Logic error
1
Active bits set 
in STATUS_CML 
register
0
0
No active bits set 
in STATUS_CML 
register
0
NONE_OF_THE_AB
OVE
1
An event other than 
the ones listed in bits 
7:1 has occurred
0
0
An event other than 
the ones listed in bits 
7:1 has not occurred
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
60
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 61

8.3.14.7.1.12 STATUS_WORD (79h, Read Word)
STATUS_WORD is a standard PMBus® command that returns two bytes of information with a summary of the 
eFuse fault conditions.
This command uses the PMBus® read word protocol.
To clear the bits in this register, the underlying faults must be removed and the CLEAR_FAULTS command must 
be issued by the host controller.
The low byte of STATUS_WORD is the same register as the STATUS_BYTE command. The STATUS_WORD 
register contents are described in Figure 8-18 and Table 8-11.
STATUS_WORD (79h)
7
6
5
4
3
2
1
0
7
6
5
4
3
2
1
0
OUT_STATUS
IOUT_STATUS
INPUT_STATUS
MFR_STATUS
UNKNOWN
RESERVED
PGOODB
RESERVED
UNKNOWN
CML_ERR
TEMP_FLT
VIN_UV_FLT
BUSY
RESERVED
RESERVED
FET_OFF
High Byte
Low Byte [STATUS_BYTE (78h)]
STATUS_CML 
Register (7Eh)
STATUS_MFR_
SPECIFIC_2 
Register (F3h)
STATUS_OUT 
Register (7Ah)
STATUS_IOUT 
Register (7Bh)
STATUS_MFR_
SPECIFIC 
Register (80h)
STATUS_IN 
Register (7Ch)
STATUS_TEMP 
Register (7Dh)
Figure 8-18. Status Register Bit Map
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
61
Product Folder Links: TPS25990



---

## Page 62

Table 8-11. STATUS_WORD Register Description
Bit
Name
Value
Description
Default
Access
15
OUT_STATUS
OUTPUT fault status
Read
1
Active bits set in 
the STATUS_OUT 
register
0
0
No active bits set 
in the STATUS_OUT 
register
14
IOUT_STATUS
IOUT fault status
1
Active bits set in 
the STATUS_IOUT 
register
0
0
No active bits set 
in the STATUS_IOUT 
register
13
INPUT_STATUS
INPUT fault status
1
Active bits set in 
the STATUS_INPUT 
register
0
0
No active bits set in 
the STATUS_INPUT 
register
12
MFR_STATUS
Manufacturer specific 
fault status
1
Active bits set 
in the STATUS 
_MFR_SPECIFIC 
register
0
0
No active bits set 
in the STATUS 
_MFR_SPECIFIC 
register
11
PGOODB
Power Good status
1
PGOOD de-asserted
1
0
PGOOD asserted
10:9
Reserved
00
Reserved
00
8
UNKNOWN
1
An event other than 
the ones listed in bits 
15:1 has occurred
0
0
An event other than 
the ones listed in bits 
15:1 has not occurred
7:0
Same as STATUS_BYTE register
Figure 8-19 depicts the relationship between the STATUS_BYTE register, the STATUS_WORD register and the 
more detailed status registers.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
62
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 63

Based on the information in these bytes, the host can get more insight by reading the appropriate status 
registers.
7
6
5
4
3
2
1
0
STATUS_CML
INV_CMD
INV_DATA
INV_PEC
MEMORY_FLT
RESERVED
RESERVED
RESERVED
OTHER
7
6
5
4
3
2
1
0
STATUS_OUT
RESERVED
RESERVED
VOUT_UV_WARN
RESERVED
RESERVED
RESERVED
RESERVED
RESERVED
7
6
5
4
3
2
1
0
STATUS_TEMP
OT_FLT
OT_WARN
RESERVED
RESERVED
RESERVED
RESERVED
RESERVED
RESERVED
7
6
5
4
3
2
1
0
STATUS_INPUT
VIN_OV_FLT
VIN_OV_WARN
VIN_UV_WARN
VIN_UV_FLT
RESERVED
OC_FLT
OC_WARN
IN_OP_WARN
7
6
5
4
3
2
1
0
STATUS_MFR_ 
SPECIFIC
FET_FAULT_GD
FET_FAULT_GS
FET_FAULT_DS
BB_RAM_FULL
SOA_FLT
EXT_FLT
CMP2_FLT
CMP1_FLT
15
14
13
12
11
10
9
8
STATUS_MFR_ 
SPECIFIC_2
RESERVED
RESERVED
PGOODB
SPFAIL
SC_FLT
OC_DET
EIN_OF_WARN
VIN_TRAN
7
6
5
4
3
2
1
0
EE_DET
EE_PROG
AVG_DONE
VIN_CABLE_FLT
RETRY_REC
POWER_CYCLE_REC
INIT_DONE
CONFIG_NVM_STAT
7
6
5
4
3
2
1
0
STATUS_IOUT
RESERVED
RESERVED
RESERVED
RESERVED
RESERVED
RESERVED
RESERVED
RESERVED
7
6
5
4
3
2
1
0
STATUS_WORD 
(Upper Byte)
OUT_STATUS
IOUT_STATUS
INPUT_STATUS
MFR_STATUS
PGOODB
RESERVED
RESERVED
UNKNOWN
7
6
5
4
3
2
1
0
STATUS_BYTE
(Lower byte of 
STATUS_WORD)
BUSY
FET_OFF
RESERVED
RESERVED
VIN_UV_FLT
STATUS_TEMP
CML_ERR
UNKNOWN
Figure 8-19. Summary of the Status Registers
8.3.14.7.1.13 STATUS_OUT (7Ah, Read Byte)
STATUS_OUT is a standard PMBus® command that returns one data byte with contents as shown in Table 
8-12.
This command uses the PMBus® read byte protocol.
To clear the bits in this register, the underlying faults must be removed and the CLEAR_FAULTS command must 
be issued by the host controller.
Table 8-12. STATUS_OUT Register Description
Bit
Name
Value
Description
Default
Access
7:6
Reserved
00
Reserved
00
Read
5
VOUT_UV_WARN
VOUT undervoltage 
warning
1
VOUT UV warning 
threshold crossed
0
0
VOUT UV warning 
threshold not crossed
4:0
Reserved
00
Reserved
00
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
63
Product Folder Links: TPS25990



---

## Page 64

8.3.14.7.1.14 STATUS_IOUT (7Bh, Read Byte)
STATUS_IOUT is a standard PMBus® command that returns one data byte with contents as shown in Table 
8-13.
Table 8-13. STATUS_IOUT Register Description
Bit
Name
Value
Description
Default
Access
7:0
Reserved
00000000
Reserved
000000000
Read
Note
The input and output current information is identical for this device, so all the bits in this register are 
reserved. Refer to the STATUS_INPUT register instead for status information.
8.3.14.7.1.15 STATUS_INPUT (7Ch, Read Byte)
STATUS_INPUT is a standard PMBus® command that returns the status flags related to input voltage, current, 
and power as shown in Table 8-14.
This command uses the PMBus® read byte protocol.
To clear the bits in this register, the underlying faults must be removed and the CLEAR_FAULTS command must 
be issued by the host controller.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
64
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 65

Table 8-14. STATUS_INPUT Register Description
Bit
Name
Value
Description
Default
Access
7
VIN_OV_FLT
VIN overvoltage fault
Read
1
VIN OV fault 
threshold crossed
0
0
VIN OV fault 
threshold not crossed
6
VIN_OV_WARN
VIN overvoltage 
warning
1
VIN OV warning 
threshold crossed
0
0
VIN OV warning 
threshold not crossed
5
VIN_UV_WARN
VIN undervoltage 
warning
1
VIN UV warning 
threshold crossed
0
0
VIN UV warning 
threshold not crossed
4
VIN_UV_FLT
VIN undervoltage 
fault
1
VIN UV fault 
threshold crossed
0
0
VIN UV fault 
threshold not crossed
3
Reserved
0
Reserved
0
2
OC_FLT
Overcurrent fault 
(Inrush & steady-
state)
1
Input current crossed 
overcurrent fault 
threshold (Inrush) or 
OC_TIMER expired 
after input current 
crossed overcurrent 
fault threshold 
(steady-state)
0
0
Input current 
below overcurrent 
fault threshold or 
OC_TIMER not 
expired
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
65
Product Folder Links: TPS25990



---

## Page 66

Table 8-14. STATUS_INPUT Register Description (continued)
Bit
Name
Value
Description
Default
Access
1
OC_WARN
Overcurrent warning 
(Inrush & steady-
state)
1
Input current crossed 
overcurrent warning 
threshold
0
0
Input current below 
overcurrent warning 
threshold
0
IN_OP_WARN
Overpower warning
1
Input overpower 
warning threshold 
crossed
0
0
Input overpower 
warning threshold not 
crossed
8.3.14.7.1.16 STATUS_TEMP (7Dh, Read Byte)
STATUS_TEMP is a standard PMBus® command that returns the status flags related to the overtemperature 
fault and warning as shown in Table 8-15.
This command uses the PMBus® read byte protocol.
To clear the bits in this register, the underlying faults must be removed and the CLEAR_FAULTS command must 
be issued by the host controller.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
66
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 67

Table 8-15. STATUS_TEMP Register Description
Bit
Name
Value
Description
Default
Access
7
OT_FLT
Overtemperature fault
Read
1
Device temperature 
crossed 
overtemperature 
fault threshold (TSD/
OT_FLT)
0
0
Device 
temperature below 
overtemperature 
fault threshold (TSD/
OT_FLT)
6
OT_WARN
Overtemperature 
warning
1
Device temperature 
crossed 
overtemperature 
warning threshold
0
0
Device 
temperature below 
overtemperature 
warning threshold
5:0
Reserved
000000
Reserved
000000
8.3.14.7.1.17 STATUS_CML (7Eh, Read Byte)
STATUS_CML is a standard PMBus® command that returns the status flags related to communication, logic, 
and memory faults as shown in Table 8-16.
This command uses the PMBus® read byte protocol.
To clear the bits in this register, the underlying faults must be removed and the CLEAR_FAULTS command must 
be issued by the host controller.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
67
Product Folder Links: TPS25990



---

## Page 68

Table 8-16. STATUS_CML Register Description
Bit
Name
Value
Description
Default
Access
7
INV_CMD
Command status
Read
1
Invalid/unsupported 
command received
0
0
Valid/supported 
command received
6
INV_DATA
Data status
1
Invalid/unsupported 
data received
0
0
Valid/supported data 
received
5
INV_PEC
Packet Error Check 
status
1
PEC failed
0
0
PEC passed
4
MEMORY_FLT
Memory fault status
1
Memory related fault - 
Configuration Memory 
Content Invalid 
(Empty or corrupted) 
OR 
STORE_USER_ALL 
or 
RESTORE_USER_A
LL commands 
unsuccessful
0
0
No memory related 
fault
3:1
Reserved
000
Reserved
000
0
OTHER
Other communications failure
0
Note
The SMBA# signal may be asserted due to a CML fault if the CML_ERR is unmasked in the 
ALERT_MASK register. If there are multiple PMBus® devices on the same bus, TI recommends 
unmasking the CML_ERR only while communicating with the TPS25990 and masking it at all other 
times. This prevents TPS25990 from asserting the SMBA# due to CML faults generated by other 
devices on the bus.
8.3.14.7.1.18 STATUS_MFR_SPECIFIC (80h, Read Byte)
STATUS_MFR_SPECIFIC is a standard PMBus® command that returns manufacturer-specific status 
information as shown in Table 8-17.
This command uses the PMBus® read byte protocol.
To clear the bits in this register, the underlying faults must be removed and the CLEAR_FAULTS command must 
be issued by the host controller.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
68
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 69

Table 8-17. STATUS_MFR_SPECIFIC Register Description
Bit
Name
Value
Description
Default
Access
7
FET_FAULT_GD
FET fault type
Read
1
Gate to drain fault
0
0
No gate to drain fault
6
FET_FAULT_GS
FET fault type
1
Gate to source fault
0
0
No gate to source 
fault
5
FET_FAULT_DS
FET fault type
1
Drain to source fault
0
0
No drain to source 
fault
4
BB_RAM_FULL
BB RAM fill status
1
Seven (7) events 
have been recorded
0
0
Seven (7) events not 
yet recorded
3
SOA_FLT
FET SOA status
1
Device turned off due 
to SOA limit violation
0
0
FET operating within 
SOA limit
2
EXT_FLT
External fault
1
Device turned off due 
to SWEN pin being 
pulled low externally 
by another device in 
parallel chain
0
0
SWEN pin not pulled 
low externally by 
another device in 
parallel chain
1
CMP2_FLT
AUX (CMP2) 
comparator fault 
indication
1
CMP2 fault detected
0
0
CMP2 fault not 
detected
0
CMP1_FLT
TEMP/CMP (CMP1) 
comparator fault 
indication
1
CMP1 fault detected
0
0
CMP1 fault not 
detected
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
69
Product Folder Links: TPS25990



---

## Page 70

8.3.14.7.1.19 STATUS_MFR_SPECIFIC_2 (F3h, Read Word)
STATUS_MFR_SPECIFIC_2 is a manufacturer specific command which returns additional status information as 
shown in Table 8-18.
This command uses the PMBus® read word protocol.
To clear the bits in this register, the underlying faults must be removed and the CLEAR_FAULTS command must 
be issued by the host controller.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
70
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 71

Table 8-18. STATUS_MFR_SPECIFIC_2 Register Description
Bit
Name
Value
Description
Default
Access
15:14
Reserved
00
Reserved
00
Read
13
PGOODB
PGOOD status
1
PGOOD low
0
0
PGOOD high
12
SPFAIL
Single point failure 
(ILIM/IMON/IREF)
1
Single point failure 
detected
0
0
Single point failure 
not detected
11
SC_FLT
Short-circuit fault
1
Short-circuit fault 
threshold crossed
0
0
Short-circuit fault 
threshold not crossed
10
OC_DET
Overcurrent detected 
(Inrush & steady-
state)
1
Input current crossed 
overcurrent fault 
threshold but 
OC_TIMER not 
expired
0
0
Input current below 
overcurrent fault 
threshold
9
EIN_OF_WARN
EIN register overflow
1
EIN register 
overflowed
0
0
EIN register not 
overflowed
8
VIN_TRAN
VIN transient warning 
indication
1
VIN transient 
detected
0
0
VIN transient not 
detected
7
EE_DET
External EEPROM 
detect status
1
External EEPROM 
detected
0
0
External EEPROM 
not detected
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
71
Product Folder Links: TPS25990



---

## Page 72

Table 8-18. STATUS_MFR_SPECIFIC_2 Register Description (continued)
Bit
Name
Value
Description
Default
Access
6
EE_PROG
External EEPROM 
programmed status
Read
1
External EEPROM 
programmed
0
0
External EEPROM 
not programmed
5
AVG_DONE
Average computation 
complete status
1
Average computation 
done
0
0
Average computation 
ongoing
4
VIN_CABLE_FLT
Input cable fault 
indication
1
Cable fault detected
0
0
Cable fault not 
detected
3
RETRY_REC
Fault recovery/retry 
status
1
Device has recovered 
from fault through 
auto-retry
0
0
Normal power up 
i.e. Device has not 
recovered from fault 
through auto-retry
Read
2
POWER_CYCLE_RE
C
Power Cycle 
command status
1
Device has recovered 
from power cycle
0
0
Normal power up 
i.e. Device has not 
recovered from power 
cycle
1
INIT_DONE
Register Initialization 
status
1
Register Initialization 
Complete, All default/
Config values loaded 
into RAM
0
Read
0
Register Initialization 
not complete
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
72
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 73

Table 8-18. STATUS_MFR_SPECIFIC_2 Register Description (continued)
Bit
Name
Value
Description
Default
Access
0
CONFIG_NVM_STAT
Configuration NVM
Read
1
Not available to be 
programmed
0
Read
0
Available to be 
programmed
8.3.14.7.1.20 PMBUS_REVISION (98h, Read Byte)
PMBUS_REVISION is a standard PMBus® command which returns the revision of the PMBus® standard to 
which the device conforms.
The command has one data byte. Bits[7:4] indicate the revision of PMBus® specification Part I to which 
the device is compliant. Bits[3:0] indicate the revision of PMBus® specification Part II to which the device is 
compliant. To access this command, use the PMBus® read byte protocol.
This command returns 0x33h from the TPS25990x eFuse. This implies the device is compliant with Part I rev 1.3 
and Part II rev 1.3.
8.3.14.7.1.21 MFR_ID (99h, Block Read)
MFR_ID is a standard PMBus® command that returns the manufacturer name.
This command uses the PMBus® block read protocol with a block size of two (2). This register contains 
0x5449h, which represents "TI" in ASCII.
8.3.14.7.1.22 MFR_MODEL (9Ah, Block Read)
MFR_MODEL is a standard PMBus® command that returns the device part number.
This command uses the PMBus® block read protocol with a block size of eight (8). This register contains 
0x5450533235393930h, which represents "TPS25990" in ASCII.
8.3.14.7.1.23 MFR_REVISION (9Bh, Block Read)
MFR_REVISION is a standard PMBus® command that returns the device revision.
This command uses the PMBus® block read protocol with a block size of one (1). This register contains 0x01h.
8.3.14.7.1.24 READ_VIN (88h, Read Word)
READ_VIN is a standard PMBus® command that returns the 10-bit measured input voltage value.
This command uses the PMBus® read word protocol.
Follow the PMBus® DIRECT format conversion using the coefficients in Table 8-67 and Equation 19, to convert 
the hexadecimal data read from this register into a real-world value in V.
Table 8-19. READ_VIN Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Access
15:0
READ_VIN
Value measured for 
input voltage
0x0000 (0 V)
0x03FF (19.48 V)
Read
8.3.14.7.1.25 READ_VOUT (8Bh, Read Word)
READ_VOUT is a standard PMBus® command that returns the 10-bit measured output voltage value.
This command uses the PMBus® read word protocol.
Follow the PMBus® DIRECT format conversion using the coefficients in Table 8-67 and Equation 19, to convert 
the hexadecimal data read from this register into a real-world value in V.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
73
Product Folder Links: TPS25990



---

## Page 74

Table 8-20. READ_VOUT Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Access
15:0
READ_VOUT
Value measured for 
output voltage
0x0000 (0 V)
0x03FF (19.48 V)
Read
8.3.14.7.1.26 READ_IIN (89h, Read Word)
READ_IIN is a standard PMBus® command that returns the 10-bit measured input current value.
This command uses the PMBus® read word protocol.
Follow the PMBus® DIRECT format conversion using the coefficients in Table 8-67 and Equation 19, to convert 
the hexadecimal data read from this register into a real-world value in A.
Table 8-21. READ_IIN Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Access
15:0
READ_IIN
Value measured for input 
current
0x0000 (0 A)
0x03FF (107250/RIMON A)
Read
8.3.14.7.1.27 READ_TEMPERATURE_1 (8Dh, Read Word)
READ_TEMPERATURE_1 is a standard PMBus® command that returns the 10-bit measured device 
temperature value.
This command uses the PMBus® read word protocol.
Follow the PMBus® DIRECT format conversion using the coefficients in Table 8-67 and Equation 19, to convert 
the hexadecimal data read from this register into a real-world value °C.
Table 8-22. READ_TEMPERATURE_1 Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Access
15:0
READ_TEMPERATU
RE_1
Value measured for 
device temperature
0x0000 (-229 °C)
0x03FF (501 °C)
Read
8.3.14.7.1.28 READ_VAUX (D0h, Read Word)
READ_VAUX is a manufacturer specific command that reports the 10-bit measured voltage on the AUX pin.
This command uses the PMBus® read word protocol.
Follow the PMBus® DIRECT format conversion using the coefficients in Table 8-67 and Equation 19, to convert 
the hexadecimal data read from this register into a real-world value in V.
Table 8-23. READ_VAUX Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Access
15:0
READ_VAUX
Value measured 
for auxiliary voltage 
source connected at 
the AUX pin
0x0000 (0 V)
0x03FF (1.95 V)
Read
Note
Voltages greater than or equal to 1.95 V to ground are reported as full scale (0x03FFh). Voltages less 
than or equal to 0 V referenced to ground are reported as 0 V (0x0000h).
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
74
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 75

8.3.14.7.1.29 READ_PIN (97h, Read Word)
READ_PIN is a PMBus® standard command which returns the input power (input voltage multiplied by input 
current).
This command uses the PMBus® read word protocol.
Follow the PMBus® DIRECT format conversion using the coefficients in Table 8-67 and Equation 19, to convert 
the hexadecimal data read from this register into a real-world value in W.
Table 8-24. READ_PIN Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Access
15:0
READ_PIN
Value measured for 
input power
0x0000 (0 W)
0x03FF (2089230/RIMON W)
Read
8.3.14.7.1.30 READ_EIN (86h, Block Read)
The READ_EIN command is a standard PMBus® command which returns information to the host for computing 
the accumulated energy and average power consumption by a system powered by the eFuse. The information 
provided by this command is independent of any device specific averaging period, sampling frequency, or 
calculation algorithm.
This command uses the PMBus® block read protocol with a block size of six (6).
This command returns six (6) bytes of data. The first two (2) bytes are the two's complement and signed output 
of an accumulator that continuously sums samples of the instantaneous input power (the product of the samples 
of the input voltage and input current). These two data bytes are encoded in the DIRECT format as described 
in Section 8.3.14.10. The accumulator values are scaled so that the units are in “watt-samples”. This value in 
“watt-samples” must be multiplied by the effective ADC sampling period to obtain the real world value of energy 
accumulation in joules. If Bit[3] of the DEVICE_CONFIG register is set to high, the effective ADC sampling 
period is 18 µs (typical). Otherwise, it will be 11 µs (typical) by default.
The third data byte, ROLLOVER_COUNT is a count of rollover events for the accumulator. This byte is an 
unsigned integer indicating the number of times the accumulator has rolled over from its maximum positive value 
of 7FFFh to zero. The ROLLOVER_COUNT will periodically roll over from its maximum positive value to zero. It 
is up to the host to keep track of the state of the ROLLOVER_COUNT and account for the rollovers.
The other three (3) data bytes are a 24-bit unsigned integer that counts the number of samples of the 
instantaneous input power accumulated till now. This value will also roll over periodically from its maximum 
positive value to zero.
The combination of the accumulator and the rollover count may overflow within a few seconds. It is left to the 
host software to detect this overflow and handle it appropriately. Similarly, the sample count value will overflow. 
However, this event only occurs every five (5) minutes if Bit[3] of the DEVICE_CONFIG register is set to high, 
otherwise every three (3) minutes.
Table 8-25. READ_EIN Register Description
BYTE
Description
DEFAULT
Access
0
Power Accumulator Low Byte
0x00
Read
1
Power Accumulator High Byte
0x00
2
Power Accumulator Rollover Count
0x00
3
Sample Count Low byte
0x00
4
Sample Count Mid byte
0x00
5
Sample Count High byte
0x00
The host uses the accumulator value and rollover count to calculate the current “energy count” in “watt-samples” 
using Equation 15.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
75
Product Folder Links: TPS25990



---

## Page 76

Energy_Count = Rollover_Count × Accumulator_Roll_Over_Value + Accumulator_Value 
(15)
Where the Accumulator_Roll_Over_Value is the maximum possible positive value of the accumulator plus one 
(1). It is necessary to add one (1) to the maximum accumulator value to make the average power calculation 
correctly. The Accumulator_Roll_Over_Value is calculated using Equation 16.
Accumulator_Roll_Over_Value = 1
m
YMAX + 1 × 10−R −b = 1
m
215 × 10−R −b
(16)
Table 8-67 includes the "m, b, R" coefficients used in Equation 16. Accumulator_Value is obtained using the 
coefficients in Table 8-67 and Equation 19. The real world value of energy accumulation in joules is calculated 
using Equation 17.
Accumulated_Energy = Energy_Count × Effective_ADC_Sampling_Period
(17)
If Bit[3] of the DEVICE_CONFIG register is set to high, the Effective_ADC_Sampling_Period is 18 µs (typical). 
Otherwise, it will be 11 µs (typical) by default. The host calculates the average power in watt since the last 
reading using Equation 18.
Average_Power = Current_Energy_Count −Last_Energy_Count
Current_Sample_Count −Last_Sample_Count
(18)
Note
The ADC HI PERF bit in the DEVICE_CONFIG register) defines the ADC internal operating modes. 
The effective ADC sampling period is 11 µs in normal mode and 18 µs in high performance mode. The 
device is configured for normal mode by default. If it is necessary to change the ADC internal modes, 
it must be done before the downstream loads are enabled. It should not be changed under normal 
operation. This results in the wrong real world value for energy accumulation.
8.3.14.7.1.31 READ_VIN_AVG (DCh, Read Word)
READ_VIN_AVG is a manufacturer-specific command that reports 10-bit average value of input voltage.
This command uses the PMBus® read word protocol.
Follow the PMBus® DIRECT format conversion using the coefficients in Table 8-67 and Equation 19, to convert 
the hexadecimal data read from this register into a real-world value in V.
Table 8-26. READ_VIN_AVG Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Access
15:0
READ_VIN_AVG
Value measured for 
average input voltage
0x0000 (0 V)
0x03FF (19.48 V)
Read
The sample count for averaging can be programmed through PMBus® using Bit[2:0] in the PK_MIN_AVG 
register. The contents of READ_VIN_AVG register can be reset to zero (0x0000h) by setting Bit[6] in the 
PK_MIN_AVG register.
8.3.14.7.1.32 READ_VIN_MIN (D1h, Read Word)
READ_VIN_MIN is a manufacturer-specific command that reports 10-bit minimum input voltage measured since 
a power-on reset or the last RESET_MIN (Bit[5] in the PK_MIN_AVG register) made high.
This command uses the PMBus® read word protocol.
Follow the PMBus® DIRECT format conversion using the coefficients in Table 8-67 and Equation 19, to convert 
the hexadecimal data read from this register into a real-world value in V.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
76
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 77

Table 8-27. READ_VIN_MIN Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Access
15:0
READ_VIN_MIN
Value measured 
for minimum input 
voltage since reset or 
last clear
0x0000 (0 V)
0x03FF (19.48 V)
Read
8.3.14.7.1.33 READ_VIN_PEAK (D2h, Read Word)
READ_VIN_PEAK is a manufacturer-specific command that reports 10-bit maximum input voltage measured 
since a power-on reset or the last RESET_PEAK (Bit[7] in the PK_MIN_AVG register) command issued.
This command uses the PMBus® read word protocol.
Follow the PMBus® DIRECT format conversion using the coefficients in Table 8-67 and Equation 19, to convert 
the hexadecimal data read from this register into a real-world value in V.
Table 8-28. READ_VIN_PEAK Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Access
15:0
READ_VIN_PEAK
Value measured 
for maximum input 
voltage since reset or 
last clear
0x0000 (0 V)
0x03FF (19.48 V)
Read
8.3.14.7.1.34 READ_VOUT_AVG (DDh, Read Word)
READ_VOUT_AVG is a manufacturer-specific command that reports 10-bit average values of output voltage 
telemetry. Data are updated with each data cycle, reducing averaged telemetry read latency. Average 
count can be programmed through PMBus® using Bit[2:0] in the PK_MIN_AVG register. The contents of 
READ_VOUT_AVG register can be reset to zero (0x0000h) by setting Bit[6] in the PK_MIN_AVG register high.
This command uses the PMBus® read word protocol.
Follow the PMBus® DIRECT format conversion using the coefficients in Table 8-67 and Equation 19, to convert 
the hexadecimal data read from this register into a real-world value in V.
Table 8-29. READ_VOUT_AVG Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Access
15:0
READ_VOUT_AVG
Value measured 
for average output 
voltage
0x0000 (0 V)
0x03FF (19.48 V)
Read
8.3.14.7.1.35 READ_VOUT_MIN (DAh, Read Word)
READ_VOUT_MIN is a manufacturer-specific command that reports 10-bit minimum output voltage measured 
since a power-on reset or the last RESET_MIN (Bit[5] in the PK_MIN_AVG register) made high.
This command uses the PMBus® read word protocol.
Follow the PMBus® DIRECT format conversion using the coefficients in Table 8-67 and Equation 19, to convert 
the hexadecimal data read from this register into a real-world value in V.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
77
Product Folder Links: TPS25990



---

## Page 78

Table 8-30. READ_VOUT_MIN Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Access
15:0
READ_VOUT_MIN
Value measured 
for minimum output 
voltage since reset or 
last clear
0x0000 (0 V)
0x03FF (19.48 V)
Read
8.3.14.7.1.36 READ_IIN_AVG (DEh, Read Word)
READ_IIN_AVG is a manufacturer-specific command that reports 10-bit average values of input current 
telemetry. Data are updated with each data cycle, reducing averaged telemetry read latency. Average count can 
be programmed through PMBus® using Bit[2:0] in the PK_MIN_AVG register. The contents of READ_IIN_AVG 
register can be reset to zero (0x0000h) by setting Bit[6] in the PK_MIN_AVG register to high.
This command uses the PMBus® read word protocol.
Follow the PMBus® DIRECT format conversion using the coefficients in Table 8-67 and Equation 19, to convert 
the hexadecimal data read from this register into a real-world value in A.
Table 8-31. READ_IIN_AVG Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Access
15:0
READ_IIN_AVG
Value measured for 
average input current
0x0000 (0 A)
0x03FF (107250/RIMON A)
Read
8.3.14.7.1.37 READ_IIN_PEAK (D4h, Read Word)
READ_IIN_PEAK is a manufacturer-specific command that reports 10-bit maximum input current measured 
since a power-on reset or the last RESET_PEAK (Bit[7] in the PK_MIN_AVG register) made high.
This command uses the PMBus® read word protocol.
Follow the PMBus® DIRECT format conversion using the coefficients in Table 8-67 and Equation 19, to convert 
the hexadecimal data read from this register into a real-world value in A.
Table 8-32. READ_IIN_PEAK Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Access
15:0
READ_IIN_PEAK
Value measured for 
maximum input current 
since reset or last clear
0x0000 (0 A)
0x03FF (107250/RIMON A)
Read
8.3.14.7.1.38 READ_TEMP_AVG (D6h, Read Word)
The READ_TEMP_AVG command is a manufacturer-specific command that reports 10-bit average values of 
device temperature or auxiliary input voltage telemetry based on the state of Bit[7] in the ADC_CONFIG_2 
register. If this bit is set high, the READ_TEMP_AVG command reports average values of auxiliary input 
voltage telemetry, otherwise average values of device temperature telemetry. Default state of Bit[7] in the 
ADC_CONFIG_2 register is low. Data are updated with each data cycle, reducing averaged telemetry read 
latency. Average count can be programmed through PMBus® using Bit[2:0] in the PK_MIN_AVG register. The 
contents of READ_TEMP_AVG register can be reset to zero (0x0000h) by setting Bit[6] in the PK_MIN_AVG 
register high.
This command uses the PMBus® read word protocol.
Follow the PMBus® DIRECT format conversion using the coefficients in Table 8-67 and Equation 19, to convert 
the hexadecimal data read from this register into a real-world value in °C or V.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
78
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 79

Table 8-33. READ_TEMP_AVG Register Description
Bit
Bit[7] in the 
ADC_CONFIG_2 
register
Name
Description
Minimum Value
Maximum Value
Access
15:0
1
READ_VAUX_AVG
Value measured 
for average 
auxiliary input 
voltage
0x0000 (0 V)
0x03FF (1.95 V)
Read
0
READ_TEMP_AVG
Value measured 
for average 
device 
temperature
0x0000 (-229 °C)
0x03FF (501 °C)
Make sure to use the DIRECT format calculation coefficients correctly based on the state of Bit[7] in 
the ADC_CONFIG_2 register.
8.3.14.7.1.39 READ_TEMP_PEAK (D7h, Read Word)
READ_TEMP_PEAK is a manufacturer-specific command that reports 10-bit maximum device temperature 
measured since a power-on reset or the last RESET_PEAK (Bit[7] in the PK_MIN_AVG register) made high.
This command uses the PMBus® read word protocol.
Follow the PMBus® DIRECT format conversion using the coefficients in Table 8-67 and Equation 19, to convert 
the hexadecimal data read from this register into a real-world value in °C.
Table 8-34. READ_TEMP_PEAK Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Access
15:0
READ_TEMP_PEAK
Value measured for 
maximum device 
temperature since 
reset or last clear
0x0000 (-229 °C)
0x03FF (501 °C)
Read
8.3.14.7.1.40 READ_PIN_AVG (DFh, Read Word)
READ_PIN_AVG is a manufacturer-specific command that reports 10-bit average values of input power 
telemetry. Data are updated with each data cycle, reducing averaged telemetry read latency. Average count 
can be programmed through PMBus® using Bit[2:0] in the PK_MIN_AVG register. The contents of this register 
can be reset to zero (0x0000h) by setting Bit[6] in the PK_MIN_AVG register high.
This command uses the PMBus® read word protocol.
Follow the PMBus® DIRECT format conversion using the coefficients in Table 8-67 and Equation 19, to convert 
the hexadecimal data read from this register into a real-world value in W.
Table 8-35. READ_PIN_AVG Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Access
15:0
READ_PIN_AVG
Value measured for 
average input power
0x0000 (0 W)
0x03FF (2089230/RIMON W)
Read
8.3.14.7.1.41 READ_PIN_PEAK (D5h, Read Word)
READ_PIN_PEAK is a manufacturer-specific command that reports 10-bit maximum input power measured 
since a power-on reset or the last RESET_PEAK (Bit[7] in the PK_MIN_AVG register) made high.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
79
Product Folder Links: TPS25990



---

## Page 80

This command uses the PMBus® read word protocol.
Follow the PMBus® DIRECT format conversion using the coefficients in Table 8-67 and Equation 19, to convert 
the hexadecimal data read from this register into a real-world value in W.
Table 8-36. READ_PIN_PEAK Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Access
15:0
READ_PIN_PEAK
Value measured for 
maximum input power 
since reset or last clear
0x0000 (0 W)
0x03FF (2089230/RIMON W)
Read
8.3.14.7.1.42 READ_SAMPLE_BUF (D8h, Block Read)
READ_SAMPLE_BUF is a manufacturer-specific command used to read the latest sixty-four (64) samples of 
a particular parameter from a round-robin ADC buffer available in the device RAM. This allows multiple ADC 
samples to be captured at a higher speed and read out at on go without the bottleneck of reading individual 
samples sequentially over the PMBus® serial interface. This allows the system designer to reconstruct the time 
domain profile/waveform of that parameter in a given time interval. This could be useful during design or system 
debugging by functioning like an in-built "digital oscilloscope". The rate at which ADC samples are updated in 
the buffer depends on the effective ADC sampling period and the decimation rate/sample skip count. If Bit[3] of 
the DEVICE_CONFIG register is set to high, the effective ADC sampling period is 18 µs (typical). Otherwise, it 
will be 11 µs (typical) by default. The ADC channel to sample for buffering and the decimation rate/sample skip 
count can be configured through the ADC_CONFIG_2 register. By selecting different decimation rates, users can 
choose between “fine time resolution with short aperture” and “coarse time resolution with wide aperture”.
This command uses the PMBus® block read protocol with a block size of sixty-four (64).
Follow the PMBus® DIRECT format conversion using the coefficients in Table 8-67 and Equation 19, to convert 
the hexadecimal data bytes into their real-world values in the appropriate unit.
The ADC sample buffer starts buffering as soon as the device powers up. The buffering is paused under two 
different conditions:
1.
The instant READ_SAMPLE_BUF command is issued. This ensures the sample buffer is not overwritten 
with new values while the host is reading out the previous set of values. After sixty-four (64) bytes have been 
read, it will again start buffering new samples.
2.
In the event of a fault, which is latched internally as shown in Table 8-2. This ensures the snapshot of the 
samples prior to the fault event is preserved even if there's a delay from host in reading out the sample 
buffer. After issuing the CLEAR_FAULTS command, or writing OPERATION OFF command followed by 
OPERATION ON command, or toggling the EN/UVLO pin, it will again start buffering new samples.
Figure 8-20. ADC Sample Buffering Example
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
80
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 81

0
1
2
63
0
1
2
. . . .
Skip count = 0
. . . .
63
8-bits
ADC sample buer
0
1
2
3
4
5
6
0
1
2
. . . .
. . . .
Skip count = 2
Skip count = 2
188
189
. . . .
63
187
ADC
10-bits
fS
8-bits
Skip count = 2
ADC raw output
ADC sample bu er
191
192
190
Skip count = 2
. . . .
64
ADC
10-bits
fS
ADC raw output
PMBus Block Read
PMBus Block Read
Note
The ADC samples are truncated from 10-bits to 8-bits while filling up the ADC sample buffer. Make 
sure to use the DIRECT format calculation coefficients correctly.
8.3.14.7.1.43 READ_BB_RAM (FDh, Block Read)
READ_BB_RAM is a manufacturer-specific command used to read the contents of the Blackbox buffer RAM, 
which is seven (7) bytes deep as described in Section 8.3.14.11.
This command uses the PMBus® block read protocol with a block size of seven (7).
Table 8-37 presents details of the Blackbox RAM registers. There are seven (7) Blackbox RAM registers, starting 
from BB_RAM_0 to BB_RAM_6. Descriptions of all seven (7) registers (BB_RAM_0 to BB_RAM_6) are identical.
Table 8-37. BB_RAM Register Description
Bit
Name
Value
Description
Default
Access
7:5
EVENT_ID
Event identifier
Read
111
VIN_UV_WARN
000
110
VIN_OV_WARN
101
OC_WARN
100
OT_WARN
011
OC_DET
010
VIN_TRAN
001
IN_OP_WARN
000
None
4
BB_TMR_EXP
Blackbox timer expiry
1
Blackbox timer 
overflowed at least 
once since the last 
event
0
0
Blackbox timer has 
not overflowed
3:0
BB_TICK
0000
Blackbox tick timer
0000
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
81
Product Folder Links: TPS25990



---

## Page 82

The Blackbox RAM contents get reset under the following events:
•
Input power recycle at VIN or VDD pin
•
ENABLE recycling
•
CLEAR_FAULTS command
•
OPERATION OFF command followed by OPERATION ON command
•
Initiation of an auto-retry sequence
8.3.14.7.1.44 READ_BB_EEPROM (F4h, Block Read)
READ_BB_EEPROM is a manufacturer-specific command used to read contents stored in the Blackbox shadow 
registers internal to the TPS25990 eFuse. Before issuing this command, the FETCH_BB_EEPROM command 
needs to be sent to load the Blackbox contents from the external EEPROM (Page-0) as described in Section 
8.3.14.11 into the Blackbox shadow registers. READ_BB_EEPROM retrieves sixteen (16) bytes of Blackbox 
information stored in the EEPROM as shown below.
•
BB_RAM_0 to BB_RAM_6 [Seven (7) bytes]
•
BB_TIMER [One (1) byte]
•
STATUS_WORD [Two (2) bytes]
•
STATUS_MFR_SPECIFIC [One (1) byte]
•
STATUS_INPUT [One (1) byte]
•
VIN_PEAK [One (1) byte, Eight (8) MSBs from the 10-bit ADC output data]
•
IIN_PEAK [One (1) byte, Eight (8) MSBs from the 10-bit ADC output data]
•
TEMPERATURE_PEAK [One (1) byte, Eight (8) MSBs from the 10-bit ADC output data]
•
CHECKSUM [One (1) byte]
This command uses the PMBus® block read protocol with a block size of sixteen (16).
VIN_PEAK, IIN_PEAK, and TEMPERATURE_PEAK data use the PMBus® DIRECT format. Use the coefficients 
in Table 8-67 and Equation 19 to convert the hexadecimal data read from these registers into their real-world 
value in the appropriate units.
Note
The peak input voltage, input current, and temperature values are truncated from 10-bits to 8-bits 
while stored in an external EEPROM. Make sure to use the DIRECT format calculation coefficients 
correctly.
8.3.14.7.1.45 BB_TIMER (FAh, Read Byte)
BB_TIMER is a manufacturer-specific command used to read the following:
•
Blackbox RAM address pointer, indicating which Blackbox RAM has been filled to date. After filling up all 
seven (7) Blackbox RAM locations, it resets to zero.
•
Blackbox timer expiry bit, showing if the Blackbox tick timer has overflowed at least once since the last event. 
This bit indicates if the Blackbox RAM event entries are relatively recent or old. This bit is latched when the 
timer overflows and resets to zero along with the free running timer when the next event occurs.
•
Blackbox tick timer, a free running timer, which is reset to zero after every event. The timer update rate can 
be configured through the BB_CONFIG register. This allows users to tradeoff between fine resolution and 
longer time span depending on their debugging needs.
To access the BB_TIMER register, use the PMBus® read byte protocol. The whole content of this register resets 
to zero (0) at the instant the CLEAR_FAULTS command is issued. The details of the BB_TIMER register are 
shown in Table 8-38.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
82
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 83

Table 8-38. BB_TIMER Register Description
Bit
Name
Value
Description
Default
Access
7:5
BB_PTR
BB RAM address 
pointer
Read
000
Either all seven 
(7) Blackbox RAM 
registers are empty 
or all are filled up till 
date
000
001
BB_RAM_0 filled up 
till date
010
BB_RAM_0 and 
BB_RAM_1 filled up 
till date
011
BB_RAM_0, 
BB_RAM_1, and 
BB_RAM_2 filled up 
till date
100
BB_RAM_0, 
BB_RAM_1, 
BB_RAM_2, and 
BB_RAM_3 filled up 
till date
101
BB_RAM_0, 
BB_RAM_1, 
BB_RAM_2, 
BB_RAM_3, and 
BB_RAM_4 filled up 
till date
110
BB_RAM_0, 
BB_RAM_1, 
BB_RAM_2, 
BB_RAM_3, 
BB_RAM_4, and 
BB_RAM_5 filled up 
till date
111
Reserved
4
BB_TMR_EXP
Blackbox timer expiry
1
Blackbox timer 
overflowed at least 
once since the last 
event
0
0
Blackbox timer has 
not overflowed
3:0
BB_TICK
Blackbox timer
0000
8.3.14.7.1.46 PMBUS_ADDR (FBh, Read/Write Byte)
PMBUS_ADDR is a manufacturer-specific command used for reading and configuring a user-specific device 
address apart from the addresses mentioned in Table 8-5. The device uses this address for I2C communication 
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
83
Product Folder Links: TPS25990



---

## Page 84

instead of the default value (0x40) when ADDR0 and ADDR1 pins are OPEN. This updated device address can 
be stored in the NVM and the device responds to this revised address upon power up next time.
This command uses the PMBus® read or write byte protocol.
8.3.14.7.1.47 VIN_UV_WARN (58h, Read/Write Word)
VIN_UV_WARN is a standard PMBus® command for configuring or reading an 8-bit threshold for the input 
undervoltage warning detection. This command uses the PMBus® DIRECT format. When reading and writing 
to this register, use the coefficients shown in Table 8-67, Equation 19, and Equation 20 to convert between real 
word units and hexadecimal values. This command uses the PMBus® read or write word protocol.
Contents of this register are compared to the VIN ADC telemetry value. If the measured VIN value falls 
below the value in this register, the VIN_UV_WARN flags are set in the respective registers. The SMBA# 
signal is asserted. When the input voltage rises above the VIN_UV_WARN threshold, and the CLEAR_FAULTS 
command is sent afterwards, this warning flag and alert are cleared.
Table 8-39. VIN_UV_WARN Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Default Value
Access
15:0
VIN_UV_WARN
Input undervoltage 
warning threshold
0x0000 (0 V)
0x00FF (19.42 V)
0x0095h (11.35 V)
Read/Write
When an input undervoltage warning is detected, the device:
•
sets the NONE_OF_THE_ABOVE/UNKNOWN bit in the STATUS_BYTE register
•
sets the INPUT_STATUS bit in the upper byte of the STATUS_WORD register
•
sets the VIN_UV_WARN bit in the STATUS_INPUT register
•
fills-up one of the Blackbox RAM registers (if available to write) writing the event identifier as VIN_UV_WARN 
and relative time stamp information
•
increases the Blackbox RAM address pointer in the BB_TIMER register by one (1) if it was previously less 
than six (6), otherwise resets to zero (0). This change in the address pointer only occurs if one of the 
Blackbox RAM registers is available to write.
•
notifies the host by asserting SMBA#, if it is not masked setting the STATUS_IN bit in the ALERT_MASK 
register and the GPIO4 pin is configured as SMBA# Output in the GPIO_CONFIG_34 register
Note
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
8.3.14.7.1.48 VIN_UV_FLT (59h, Read/Write Word)
VIN_UV_FLT is a standard PMBus® command for configuring or reading an 8-bit threshold for the input 
undervoltage fault detection. This command uses the PMBus® DIRECT format. When reading and writing to 
this register, use the coefficients shown in Table 8-67, Equation 19, and Equation 20 to convert between the real 
world units and hexadecimal values.
This command uses the PMBus® read or write word protocol.
Contents of this register are compared to the VIN ADC telemetry value. Once the input voltage has fallen below 
the undervoltage fault threshold, the output is turned off, and the VIN_UV_FLT flags are set in the respective 
registers. The SMBA# signal is asserted. 250 mV (typical) of hysteresis is added to the value in this register. This 
is to provide the rising threshold the input voltage must rise above for this fault to clear. Once the input voltage 
rises above the rising threshold, the output is turned back on. However, the fault flags and alerts remain until 
cleared by the host by sending the CLEAR_FAULTS command.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
84
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 85

Table 8-40. VIN_UV_FLT Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Default Value
Access
15:0
VIN_UV_FLT
Input undervoltage 
fault threshold
0x0000 (0 V)
0x00FF (19.42 V)
0x008Dh (10.74 V)
Read/Write
When an input undervoltage fault is detected, the device:
•
sets the FET_OFF, VIN_UV_FLT, and NONE_OF_THE_ABOVE/UNKNOWN bits in the STATUS_BYTE 
register
•
sets the OUT_STATUS, INPUT_STATUS, PGOODB, and NONE_OF_THE_ABOVE/UNKNOWN bits in the 
upper byte of the STATUS_WORD register
•
sets the VOUT_UV_WARN bit in the STATUS_OUT register
•
sets the VIN_UV_FLT bit in the STATUS_INPUT register
•
sets the PGOODB bit in the STATUS_MFR_SPECIFIC_2 register
•
notifies the host by asserting SMBA#, if it is not masked setting the STATUS_IN, PGOODB, and 
STATUS_OUT bits in the ALERT_MASK register and the GPIO4 pin is configured as SMBA# Output in 
the GPIO_CONFIG_34 register
•
deasserts the external PGOOD signal, if the GPIO1 pin is configured as PGOOD output in the 
GPIO_CONFIG_12 register
Note
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
8.3.14.7.1.49 VIN_OV_WARN (57h, Read/Write Word)
VIN_OV_WARN is a standard PMBus® command for configuring or reading an 8-bit threshold for the input 
overvoltage warning detection. This command uses the PMBus® DIRECT format. When reading and writing to 
this register, use the coefficients shown in Table 8-67, Equation 19, and Equation 20 to convert between the real 
world units and hexadecimal values.
This command uses the PMBus® read or write word protocol.
Contents of this register are compared to the VIN ADC telemetry value. If the measured VIN value rises above 
the value in this register, the VIN_OV_WARN flags are set in the respective registers. The SMBA# signal is 
asserted. When the input voltage falls below the VIN_OV_WARN threshold, and the CLEAR_FAULTS command 
is sent afterwards, this warning flag and alert are cleared.
Table 8-41. VIN_OV_WARN Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Default Value
Access
15:0
VIN_OV_WARN
Input overvoltage 
warning threshold
0x0000 (0 V)
0x00FF (19.42 V)
0x00A5h (12.57 V)
Read/Write
When an input overvoltage warning is detected, the device:
•
sets the NONE_OF_THE_ABOVE/UNKNOWN bit in the STATUS_BYTE register
•
sets the INPUT_STATUS bit in the upper byte of the STATUS_WORD register
•
sets the VIN_OV_WARN bit in the STATUS_INPUT register
•
fills-up one of the Blackbox RAM registers (if available to write) writing the event identifier as VIN_OV_WARN 
and relative time stamp information
•
increases the Blackbox RAM address pointer in the BB_TIMER register by one (1) if it was previously less 
than six (6), otherwise resets to zero (0). This change in the address pointer only occurs if one of the 
Blackbox RAM registers is available to write.
•
notifies the host by asserting SMBA#, if it is not masked setting the STATUS_IN bit in the ALERT_MASK 
register and the GPIO4 pin is configured as SMBA# Output in the GPIO_CONFIG_34 register
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
85
Product Folder Links: TPS25990



---

## Page 86

Note
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
8.3.14.7.1.50 VIN_OV_FLT (55h, Read/Write Word)
VIN_OV_FLT is a standard PMBus® command for configuring or reading a 4-bit threshold for the input 
overvoltage fault detection. This command uses the PMBus® DIRECT format. When reading and writing to 
this register, use the coefficients shown in Table 8-67, Equation 19, and Equation 20 to convert between the real 
world units and hexadecimal values.
This command uses the PMBus® read or write word protocol.
Contents of this register drive a DAC to set the thresholds for a comparator monitoring the input voltage. Once 
the input voltage exceeds the overvoltage fault rising threshold, the output is turned off, and the VIN_OV_FLT 
flags are set in the respective registers. The SMBA# signal is asserted. 250 mV (typical) of hysteresis is 
subtracted from the value in this register. This is to provide the falling threshold the input voltage must fall below 
for this fault to clear. Once the input voltage falls below the falling threshold, the output is turned back on. 
However, the fault flags and alerts remain until cleared by the host by sending the CLEAR_FAULTS command.
Table 8-42. VIN_OV_FLT Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Default Value
Access
15:0
VIN_OV_FLT
Input overvoltage 
fault threshold
0x0000h (2.96 V)
0x000Fh (17.72 V) 0x000Eh (16.74 V)
Read/Write
When an input overvoltage fault is detected, the device:
•
sets the FET_OFF and NONE_OF_THE_ABOVE/UNKNOWN bits in the STATUS_BYTE register
•
sets the OUT_STATUS, INPUT_STATUS, PGOODB and NONE_OF_THE_ABOVE/UNKNOWN bits in the 
upper byte of the STATUS_WORD register
•
sets the VOUT_UV_WARN bit in the STATUS_OUT register
•
sets the VIN_OV_FLT bit in the STATUS_INPUT register
•
sets the PGOODB bit in the STATUS_MFR_SPECIFIC_2 register
•
notifies the host by asserting SMBA#, if it is not masked setting the STATUS_IN, PGOODB, and 
STATUS_OUT bits in the ALERT_MASK register and the GPIO4 pin is configured as SMBA# Output in 
the GPIO_CONFIG_34 register
•
deasserts the external PG signal, if the GPIO1 pin is configured as PGOOD output in the GPIO_CONFIG_12 
register
Note
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
8.3.14.7.1.51 VOUT_UV_WARN (43h, Read/Write Word)
VOUT_UV_WARN is a standard PMBus® command for configuring or reading an 8-bit threshold for the output 
undervoltage warning detection. This command uses the PMBus® DIRECT format. When reading and writing to 
this register, use the coefficients shown in Table 8-67, Equation 19, and Equation 20 to convert between the real 
world units and hexadecimal values.
This command uses the PMBus® read or write word protocol.
Contents of this register are compared to the VOUT ADC telemetry value. If the measured VOUT value 
falls below the value in this register, the VOUT_UV_WARN flags are set in the respective registers. The 
SMBA# signal is asserted. When the output voltage rises above the VOUT_UV_WARN threshold, and the 
CLEAR_FAULTS command is sent afterwards, this warning flag and alert are cleared.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
86
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 87

Table 8-43. VOUT_UV_WARN Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Default Value
Access
15:0
VIN_UV_WARN
Input undervoltage 
warning threshold
0x0000h (0 V)
0x00FFh (19.42 V) 0x0095h (11.35 V)
Read/Write
When an output undervoltage warning is detected, the device:
•
sets the NONE_OF_THE_ABOVE/UNKNOWN bit in the STATUS_BYTE register
•
sets the OUT_STATUS bit in the upper byte of the STATUS_WORD register
•
sets the VOUT_OV_WARN bit in the STATUS_OUT register
•
notifies the host by asserting SMBA#, if it is not masked setting the STATUS_OUT bit in the ALERT_MASK 
register and the GPIO4 pin is configured as SMBA# Output in the GPIO_CONFIG_34 register.
Note
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
8.3.14.7.1.52 VOUT_PGTH (5Fh, Read/Write Word)
VOUT_PGTH is a standard PMBus® command for setting or reading an 8-bit output voltage threshold at which 
Power Good (PGOOD) is be de-asserted. This command uses the PMBus® DIRECT format. When reading 
and writing to this register, use the coefficients shown in Table 8-67, Equation 19, and Equation 20 to convert 
between the real world units and hexadecimal values.
This command uses the PMBus® read or write word protocol.
Contents of this register are compared to the VOUT ADC telemetry value. Once the output voltage has fallen 
below the VOUT_PGTH threshold at any point of time during normal operation or the device detects a fault 
(except short-circuit), the PGOOD is de-asserted, and the PGOODB flags are set in the respective registers. 
The SMBA# signal is also asserted. 250 mV (typical) of hysteresis is added to the value in this register. In order 
for the PGOOD to be asserted again, the output voltage must rise above this rising threshold after clearing all 
underlying faults and enabling the FET internal to the device. However, the fault flags and alerts remain until 
cleared by the host by sending the CLEAR_FAULTS command.
Table 8-44. VOUT_PGTH Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Default Value
Access
15:0
VOUT_PGTH
Output power 
good de-assertion 
threshold
0x0000h (0 V)
0x00FFh (19.42 V)
0x008Dh (10.74 V)
Read/Write
When the output voltage is less than VOUT_PGTH threshold, the device:
•
sets the NONE_OF_THE_ABOVE/UNKNOWN bit in the STATUS_BYTE register
•
sets the PGOODB and NONE_OF_THE_ABOVE/UNKNOWN bits in the upper byte of the STATUS_WORD 
register
•
sets the PGOODB bit in the STATUS_MFR_SPECIFIC_2 register
•
notifies the host by asserting SMBA#, if it is not masked setting the PGOODB bit in the ALERT_MASK 
register and the GPIO4 pin is configured as SMBA# Output in the GPIO_CONFIG_34 register
Note
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
87
Product Folder Links: TPS25990



---

## Page 88

8.3.14.7.1.53 OT_WARN (51h, Read/Write Word)
OT_WARN is a standard PMBus® command for configuring or reading an 8-bit threshold for the device 
overtemperature warning detection. This command uses the PMBus® DIRECT format. When reading and 
writing to this register, use the coefficients shown in Table 8-67, Equation 19, and Equation 20 to convert 
between the real world units and hexadecimal values.
This command uses the PMBus® read or write word protocol.
Contents of this register are compared to the VTEMP ADC telemetry value. If the device temperature rises 
above the value in this register, the OT_WARN flags are set in the respective registers. The SMBA# signal 
is asserted. When the device temperature falls below the OT_WARN threshold, and the CLEAR_FAULTS 
command is sent afterwards, this warning flag and alert are cleared.
Table 8-45. OT_WARN Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Default Value
Access
15:0
OT_WARN
Device 
overtemperature 
warning threshold
0x0000h (-229 ºC)
0x00FFh (500 ºC)
0x007Eh (131 ºC)
Read/Write
When an overtemperature warning is detected, the device:
•
sets the STATUS_TEMP bit in the STATUS_BYTE register
•
sets the OT_WARN bit in the STATUS_TEMP register
•
fills-up one of the Blackbox RAM registers (if available to write) writing the event identifier as OT_WARN and 
relative time stamp information
•
increases the Blackbox RAM address pointer in the BB_TIMER register by one (1) if it was previously less 
than six (6), otherwise resets to zero (0). This change in the address pointer only occurs if one of the 
Blackbox RAM registers is available to write
•
notifies the host by asserting SMBA#, if it is not masked setting the STATUS_TEMP bit in the ALERT_MASK 
register and the GPIO4 pin is configured as SMBA# Output in the GPIO_CONFIG_34 register
Note
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
8.3.14.7.1.54 OT_FLT (4Fh, Read/Write Word)
OT_FLT is a standard PMBus® command for configuring or reading an 8-bit threshold for the device 
overtemperature fault detection. This command uses the PMBus® DIRECT format. When reading and writing to 
this register, use the coefficients shown in Table 8-67, Equation 19, and Equation 20 to convert between the real 
world units and hexadecimal values.
This command uses the PMBus® read or write word protocol.
Contents of this register are compared to the VTEMP ADC telemetry value. Once the device temperature 
exceeds the overtemperature fault threshold, the output is turned off, and the OT_FLT flags are set in the 
respective registers. The SMBA# signal is asserted. Refer to Section 8.3.7 for more details on thermal shutdown. 
After the device recovers from an overtemperature fault, the CLEAR_FAULTS command clears the OT_FLT flag 
and alert.
Table 8-46. OT_FLT Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Default Value
Access
15:0
OT_WARN
Device 
overtemperature 
fault threshold
0x0000h (-229 ºC)
0x00FFh (500 ºC)
0x0085h (151 ºC)
Read/Write
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
88
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 89

When an overtemperature fault is detected, the device:
•
sets the FET_OFF, STATUS_TEMP, and NONE_OF_THE_ABOVE/UNKNOWN bits in the STATUS_BYTE 
register
•
sets the OUT_STATUS, PGOODB, and NONE_OF_THE_ABOVE/UNKNOWN bits in the upper byte of the 
STATUS_WORD register
•
sets the VOUT_UV_WARN bit in the STATUS_OUT register
•
sets the OT_FLT bit in the STATUS_TEMP register
•
sets the PGOODB bit in the STATUS_MFR_SPECIFIC_2 register
•
notifies the host asserting SMBA#, if it is not masked setting the STATUS_TEMP, PGOODB, and 
STATUS_OUT bits high in the ALERT_MASK register and the GPIO4 pin is configured as SMBA# Output in 
the GPIO_CONFIG_34 register
•
deasserts the external PGOOD signal, if the GPIO1 pin is configured as PGOOD Output in the 
GPIO_CONFIG_12 register
•
asserts the FLT signal, if it is not masked setting the TEMP_FLT bit high in the FAULT_MASK register and the 
GPIO2 pin is configured as FLT Output in the GPIO_CONFIG_12 register
Note
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
8.3.14.7.1.55 PIN_OP_WARN (6Bh, Read/Write Word)
PIN_OP_WARN is a standard PMBus® command for configuring or reading an 8-bit threshold for the input 
overpower warning detection. This command uses the PMBus® DIRECT format. When reading and writing to 
this register, use the coefficients shown in Table 8-67, Equation 19, and Equation 20 to convert between the real 
world units and hexadecimal values.
This command uses the PMBus® read or write word protocol.
Contents of this register are compared to the calculated telemetry power value. If the input power rises above 
the value in this register, the PIN_OP_WARN flags are set in the respective registers. The SMBA# signal is 
asserted. When the input power falls below the PIN_OP_WARN threshold, and the CLEAR_FAULTS command 
is sent afterwards, this warning flag and alert are cleared.
Table 8-47. PIN_OP_WARN Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Default Value
Access
15:0
PIN_OP_WARN
Input overpower 
warning threshold
0x0000h (0 W)
0x00FFh 
(2089230/RIMON 
W)
0x00FFh 
(2089230/RIMON 
W)
Read/Write
When an input overpower warning is detected, the device:
•
sets the NONE_OF_THE_ABOVE/UNKNOWN bit in the STATUS_BYTE register
•
sets the INPUT_STATUS and NONE_OF_THE_ABOVE/UNKNOWN bits in the upper byte of the 
STATUS_WORD register
•
sets the IN_OP_WARN bit in the STATUS_INPUT register
•
may set the EIN_OF_WARN bit in the STATUS_MFR_SPECIFIC_2 register
•
fills-up one of the Blackbox RAM registers (if available to write) writing the event identifier as IN_OP_WARN 
and relative time stamp information
•
increments the Blackbox RAM address pointer in the BB_TIMER register by one (1) if it was previously 
less than six (6), otherwise resets to zero (0). This change in the address pointer only occurs if one of the 
Blackbox RAM registers is available to write.
•
notifies the host by asserting SMBA#, if it is not masked setting the STATUS_IN bit in the ALERT_MASK 
register and the GPIO4 pin is configured as SMBA# Output in the GPIO_CONFIG_34 register
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
89
Product Folder Links: TPS25990



---

## Page 90

Note
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
8.3.14.7.1.56 IIN_OC_WARN (5Dh, Read/Write Word)
IIN_OC_WARN is a standard PMBus® command for configuring or reading an 8-bit threshold for the input 
overcurrent warning detection. This command uses the PMBus® DIRECT format. When reading and writing to 
this register, use the coefficients shown in Table 8-67, Equation 19, and Equation 20 to convert between the real 
world units and hexadecimal values.
This command uses the PMBus® read or write word protocol.
Contents of this register are compared to the VIMON ADC telemetry value. If the input current rises above the 
value in this register, the IIN_OC_WARN flags are set in the respective registers. The SMBA# signal is asserted. 
When the input current falls below the IIN_OC_WARN threshold, and the CLEAR_FAULTS command is sent 
afterwards, this warning flag and alert are cleared.
Table 8-48. IIN_OC_WARN Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Default Value
Access
15:0
IIN_OC_WARN
Input overcurrent 
warning threshold
0x0000h (0 A)
0x00FFh (107250/
RIMON A)
0x00FFh (107250/
RIMON A)
Read/Write
When an input overcurrent warning is detected, the device:
•
sets the NONE_OF_THE_ABOVE/UNKNOWN bit in the STATUS_BYTE register
•
sets the INPUT_STATUS bit in the upper byte of the STATUS_WORD register
•
sets the OC_WARN bit in the STATUS_INPUT register
•
may set the EIN_OF_WARN bit in the STATUS_MFR_SPECIFIC_2 register
•
fills-up one of the Blackbox RAM registers (if available to write) writing the event identifier as OC_WARN and 
relative time stamp information
•
increments the Blackbox RAM address pointer in the BB_TIMER register by one (1) if it was previously 
less than six (6), otherwise resets to zero (0). This change in the address pointer only occurs if one of the 
Blackbox RAM registers is available to write.
•
notifies the host by asserting SMBA#, if it is not masked setting the STATUS_IN bit high in the ALERT_MASK 
register and the GPIO4 pin is configured as SMBA# Output in the GPIO_CONFIG_34 register
Note
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
8.3.14.7.1.57 VIREF (E0h, Read/Write Byte)
VIREF is a manufacturer-specific command for configuring or reading a 6-bit reference threshold for overcurrent 
& short-circuit protections and active current sharing blocks as described in Section 8.3.4.2, Section 8.3.4.3, and 
Section 8.3.4.4. This command uses the PMBus® DIRECT format. When reading and writing to this register, use 
the coefficients shown in Table 8-67, Equation 19, and Equation 20 to convert between the real world units and 
hexadecimal values.
This command uses the PMBus® read or write byte protocol.
Contents of this register drive a DAC to set the threshold for different comparators monitoring the input current. 
The details of this register are shown in Table 8-49.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
90
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 91

Table 8-49. VIREF Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Default Value
Access
7:0
VIREF
Programmable 
reference voltage 
for overcurrent 
& short-circuit 
protections and 
active current 
sharing blocks
0x00h (0.3 V)
0x3Fh (1.186 V)
0x32h (1 V)
Read/Write
Note
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
8.3.14.7.1.58 GPIO_CONFIG_12 (E1h, Read/Write Byte)
GPIO_CONFIG_12 is a manufacturer-specific command for configuring or reading functionalities of GPIO1 
(Pin-19) and GPIO2 (Pin-20) as described in Section 8.3.10.
This command uses the PMBus® read byte protocol.
The details of this register are shown in Table 8-50.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
91
Product Folder Links: TPS25990



---

## Page 92

Table 8-50. GPIO_CONFIG_12 Register Description
Bit
Name
Value
Description
Default
Access
7:5
GPIO1 configuration
GPIO1 functionality
Read/Write
111
Reserved
000
110
EEDATA
101
EECLK
100
COMP1 output
011
COMP2 output
010
General purpose logic 
output
001
General purpose logic 
input
000
PGOOD Output
4
GPIO1 pin state when 
configured as general 
purpose input/output
1
Pin set to HI
0
0
Pin set to LO
3:1
GPIO2 configuration
GPIO2 functionality
111
Reserved
000
110
EEDATA
101
EECLK
100
COMP1 output
011
COMP2 output
010
General purpose logic 
output
001
General purpose logic 
input
000
FLT output
0
GPIO2 pin state when 
configured as general 
purpose input/output
1
Pin set to HI
0
0
Pin set to LO
Note
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
8.3.14.7.1.59 GPIO_CONFIG_34 (E2h, Read/Write Byte)
GPIO_CONFIG_34 is a manufacturer-specific command for configuring or reading functionalities of GPIO3 
(PIN-21) and GPIO4 (PIN-17) as described in Section 8.3.10.
This command uses the PMBus® read byte protocol.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
92
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 93

The details of this register are shown in Table 8-51.
Table 8-51. GPIO_CONFIG_34 Register Description
Bit
Name
Value
Description
Default
Access
7:5
GPIO3 configuration
GPIO3 functionality
Read/Write
111
Reserved
000
110
EEDATA
101
EECLK
100
COMP1 output
011
COMP2 output
010
General purpose logic 
output
001
General purpose logic 
input
000
SWEN
4
GPIO3 pin state when 
configured as general 
purpose input/output
1
Pin set to HI
0
0
Pin set to LO
3:1
GPIO4 configuration
GPIO4 functionality
111
Reserved
000
110
EEDATA
101
EECLK
100
COMP1 output
011
COMP2 output
010
General purpose logic 
output
001
General purpose logic 
input
000
SMBA# output
0
GPIO4 pin state when 
configured as general 
purpose input/output
1
Pin set to HI
0
0
Pin set to LO
Note
•
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
•
When using a TPS25990 eFuse with one or more TPS25985x eFuse(s) in parallel, GPIO3 must be 
in its default configuration i.e. SWEN.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
93
Product Folder Links: TPS25990



---

## Page 94

8.3.14.7.1.60 ALERT_MASK (DBh, Read/Write Word)
ALERT_MASK is a manufacturer-specific command for configuring or reading the events which are allowed to 
assert the SMBA# signal.
This command uses the PMBus® read or write word protocol.
Each bit corresponds to one of the analog or digital faults or warnings that would normally result in SMBA# 
being asserted. When the corresponding bit is high, that condition does not cause SMBA# to be asserted. If 
that condition occurs, the registers where that condition is captured are still updated (STATUS registers and 
Blackbox) and the device ON/OFF control is still active. The details of this register are shown in Table 8-52.
Table 8-52. ALERT_MASK Register Description
Bit
Name
Value
Description
Default
Access
15:9
Reserved
0000000
Reserved
0000000
Read/Write
8
UNKNOWN
1
UNKNOWN status bit doesn’t assert 
SMBA#
1
0
UNKNOWN status bit asserts
SMBA#
7
PGOODB
1
PGOOD falling doesn’t assert SMBA#
0
0
PGOOD falling asserts SMBA#
6
GLBL_FLT
1
GLBL_FLT doesn’t assert SMBA#
0
0
GLBL_FLT asserts SMBA#
5
MFR_STATUS
1
Active bits set in STATUS_MFR_SPECIFIC 
register don’t assert SMBA#
0
0
Active bits set in STATUS_MFR_SPECIFIC 
register assert SMBA#
4
STATUS_TEMP
1
Active bits set in STATUS_TEMP register 
don’t assert SMBA#
0
0
Active bits set in STATUS_TEMP register 
assert SMBA#
3
STATUS_OUT
1
Active bits set in STATUS_OUT register 
don’t assert SMBA#
0
0
Active bits set in STATUS_OUT register 
assert SMBA#
2
STATUS_IN
1
Active bits set in STATUS_INPUT register 
don’t assert SMBA#
0
0
Active bits set in STATUS_INPUT register 
assert
SMBA#
1
CML_ERR
1
Active bits set in STATUS_CML register 
don’t assert SMBA#
0
0
Active bits set in STATUS_CML register 
assert SMBA#
0
STATUS_IOUT
1
Active bits set in STATUS_IOUT register 
don’t assert SMBA#
0
0
Active bits set in STATUS_IOUT register 
assert SMBA#
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
94
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 95

Note
•
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
•
GLBL_FLT is a logical OR of the status bits unmasked using the FAULT_MASK register.
8.3.14.7.1.61 FAULT_MASK (E3h, Read/Write Word)
FAULT_MASK is a manufacturer-specific command for configuring or reading the events to govern the global 
fault (GLBL_FLT) bit in asserting SMBA# as described in the ALERT_MASK register and causing the external 
FLT signal to be asserted, if the GPIO2 pin is configured as FLT in the GPIO_CONFIG_12 register.
This command uses the PMBus® read or write word protocol.
The details of this register are shown in Table 8-53.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
95
Product Folder Links: TPS25990



---

## Page 96

Table 8-53. FAULT_MASK Register Description
Bit
Name
Value
Description
Default
Access
15:11
Reserved
00000
Reserved
00000
Read/Write
10
EXT_FLT
1
EXT_FLT doesn’t 
assert FLT
0
0
EXT _FLT asserts 
FLT
9
CMP1_FLT
1
CMP1_FLT doesn’t 
assert FLT
0
0
CMP1_FLT asserts 
FLT
8
CMP2_FLT
1
CMP2_FLT doesn’t 
assert FLT
0
0
CMP2_FLT asserts 
FLT
7
FET_HEALTH
1
FET_HEALTH doesn’t 
assert FLT
0
0
FET_HEALTH asserts 
FLT
6
SPFAIL
1
SPFAIL doesn’t 
assert FLT
0
0
SPFAIL asserts FLT
5
SOA_FLT
1
SOA_FLT doesn’t 
assert FLT
0
0
SOA_FLT asserts 
FLT
4:3
Reserved
00
Reserved
00
2
TEMP_FLT
1
TEMP_FLT doesn’t 
assert FLT
0
0
TEMP_FLT asserts 
FLT
1
OC_FLT
1
OC_FLT doesn’t 
assert FLT
0
0
OC_FLT asserts FLT
0
SC_FLT
1
SC_FLT doesn’t 
assert FLT
0
0
SC_FLT asserts FLT
Note
•
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
•
This command only allows the user to choose which events will cause assertion of the FLT pin. 
Masking any event in the FAULT_MASK register doesn’t prevent the respective event from turning 
OFF the device.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
96
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 97

8.3.14.7.1.62 DEVICE_CONFIG (E4h, Read/Write Word)
DEVICE_CONFIG is a manufacturer-specific command for configuring or reading several key device setup 
related information of TPS25990 eFuse.
This command uses the PMBus® read or write word protocol.
The details of this register are shown in Table 8-54.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
97
Product Folder Links: TPS25990



---

## Page 98

Table 8-54. DEVICE_CONFIG Register Description
Bit
Name
Value
Description
Default
Access
15
PG_DVDT_DLY
Internal PG delay 
for discharging DVDT 
capacitor
Read/Write
1
38 ms
0
0
110 µs
14
DIS_VDSFLT
Disable FET drain to 
source fault detection 
at start-up
1
Low drain to source 
voltage doesn’t trigger 
a fault
0
0
Low drain to source 
voltage triggers a fault
13
SC_RETRY
Retry after short-
circuit fault (Fast-trip)
1
Retry once into 
current limit (Not a 
latched fault)
0
0
Remain off (latched 
fault)
12:11
SPFAIL
Scalable fast-trip 
threshold
11
225% of IOCP(TOTAL)
10
10
200% of IOCP(TOTAL)
01
175% of IOCP(TOTAL)
00
150% of IOCP(TOTAL)
10:9
DVDT_CONFIG
DVDT current scaling
11
150%
10
10
100%
01
75%
00
50%
8
VIN_TRAN_DIS
Input transient 
blanking control
1
Disabled
0
0
Enabled
7
EXT_EEPROM
External EEPROM 
connection
1
External EEPROM 
connected
0
Read/Write
0
External EEPROM 
not connected
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
98
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 99

Table 8-54. DEVICE_CONFIG Register Description (continued)
Bit
Name
Value
Description
Default
Access
6
IREF_DAC2_SEL
IREF/DAC2 pin 
output selection
Read/Write
1
DAC2
0
0
IREF DAC
Read/Write
5
CMP2_POL
Comparator-2 
(COMP2) polarity 
(AUX pin)
1
Active Low
0
0
Active High
4
CMP1_POL
Comparator-1 
(COMP1) polarity 
(TEMP/CMP pin)
Read/Write
1
Active Low
0
0
Active High
3
ADC_HI_PERF
ADC performance 
and speed selection
1
High performance 
mode (Effective 
throughput = 18 µs)
0
Read/Write
0
High speed mode 
(Effective throughput 
= 11 µs)
2
CMP1_IN_SEL
+ve input signal 
for the Comparator-1 
(CMP1) at 
TEMP/CMP pin
1
TEMP pin
0
0
IMON pin
Read/Write
1
CMP1_FLT
Comparator-1 
(COMP1) fault 
(TEMP/CMP pin)
1
CMP1_FLT is a 
latched fault and turns 
off the device
0
0
CMP1_FLT is not 
a latched fault and 
doesn’t turn off the 
device
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
99
Product Folder Links: TPS25990



---

## Page 100

Table 8-54. DEVICE_CONFIG Register Description (continued)
Bit
Name
Value
Description
Default
Access
0
CMP2_FLT
Comparator-2 
(COMP2) fault (AUX 
pin)
Read/Write
1
CMP2_FLT is a 
latched fault and turns 
off the device
0
0
CMP2_FLT is not 
a latched fault and 
doesn’t turn off the 
device
Note
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
8.3.14.7.1.63 BB_CONFIG (E5h, Read/Write Byte)
BB_CONFIG is a manufacturer-specific command for configuring or reading the behavior of the Blackbox 
function as described in Section 8.3.14.11.
This command uses the PMBus® read or write byte protocol.
The details of this register are shown in Table 8-55.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
100
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 101

Table 8-55. BB_CONFIG Register Description
Bit
Name
Value
Description
Default
Access
7
FET_OFF_WR
BB EEPROM write 
trigger
Read/Write
1
Power FET turning 
OFF triggers write to 
BB EEPROM
0
0
Power FET turning 
OFF doesn’t trigger 
write to BB EEPROM
6
FLT_WR
BB EEPROM write 
trigger
1
Global Fault triggers 
write to BB EEPROM
0
0
Global Fault doesn’t 
trigger write to BB 
EEPROM
5
ALERT_WR
BB EEPROM write 
trigger
1
SMBA# assertion 
triggers write to BB 
EEPROM
0
0
SMBA# assertion 
doesn’t trigger write to 
BB EEPROM
4:2
Reserved
000
Reserved
000
1:0
BB_TICK
Blackbox timestamp 
tick interval
11
3500 µs
00
10
870 µs
01
220 µs
00
55 µs
Note
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
BB_CONFIG[5] needs to be used in conjunction with the ALERT_MASK register to determine 
which events trigger the Blackbox write to the external EEPROM. However, the GLBL_FLT 
(ALERT_MASK[6]) signal is excluded from the list of signals driving ALERT for Blackbox write even if 
they are unmasked in the ALERT_MASK register.
8.3.14.7.1.64 OC_TIMER (E6h, Read/Write Byte)
OC_TIMER is a manufacturer-specific register used to program the overcurrent blanking digital timer duration as 
described in Section 8.3.4.2.
This command uses the PMBus® read/write byte protocol.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
101
Product Folder Links: TPS25990



---

## Page 102

The details of this register are shown in Table 8-56.
Table 8-56. OC_TIMER Register Description
Bit
Name
Description
Value
Overcurrent 
Blanking Timer 
Duration (ms)
Default Value
Access
7:0
OC_TIMER
Overcurrent 
blanking digital 
timer
0x00h
0
0x14h
Read/Write
0x01h
0.109
0x02h
0.218
0x03h
0.327
0x04h
0.436
0x05h
0.545
0x06h
0.654
0x07h
0.763
...
0x0Ah
1.09
...
0x14h
2.18
...
0x64h
10.9
...
0xC8h
21.8
...
0xFFh
27.8
Note
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
8.3.14.7.1.65 RETRY_CONFIG (E7h, Read/Write Byte)
RETRY_CONFIG is a manufacturer-specific command for configuring or reading the retry behavior of the 
TPS25990 eFuse in the event of a fault as depicted in Section 8.3.10.1.
This command uses the PMBus® read or write byte protocol.
The details of this register are shown in Table 8-57.
Table 8-57. RETRY_CONFIG Register Description
Bit
Name
Value
Description
Default
Access
7:6
RESPONSE
10
Shutdown and retry
10
Read
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
102
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 103

Table 8-57. RETRY_CONFIG Register Description (continued)
Bit
Name
Value
Description
Default
Access
5:3
RETRY_CNT
Retry count
Read/Write
111
Retry indefinitely
000
110
Retry 64 times
101
Retry 32 times
100
Retry 16 times
011
Retry 8 times
010
Retry 4 times
001
Retry 1 times
000
Retry 0 times (Latch-
off)
2:0
RETRY_DLY
Retry delay timer 
value
111
7000 ms
100
110
3500 ms
101
1750 ms
100
870 ms
011
435 ms
010
220 ms
001
110 ms
000
55 ms
Note
•
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
•
The delay used in the POWER_CYCLE command is also configured through Bit[2:0] of this 
register.
8.3.14.7.1.66 ADC_CONFIG_1 (E8h, Read/Write Byte)
ADC_CONFIG_1 is a manufacturer-specific command for configuring or reading channel selections and modes 
for ADC sampling as described in Section 8.3.14.8.
This command uses the PMBus® read or write byte protocol.
The details of this register are shown in Table 8-58.
Table 8-58. ADC_CONFIG_1 Register Description
Bit
Name
Value
Description
Default
Access
7
EOC
End of conversion 
indication (Active 
Low)
Read
1
ADC is busy 
(Conversion in 
progress)
0
0
Conversion done
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
103
Product Folder Links: TPS25990



---

## Page 104

Table 8-58. ADC_CONFIG_1 Register Description (continued)
Bit
Name
Value
Description
Default
Access
6
CONVST
Software conversion 
start control (used 
with MODE = 01)
Read/Write
1
Start conversion
0
0
Do not start 
conversion
5:4
MODE
ADC sampling mode
11
Continuous 
conversion - Single 
channel
00
10
Single channel single 
conversion - External 
pin controlled
01
Single channel single 
conversion – software 
controlled
00
Continuous 
conversion – auto 
sequenced
3:0
CONV_CH_SEL
Parameter/ADC 
Channel selection for 
sampling (MODE = 
01 or 10 or 11)
1001-1111
Reserved
0000
1000
GND (Applicable only 
in MODE = 01 or 10)
0111
VIREF (Applicable 
only in MODE = 01 or 
10)
0110
ADDR1 (Applicable 
only in MODE = 01 or 
10)
0101
ADDR0 (Applicable 
only in MODE = 01 or 
10)
0100
VAUX
0011
VTEMP
0010
IIN
0001
VOUT
0000
VIN
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
104
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 105

Note
•
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
•
MODE = 10 or 01 are debug-only modes and not recommended to be used during normal 
operation as they prevent the ADC from sampling all the necessary signals needed for the eFuse 
protection features.
8.3.14.7.1.67 ADC_CONFIG_2 (E9h, Read/Write Byte)
ADC_CONFIG_2 is a manufacturer-specific command for configuring or reading parameter selection and 
decimation rate (sample skip count) for high speed ADC sample buffering as described in Section 8.3.14.7.1.42.
This command uses the PMBus® read or write byte protocol.
The details of this register are shown in Table 8-59.
Table 8-59. ADC_CONFIG_2 Register Description
Bit
Name
Value
Description
Default
Access
7
VAUX_VTEMP_SEL
Average auxiliary 
voltage or average 
temperature telemetry 
selection
Read/Write
1
Use VAUX ADC 
channel as input 
for AUX_AVG 
computation
0
0
Use TEMP ADC 
channel as input 
for TEMP_AVG 
computation
6
Reserved
0
Reserved
0
Read
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
105
Product Folder Links: TPS25990



---

## Page 106

Table 8-59. ADC_CONFIG_2 Register Description (continued)
Bit
Name
Value
Description
Default
Access
5:3
BUF_CH_SEL
Parameter selection 
for buffering
Read/Write
111
Reserved (Will default 
to IIN)
000
110
Reserved (Will default 
to IIN)
101
Reserved (Will default 
to IIN)
100
VAUX
011
VTEMP
010
IIN
001
VOUT
000
VIN
2:0
DEC_RATE
Decimation rate 
(sample skip count) 
for ADC sample 
buffering
111
Decimation rate 
(sample skip count) = 
7
0000
110
Decimation rate 
(sample skip count) = 
6
101
Decimation rate 
(sample skip count) = 
5
100
Decimation rate 
(sample skip count) = 
4
011
Decimation rate 
(sample skip count) = 
3
010
Decimation rate 
(sample skip count) = 
2
001
Decimation rate 
(sample skip count) = 
1
000
Decimation rate 
(sample skip count) = 
0
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
106
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 107

Note
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
8.3.14.7.1.68 PK_MIN_AVG (EAh, Read/Write Byte)
PK_MIN_AVG is a manufacturer-specific command that resets all the maximum, minimum, and 
average 
telemetry 
registers, 
such 
as 
READ_VIN_PEAK, 
READ_IIN_PEAK, 
READ_TEMP_PEAK, 
READ_PIN_PEAK, 
READ_VIN_MIN, 
READ_VOUT_MIN, 
READ_VIN_AVG, 
READ_VOUT_AVG, 
READ_IIN_AVG, READ_TEMP_AVG, and READ_PIN_AVG. This register is also used to program the number 
of ADC samples to be used for averaging. Averaging a higher number of samples improves the accuracy at the 
expense of higher latency.
This command uses the PMBus® read or write byte protocol.
The details of this register are shown in Table 8-60.
Table 8-60. PK_MIN_AVG Register Description
Bit
Name
Value
Description
Default
Access
7
RESET_PEAK
1
Reset all peak 
registers to 0
0
Read/Write
0
No action
6
RESET_AVG
1
Reset all average 
registers to 0
0
0
No action
5
RESET_MIN
1
Reset all minimum 
registers to 0
0
0
No action
4:3
Reserved
00
Reserved
00
2:0
AVG_CNT
111
Average count = 128
000
110
Average count = 64
101
Average count = 32
100
Average count = 16
011
Average count = 8
010
Average count = 4
001
Average count = 2
000
Average count = 1
Note
•
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
•
As soon as the PK_MIN_AVG command is executed to clear the peak, minimum, and average 
registers, the RESET_PEAK, READ_MIN, and READ_AVG bits are automatically cleared to zero 
(0).
8.3.14.7.1.69 VCMPxREF (EBh, Read/Write Byte)
VCMPxREF is a manufacturer-specific command for configuring or reading reference thresholds for general 
purpose comparators as described in Section 8.3.12.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
107
Product Folder Links: TPS25990



---

## Page 108

This command uses the PMBus® read or write byte protocol.
A 4-bit reference threshold is defined by VCMPxREF[3:0] for Comparator-1 (CMP1) and by VCMPxREF[7:4] 
for Comparator-2 (CMP2). Individually, VCMPxREF[3:0] and VCMPxREF[7:4] use the PMBus® DIRECT format. 
When reading and writing to this register, use the coefficients shown in Table 8-67, Equation 19, and Equation 20 
for VCMPxREF[3:0] and VCMPxREF[7:4] separately to define each individual comparator's threshold.
Contents of this register drive a DAC to set the thresholds for the two (2) general purpose comparators. The 
details of this register are shown in Table 8-61.
Table 8-61. VCMPxREF Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Default Value
Access
7:4
CMP2REF
Programmable 
reference voltage 
for Comparator-2 
(CMP2)
0x0xh (0.2 V)
0xFxh (1.7 V)
0xFxh (1.7 V)
Read/Write
3:0
CMP1REF
Programmable 
reference voltage 
for Comparator-1 
(CMP1)
0xx0h (0.2 V)
0xxFh (1.7 V)
0xxFh (1.7 V)
Note
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
8.3.14.7.1.70 PSU_VOLTAGE (ECh, Read/Write Byte)
PSU_VOLTAGE is a manufacturer-specific command for configuring or reading an 8-bit data corresponding to 
the input power supply voltage for implementing the input cable fault detection feature.
This command uses the PMBus® read or write byte protocol.
•
Sending a value to the PSU_VOLTAGE register:
Real world value of input power supply voltage in V is converted into a 10-bit binary data through PMBus® 
DIRECT format conversion using Equation 20 and the 'm', 'b', & 'R' coefficients corresponding to READ_VIN 
in Table 8-67. Hexadecimal value corresponding to the eight least significant bits from this 10-bit binary data 
needs to be written in the PSU_VOLTAGE register.
•
Interpreting the received values from the PSU_VOLTAGE register:
One byte of hexadecimal data read from the PSU_VOLTAGE register needs to be converted into a 10-bit 
binary data by appending the READ_VIN[9:8] bits to the left side. The hexadecimal value corresponding to 
this 10-bit binary data needs to be converted to a real world value of input power supply voltage in V through 
PMBus® DIRECT format conversion using Equation 19 and the 'm', 'b', & 'R' coefficients corresponding to 
READ_VIN in Table 8-67.
The details of this register are shown in Table 8-62.
Table 8-62. PSU_VOLTAGE Register Description
Bit
Name
Description
READ_VIN[9:8]
Minimum 
Value
Maximum Value
Default Value
Access
7:0
PSU_VOLTAGE
Nominal 
input power 
supply 
voltage
00
0x00h (0 V)
0xFFh (4.86 V)
0x9Dh (2.99 V)
Read/Write
01
0x00h (4.87 V)
0xFFh (9.73 V)
0x9Dh (7.86 V)
10
0x00h (9.75 V)
0xFFh (14.61 V)
0x9Dh (12.74 V)
11
0x00h (14.63 
V)
0xFFh (19.48 V)
0x9Dh (17.62 V)
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
108
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 109

Note
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
8.3.14.7.1.71 CABLE_DROP (EDh, Read/Write Byte)
CABLE_DROP is a manufacturer-specific command that allows configuring or reading an 8-bit reference 
threshold for the maximum cable voltage drop expected to implement the input cable fault detection feature. 
This command uses the PMBus® DIRECT format. When reading and writing to this register, use the coefficients 
shown in Table 8-67, Equation 19, and Equation 20.
This command uses the PMBus® read or write byte protocol.
Contents of this register are compared with the difference between PSU_VOLTAGE and VIN ADC telemetry 
values. If this difference value exceeds the value in the CABLE_DROP register, the VIN_CABLE_FAULT flags 
are set in the respective registers. The SMBA# signal is asserted. When the difference between PSU_VOLTAGE 
and VIN ADC telemetry value falls below the CABLE_DROP threshold, and the CLEAR_FAULTS command is 
sent afterwards, this warning flag and alart are cleared. The details of this register are shown in Table 8-49.
Table 8-63. CABLE_DROP Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Default Value
Access
7:0
CABLE_DROP
Maximum cable 
voltage drop 
expected
0x00h (0 V)
0xFFh (4.845 V)
0xFFh (4.845 V)
Read/Write
When the input cable fault is detected, the device:
•
sets the NONE_OF_THE_ABOVE/UNKNOWN bit in the STATUS_BYTE register
•
sets the NONE_OF_THE_ABOVE/UNKNOWN bit in the upper byte of the STATUS_WORD register
•
sets the VIN_CABLE_FLT bit in the STATUS_MFR_SPECIFIC_2 register
•
notifies the host asserting SMBA#, if it is not masked setting the UNKNOWN bit low in the ALERT_MASK 
register
Note
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
8.3.14.7.1.72 GPDAC1 (F0h, Read/Write Byte)
GPDAC1 is a manufacturer-specific command that allows configuring or reading a 6-bit data driving a general 
purpose DAC to generate a constant current output at PIN-6 (DAC1). This command uses the PMBus® DIRECT 
format. When reading and writing to this register, use the coefficients shown in Table 8-67, Equation 19, and 
Equation 20.
This command uses the PMBus® read or write byte protocol.
The details of this register are shown in Table 8-64.
Table 8-64. GPDAC1 Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Default Value
Access
7:0
GPDAC1
General purpose 
DAC output-1
0x00h (6 µA)
0x3Fh (53.25 µA)
0x00h (6 µA)
Read/Write
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
109
Product Folder Links: TPS25990



---

## Page 110

Note
•
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
•
Writing 1xxxxxxb in this register disconnects the DAC output from the DAC1 pin making the pin 
high-impedance and sink no current.
8.3.14.7.1.73 GPDAC2 (F1h, Read/Write Byte)
GPDAC2 is a manufacturer-specific command that allows configuring or reading a 6-bit data driving a general 
purpose DAC to generate a constant voltage output on the IREF/DAC2 pin. This command uses the PMBus® 
DIRECT format. When reading and writing to this register, use the coefficients shown in Table 8-67, Equation 19, 
and Equation 20.
This command uses the PMBus® read or write byte protocol. The details of this register are shown in Table 
8-65.
Table 8-65. GPDAC2 Register Description
Bit
Name
Description
Minimum Value
Maximum Value
Default Value
Access
7:0
GPDAC2
General purpose 
DAC output-2
0x00h (0.3 V)
0x3Fh (1.186 V)
0x00h (0.3 V)
Read/Write
Note
•
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
•
The GPDAC2 output is multiplexed with the VIREF DAC output and either one of them can be 
brought out to the IREF/DAC2 pin at a time depending on DEVICE_CONFIG[6] bit setting.
•
If the GPDAC2 output is brought out to the IREF/DAC2 pin, the VIREF DAC voltage is still 
connected internally to the overcurrent & short-circuit protections and active current sharing blocks. 
This ensures the protection thresholds are determined by the VIREF DAC setting and not by the 
voltage on the IREF/DAC2pin.
•
When using a TPS25990 eFuse with one or more TPS25985 eFuse(s) in parallel, the VIREF 
output must be brought out on the IREF/DAC2 pin. The DEVICE_CONFIG[6] setting to bring the 
GPDAC2 output on the pin must not be used in this configuration. This is to ensure the VIREF 
setting controls the reference for overcurrent & short-circuit protections and active current sharing 
for all the devices in the parallel chain.
8.3.14.7.1.74 INS_DLY (F9h, Read/Write Byte)
INS_DLY is a manufacturer-specific command which is used to program the insertion delay at start-up. The 
device implements a fixed analog insertion delay of 14 ms (typical). As described in Table 8-66, the INS_DLY 
register specifies a delay in addition to the fixed 14 ms delay.
This command uses the PMBus® read/write byte protocol.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
110
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 111

Table 8-66. INS_DLY Register Description
Bit
Name
Description
Value
Effective 
Insertion Delay 
(ms)
Default Value
Access
7:0
INS_DLY
Insertion delay at 
start-up
0x00h
14
0x00h
Read/Write
0x01h
25
0x02h
68
0x03h
123
0x04h
230
0x05h
340
0x06h
450
0x07h
560
Note
A write command to this register should be preceded by the MFR_WRITE_PROTECT command to 
unlock the device first to prevent accidental accidental/spurious writes.
8.3.14.8 Analog-to-digital Converter
The TPS25590x integrates a 10-bit, 460 KSPS SAR ADC preceded by an analog MUX. The following signals 
are available for sampling by the ADC:
1.
VIN
2.
VOUT
3.
VIMON
4.
VTEMP
5.
VAUX
6.
ADDR0
7.
ADDR1
The ADC uses a 5 kHz low-pass filter at the input to suppress high frequency noise (outside the ADC Nyquist 
bandwidth) and prevent aliasing.
Note
The ADC also supports a high performance mode wherein the sampling rate is traded off in favor of 
improved DNL and INL. In this mode, the sampling rate is reduced to 270 KSPS. This mode can be 
selected by setting the ADC_HI_PERF bit in the DEVICE_CONFIG register.
During normal operation, the ADC automatically sequences the channels. The ADC channel sequencer 
manages MUX channel selection for sampling.
Note
•
The ADDR0 and ADDR1 signals are sampled only at startup to decode the PMBus® target 
address.
•
The ADC implements background self-calibration to eliminate offset and gain errors inherent to the 
ADC.
The device also supports buffering of multiple samples of a selected parameter in RAM, which can be read by 
the host using the ADC_SAMPLE_BUF block read command. This allows the system designer to reconstruct the 
time domain profile/waveform of that parameter in a given interval. This can be useful during design/debugging 
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
111
Product Folder Links: TPS25990



---

## Page 112

by functioning like an in-built "digital oscilloscope". The ADC channel to sample for buffering and the decimation 
rate/sample skip count can be user configured using PMBus® writes to the ADC_CONFIG_2 register.
The TPS25990 can post-process raw ADC sampled data to compute the following derived parameters:
1.
VIN Average
2.
VIN Peak
3.
VIN Min
4.
VOUT Average
5.
VOUT Min
6.
IIN Average
7.
IIN Peak
8.
PIN
9.
PIN Average
10. PIN Peak
11. EIN
12. Temperature Average
13. Temperature Peak
14. Cable voltage drop
A single ADC sample can have higher errors due to internal noise. It’s possible to improve the ADC SNR and 
the telemetry accuracy by averaging higher number of samples. The number of samples to be averaged is 
user-programmable using the PK_MIN_AVG register. The minimum, maximum, and average values can also be 
reset using the PK_MIN_AVG register.
The TPS25990 performs digital comparison on the ADC sampled data to detect the following system events.
1.
VIN UV WARN
2.
VIN UV FAULT
3.
VIN OV WARN
4.
VOUT PGOOD
5.
IIN OC WARN
6.
OT WARN
7.
OT FAULT
8.
PIN OP WARN
9.
CABLE FAULT
The results of the comparisons are reflected in the PMBus® status registers and can be configured to trigger 
other actions e.g. FET turn OFF (protection response) and FLT output assertion for faults, SMBA# signal 
assertion for faults/warnings and Blackbox RAM/EEPROM update.
8.3.14.9 Digital-to-analog Converters
The TPS25990 integrates multiple DACs which are used to set the thresholds or gains of various blocks:
1.
VIREF: This is a 6-bit buffered voltage output DAC which provides a programmable threshold for overcurrent 
protection, short-circuit protection and active current sharing blocks. This can be programmed using the 
VIREF register. This signal is available internally always for these blocks, and optionally can be brought on 
the IREF/DAC2 pin to drive other devices in a parallel chain.
2.
IDVDT: This is a 2-bit current output DAC which sources current on the DVDT pin to provide output Slew 
Rate (DVDT) control. This can be programmed using the DEVICE_CONFIG[10:9] register bits.
3.
DAC1: This is a 6-bit general purpose current output DAC which can sink current on the DAC1 pin. This can 
be programmed using the GPDAC1 register.
4.
DAC2: This is a 6-bit general purpose voltage output DAC. This can be programmed using the GPDAC2 
register. This can be brought out to the IREF/DAC2 pin and is multiplexed with the VIREF DAC.
5.
VOV: This is a 4-bit DAC which provides a programmable threshold for the VIN overvoltage protection 
comparator. This can be programmed using the VIN_OV_FLT register.
6.
CMP2REF: This is a 4-bit voltage output DAC which provides a programmable threshold for general purpose 
analog comparator-2 (CMP2) on AUX pin. This can be programmed using the VCMPxREF[7:4] register bits.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
112
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 113

7.
CMP1REF: This is a 4-bit voltage output DAC which provides a programmable threshold for general purpose 
analog comparator-1 (CMP1) on TEMP/CMP pin. This can be programmed using the VCMPxREF[3:0] 
register bits.
8.3.14.10 DIRECT format Conversion
For telemetry and configuration parameters, the TPS25990 supports DIRECT format. Digital codes for telemetry 
or configuration parameters can be converted to their equivalent real world units using Equation 19 and Equation 
20.
•
Interpreting received values:
The host system uses Equation 19 to convert the value received from the PMBus® device into a reading of V, 
A, °C, or W:
X = 1
m Y × 10−R −b
(19)
Where:
–
X, is the calculated, “real world” value in the appropriate units (V, A, °C, or W);
–
m, the slope coefficient, is a two byte, two’s complement integer;
–
Y, is a two byte two’s complement integer received from the PMBus® device;
–
b, the offset, is a two byte, two’s complement integer; and
–
R, the exponent, is a one byte, two’s complement integer.
•
Sending a value:
To send a value, the host must use Equation 20 to find the value of Y:
Y = mX + b × 10R
(20)
Where:
–
Y is the two byte two’s complement integer to be sent to the unit;
–
m, the slope coefficient, is the two byte, two’s complement integer;
–
X, a “real world” value, in units such as V, A, °C, or W, to be converted for transmission;
–
b, the offset, is the two byte, two’s complement integer; and
–
R, the exponent, is the decimal value equivalent to the one byte, two’s complement integer.
Table 8-67. TPS25990 PMBus® DIRECT format Conversion Guide
Parameter
Units
Zero Code 
Analog Value
Full scale 
Digital Code
Full-scale 
Analog Value
m
b
R
READ_VIN
V
0
0x3FF
19.48
5251
0
- 2
READ_VIN_PEAK
V
0
0x3FF
19.48
5251
0
- 2
READ_VIN_PEAK_EEPROM
V
0
0xFF
19.42
13128
0
- 3
READ_VIN_MIN
V
0
0x3FF
19.48
5251
0
- 2
READ_VIN_AVG
V
0
0x3FF
19.48
5251
0
- 2
VIN_UV_WARN
V
0
0xFF
19.42
13128
0
- 3
VIN_UV_FLT
V
0
0xFF
19.42
13128
0
- 3
VIN_OV_WARN
V
0
0xFF
19.42
13128
0
- 3
VIN_OV_FLT
V
2.95
0xF
17.72
10163
− 30081
- 4
READ_VOUT
V
0
0x3FF
19.48
5251
0
- 2
READ_VOUT_AVG
V
0
0x3FF
19.48
5251
0
- 2
READ_VOUT_MIN
V
0
0x3FF
19.48
5251
0
- 2
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
113
Product Folder Links: TPS25990



---

## Page 114

Table 8-67. TPS25990 PMBus® DIRECT format Conversion Guide (continued)
Parameter
Units
Zero Code 
Analog Value
Full scale 
Digital Code
Full-scale 
Analog Value
m
b
R
VOUT_UV_WARN
V
0
0xFF
19.42
13128
0
- 3
VOUT_PGTH
V
0
0xFF
19.42
13128
0
- 3
READ_IIN
A
0
0x3FF
107250/RIMON
9.538 × RIMON
0
- 3
READ_IIN_AVG
A
0
0x3FF
107250/RIMON
9.538 × RIMON
0
- 3
READ_IIN_PEAK
A
0
0x3FF
107250/RIMON
9.538 × RIMON
0
- 3
READ_IIN_PEAK_EEPROM
A
0
0xFF
107250/RIMON
23.8 × RIMON
0
- 4
IIN_OC_WARN
A
0
0xFF
107250/RIMON
23.8 × RIMON
0
- 4
READ_TEMPERATURE_1
°C
− 229.3
0x3FF
501.4
140
32100
- 2
READ_TEMP_AVG
°C
− 229.3
0x3FF
501.4
140
32100
- 2
READ_TEMP_PEAK
°C
− 229.3
0x3FF
501.4
140
32100
- 2
READ_TEMP_PEAK_EEPROM
°C
− 228.7
0xFF
499.8
35
8006
- 2
OT_WARN
°C
− 228.7
0xFF
499.8
35
8006
- 2
OT_FLT
°C
− 228.7
0xFF
499.8
35
8006
- 2
VAUX
V
0
0x3FF
1.95
5251
0
- 1
VAUX_AVG
V
0
0x3FF
1.95
5251
0
- 1
READ_PIN
W
0
0x3FF
2091375/RIMON
4.901 × RIMON
0
- 4
READ_PIN_PEAK
W
0
0x3FF
2091375/RIMON
4.901 × RIMON
0
- 4
READ_PIN_AVG
W
0
0x3FF
2091375/RIMON
4.901 × RIMON
0
- 4
PIN_OP_WARN
W
0
0xFF
2091375/RIMON
12.217 × RIMON
0
- 5
READ_EIN
J
0
0x7FFF
-
38.22 × RIMON
0
- 7
VIREF
V
0.3
0x3F
1.186
7111
− 2133
- 2
GPDAC1
µA
6
0x3F
53.25
1333
− 8000
- 3
GPDAC2
V
0.3
0x3F
1.186
7111
− 2133
- 2
CMP2REF {VCMPXREF[7:4]}
V
0.2
0xF
1.7
10000
− 2000
- 3
CMP1REF {VCMPXREF[3:0]}
V
0.2
0xF
1.7
10000
− 2000
- 3
CABLE_VOLTAGE_DROP
V
0
0xFF
4.845
5263
0
- 2
READ_SAMPLE_BUF_VIN
V
0
0xFF
19.42
13128
0
- 3
READ_SAMPLE_BUF_VOUT
V
0
0xFF
19.42
13128
0
- 3
READ_SAMPLE_BUF_TEMP
°C
-228.7
0xFF
499.8
35
8006
- 2
READ_SAMPLE_BUF_VAUX
V
0
0xFF
1.94
13128
0
- 2
READ_SAMPLE_BUF_IIN
A
0
0xFF
107250/RIMON
23.8 × RIMON
0
- 4
8.3.14.11 Blackbox Fault Recording
The Blackbox feature greatly enhances the ability of the system designer to debug power path related issues 
during design/development and in case of field returns. Along with a snapshot of the parametric data and 
event information through various status registers, the TPS25990 provides additional information which helps to 
re-create the sequence of events as they occurred in a certain interval of time. This information is available in 
both the on-chip volatile memory and the external I2C EEPROM (connected on the EECLK/EEDATA pins) and 
can be accessed through PMBus®.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
114
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 115

Note
The PMBus® engine is up and running as soon as a stable supply is available on VDD, independent 
of VIN and other related internal nodes. This ensures that the Blackbox contents can be read back 
from a field return unit by applying power on VDD pin even if there’s damage on VIN side or Power 
FET .
During the operation of the device, the Blackbox information is stored inside the Blackbox buffer RAM which is 
seven (7) bytes deep. At any point of time, issuing the READ_BB_RAM command will retrieve the most recent 
seven (7) events in a sequence along with the timestamp relative to each other. Each byte of this buffer RAM 
holds the following information about a single event:
1.
A 3-bit event identifier
2.
A 5-bit value which indicates the time lapse because the previous event. The lower 4 bits of the timer value 
represents a snapshot of the free running Blackbox tick timer at the instant of registering the event in the 
Blackbox RAM. The 5th bit indicates whether the timer has overflowed at least once since the last event.
The event identifier and relative timer information help the system designer to reconstruct a timeline of events 
as they occurred, thereby enhancing the debug capabilities as compared to viewing a single snapshot of status 
registers. The Blackbox tick timer is a free running timer which is reset to zero after every event. The timer 
update rate can be configured through the BB_CONFIG register. This allows the users to make a tradeoff 
between fine timing resolution and longer time span as per their debug needs. The BB_TMR_EXP bit in the 
BB_TIMER register indicates if the Blackbox tick timer has overflowed at least since the last event. This bit 
indicates whether the event entries in the RAM are relatively recent or old. This bit is latched when the timer 
overflows and reset to zero along with the free running timer when the next event occurs.
Here are the events which will trigger a write to the Blackbox RAM:
1.
VIN_UV_WARN
2.
VIN_OV_WARN
3.
OC_WARN
4.
OT_WARN
5.
OC_DET
6.
VIN_TRAN
7.
IN_OP_WARN
Once the device encounters a global fault or alert event (based on the ALERT_MASK), the Blackbox RAM 
contents, along with the status registers, peak input voltage, peak input current, peak device temperature, and 
Blackbox timer values are written to an external EEPROM through the EECLK/EEDATA pins.
Note
The EEPROM interface is a standard I2C controller and operates at 400 kHz clock speed. TI 
recommends using an I2C EEPROM with minimum 1 Kbits of capacity and 16-byte page addressing. 
Examples of compatible EEPROM devices include 24LC04, 24AA04, etc.
The 
contents 
of 
the 
Blackbox 
RAM 
along 
with 
some 
status 
registers 
(STATUS_WORD, 
STATUS_MFR_SPECIFIC, and STATUS_INPUT) and certain parameters (VIN_PEAK, IIN_PEAK, and 
TEMPERATURE_PEAK) are stored into Page-0 of an external EEPROM when the following conditions are 
met. At the same time, Blackbox RAM contents and Blackbox tick timer values are locked.
1.
An external EEPROM is successfully connected by setting the EXT_EEPROM bit high in the 
DEVICE_CONFIG register. In addition, it is done by configuring two (2) of the four (4) GPIOs as EECLK 
and EEDATA appropriately in the GPIO_CONFIG_12 and GPIO_CONFIG_34 registers. Make sure those 
two (2) selected GPIO pins are physically connected to the EEPROM clock and data pins respectively on the 
board.
2.
Any one of the three BB EEPROM write trigger bits is set in the BB_CONFIG register.
Blackbox EEPROM contents:
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
115
Product Folder Links: TPS25990



---

## Page 116

1.
BB_RAM_0 to BB_RAM_6 [Seven (7) bytes]
2.
BB_TIMER [One (1) byte]
3.
STATUS_WORD [Two (2) bytes]
4.
STATUS_MFR_SPECIFIC [One (1) byte]
5.
STATUS_INPUT [One (1) byte]
6.
VIN_PEAK [One (1) byte, Eight (8) MSBs from the 10-bit ADC output data]
7.
IIN_PEAK [One (1) byte, Eight (8) MSBs from the 10-bit ADC output data]
8.
TEMPERATURE_PEAK [One (1) byte, Eight (8) MSBs from the 10-bit ADC output data]
9.
CHECKSUM [One (1) byte]
Time >
BB_TIMERMAX
. . . .
BB_RAM_0
BB_RAM_1
BB_RAM_2
CHECKSUM
TEMP_PEAK
STATUS_L
IIN_PEAK
BB_RAM_6
VIN_PEAK
STATUS_INPUT
STATUS_MFR
STATUS_H
Warning Event 1
Warning Event 2
Warning Event 3
Warning Event 7
Fault/Alert/
Shutdown
BB_TIMER
BB_RAM_6
BB_RAM_0
BB_RAM_5
BB_RAM_4
BB_RAM_3
BB_RAM_2
BB_RAM_1
Time < 
BB_TIMERMAX
BB_TICK_PER = f(BB_CONFIG[1:0])
BB_TIMERMAX = 16 * BB_TICK_PER
Write to BB RAM
Write to BB EEPROM
- Event ID 1
- BB_TIMER_EXP 
   = 1
- BB_TICK 
   current value
. . . .
- Event ID 2
- BB_TIMER_EXP 
   = 1
- BB_TICK 
   current value
- Event ID 7
- BB_TIMER_EXP 
   = 1
- BB_TICK 
   current value
Time > 
BB_TIMERMAX
. . . .
- Event ID 3
- BB_TIMER_EXP 
   = 0
- BB_TICK 
   current value
Time
Figure 8-21. Blackbox Operation Example
8.4 Device Functional Modes
The features of the device depend on the operating mode. Table 8-68 summarizes the device functional modes.
Table 8-68. Device Functional Modes Based on EN/UVLO Pin
Pin Condition
Device State
Output Discharge
EN/UVLO > VUVLO(R)
Fully ON
Disabled
VSD(F) < EN/UVLO < VUVLO(F) (time < tQOD)
FET OFF
Disabled
VSD(F) < EN/UVLO < VUVLO(F) (time > tQOD)
FET OFF
Enabled
EN/UVLO < VSD(F)
Shutdown
Disabled
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
116
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 117

9 Application and Implementation
Note
Information in the following applications sections is not part of the TI component specification, 
and TI does not warrant its accuracy or completeness. TI’s customers are responsible for 
determining suitability of components for their purposes, as well as validating and testing their design 
implementation to confirm system functionality.
9.1 Application Information
The TPS25990 is a high-current eFuse that is typically used for input power rail protection and monitoring 
applications. The device operates from 2.9 V to 16 V and supports various user adjustable and programmable 
protection options. The device provides ability to control inrush current and offers protection against overvoltage, 
overcurrent, short-circuit and overtemperature conditions. The device can be used in a variety of systems such 
as server motherboards, add-on cards, graphics cards, accelerator cards, enterprise switches, routers, and 
so forth. The design procedure explained in the subsequent sections can be used to select the supporting 
component values based on the application requirements. Additionally, a spreadsheet design tool, TPS25990x 
Design Calculator is available in the web product folder.
9.1.1 Single Device, Standalone Operation
EN/UVLO
IN
IMON
VIN
VOUT
TPS25990x
TEMP/CMP
ILIM
DVDT
IREF/DAC2
VDD
PG
PG
SWEN
GND
IMON
OUT
FLT
FLT
FLT
FLT
EN
VLSTBY
VL
VL
ADDR1
AUX
SCL
SDA
SMBA#
ADDR0
VL
VL
VL
SCL
SDA
SMBA#
DAC1
Figure 9-1. Single Device, Standalone Operation
9.1.2 Multiple Devices, Parallel Connection
Applications which need higher current input protection along with digital interface for telemetry, control, 
configurability can use one or more TPS25985 devices in parallel with TPS25990 as shown in Figure 9-2.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
117
Product Folder Links: TPS25990



---

## Page 118

EN/UVLO
EN/UVLO
EN/UVLO
FLT
FLT
FLT
IN
IN
OUT
IN
OUT
IMON
IMON
IMON
ILIM
ILIM
DVDT
DVDT
ITIMER
ITIMER
VIN
VOUT
TPS25990x
TPS25985x
TPS25985x
TEMP
TEMP
IREF
TEMP/CMP
ILIM
DVDT
IREF/DAC2
IREF
VDD
VDD
VDD
PG
PG
PG
PG
FLT
SWEN
SWEN
SWEN
GND
GND
GND
IMON
OUT
ADDR1
AUX
SCL
SDA
SMBA#
SCL
SDA
SMBA#
ADDR0
MODE
MODE
EN
VLSTBY
VL
VL
VL
VL
VL
Figure 9-2. TPS25990 Connected in Parallel with TPS25985x For Higher Current Support With PMBus® 
In this configuration, the TPS25990 acts as the primary device and controls the other TPS25985x devices in 
the chain which are designated as secondary devices. This configuration is achieved by connecting the primary 
device as follows:
1.
VDD is connected to IN through an R-C filter.
2.
DVDT is connected through capacitor to GND.
3.
IREF is connected through capacitor to GND.
4.
IMON is connected through resistor to GND.
5.
ILIM is connected through resistor to GND.
SWEN is pulled up to a 3.3-V to 5-V standby rail. This rail must be powered up independent of the eFuse 
ON/OFF status.
The secondary devices must be connected in the following manner:
1.
VDD is connected to IN through a R-C filter.
2.
MODE pin is connected to GND.
3.
ITIMER pin is left OPEN.
4.
ILIM is connected through resistor to GND.
The following pins of all devices must be connected together:
1.
IN
2.
OUT
3.
EN/UVLO
4.
DVDT
5.
SWEN
6.
PGOOD
7.
IMON
8.
IREF
9.
TEMP
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
118
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 119

In this configuration, all the devices are powered up and enabled simultaneously.
•
The TPS25990 monitors the combined VIN, VOUT, IMON, TEMP and reports it over the PMBus® telemetry 
interface.
•
The OVLO threshold is set to max value in all devices by default. For TPS25985x devices, the OV threshold 
is fixed in hardware and cannot be changed. The TPS25990 OV threshold can be lowered through PMBus® 
writes to the VIN_OV_FLT register. In this case, the TPS25990 uses the SWEN pin to turn off the TPS25985x 
devices during OV conditions.
•
The UVLO threshold for all devices is set by the external resistor divider from IN to GND on the EN/UVLO 
pin. The TPS25990 UV threshold can be changed through PMBus® writes to the VIN_UV_FLT register. In 
this case, the TPS25990 uses the SWEN pin to turn off the TPS25985x devices during UV conditions.
•
During inrush, the output of all the devices are ramped together based on the DVDT capacitor. 
However, the TPS25990 DVDT sourcing current can be configured through the PMBus® writes to the 
DEVICE_CONFIG[10:9] register to change the inrush behavior of the whole chain. The TPS25990 controls 
the DVDT ramp rate for the whole chain and secondary devices simply follow the ramp rate.
•
Due to the inherent difference in RDSON, the current carried by the TPS25990 is lower than the TPS25985x 
devices. Accordingly, the start-up current limit threshold and active current sharing threshold for the 
TPS25990 has to be set to a relatively lower value as compared to all the TPS25985x devices by connecting 
a proportionately higher ILIM resistor.
•
The TPS25990 controls the overall overcurrent threshold of the parallel chain by setting the VIREF threshold 
voltage using its internal DAC. The VIREF voltage can be programmed through PMBus® to change the 
overcurrent threshold.
•
The TPS25990 controls the transient overcurrent blanking interval (tOC_TIMER) for the whole system through 
PMBus® writes to the OC_TIMER register. Once the digital timer expires, the TPS25990 pulls the SWEN pin 
low to signal all devices to break the circuit simultaneously.
•
The system Power Good (PGOOD) indication is a combination of all the individual device PGOOD 
indications. All the devices hold their respective PGOOD pins low till their power FET is fully turned on. 
Once all devices have reached steady-state, they release their respective PGOOD pin pull-down and the 
PGOOD signal for the whole chain is asserted high. The TPS25985x secondary devices have control over 
the system PGOOD assertion only during startup. Once in steady state, only the TPS25990 controls the 
de-assertion of the PGOOD based on the VOUT_PGTH register setting.
•
The fault indication (FLT) for the whole system is provided by TPS25990. However, each secondary device 
also asserts its own FLT independently.
Power up: After power up or enable, all the eFuse devices initially hold their SWEN low till the internal blocks 
are biased and initialized correctly. After that, each device releases its own SWEN. After all devices have 
released their SWEN, the combined SWEN goes high and the devices are ready to turn on their respective FETs 
at the same time.
Inrush: During inrush, because the DVDT pins are tied together to a single DVDT capacitor all the devices turn 
on the output with the same slew rate (SR). Choose the common DVDT capacitor (CDVDT) as per Equation 21 
and Equation 22.
SR 
V
ms
=
IINRUSH  mA
COUT  µF
(21)
CdVdt  pF = 42000  ×  k
SR 
V
ms
(22)
Refer to Section 8.3.4.1 section for more details.
The internal balancing circuits ensure that the load current is shared among all devices during start-up. This 
action prevents a situation where some devices turn on faster than others and experience more thermal stress 
as compared to other devices. This can potentially result in premature or partial shutdown of the parallel chain, 
or even SOA damage to the devices. The current balancing scheme ensures the inrush capability of the chain 
scales according to the number of devices connected in parallel, thereby ensuring successful start-up with 
larger output capacitances or higher loading during start-up. All devices hold their respective PGOOD signals 
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
119
Product Folder Links: TPS25990



---

## Page 120

low during start-up. After the output ramps up fully and reaches steady-state, each device releases its own 
PGOOD pulldown. Because the DVDT pins of all devices are tied together, the internal gate high detection of 
all devices is synchronized. There can be some threshold or timing mismatches between devices leading to 
PGOOD assertion in a staggered manner. However, because the PGOOD pins of all devices are tied together, 
the combined PGOOD signal becomes high only after all devices have released their PGOOD pulldown. This 
signals the downstream load that it is okay to draw power.
Steady-state: During steady-state, all devices share current nearly equally using the active current sharing 
mechanism which actively regulates the respective device RDSON to evenly distribute current across all the 
devices in the parallel chain. Once PGOOD is asserted, de-assertion is controlled only by TPS25990 and based 
on VOUT_PGTH register setting.
Note
The TPS25985x current can be slightly higher as compared to TPS25990 higher owing to its lower on-
resistance. This must be fine as long as the steady-state current does not exceed the recommended 
maximum continuous rating for the device.
Overcurrent during steady-state: The circuit-breaker threshold for the parallel chain is based on the total 
system current rather than the current flowing through individual devices. This is done by connecting the IMON 
pins of all the devices together to a single resistor (RIMON) to GND. Similarly, the IREF pins of all devices are 
tied together and TPS25990 uses internal programmable DAC (VIREF) to generate a common reference for the 
overcurrent protection block in all the devices. This action helps minimize the contribution of VIREF variation to 
the overall mismatch in overcurrent threshold between devices.
In this case, choose the RIMON as per the following equation:
RIMON =
VIREF
GIMON × IOCP(TOTAL)
(23)
The start-up current limit and active current sharing threshold for each device is set independently using the ILIM 
pin. The RILIM value for the TPS25990 must be selected based on the following equation:
RILIM 25990   =
1.1  × 4N −1 × RIMON 
9 
(24)
The RILIM value for each TPS25985x must be selected based on the following equation:
RILIM 25985   =
1.1  × 4N −1 × RIMON 
12 
(25)
Where N = Number of devices in parallel chain (1 × TPS25990 + (N - 1) × TPS25985x)
Other variations: The IREF pin can be driven from an external precision voltage reference with low impedance.
During an overcurrent event, the overcurrent detection of all the devices is triggered simultaneously. This in turn 
triggers the overcurrent blanking timer (OC_TIMER) in TPS25990. The TPS25990 uses the OC_TIMER expiry 
event as a trigger to pull the SWEN low for all the devices, thereby initiating the circuit-breaker action for the 
whole chain at the same time. This mechanism ensures that mismatches in the current distribution, overcurrent 
thresholds and OC_TIMER intervals among the devices do not degrade the accuracy of the circuit-breaker 
threshold of the complete parallel chain or the overcurrent blanking interval. However, the secondary devices 
also maintain their backup overcurrent timer and can trigger the shutdown of the whole chain if the primary 
device fails to do so within a certain interval.
Severe overcurrent (short circuit): If there is a severe fault at the output (for example, output shorted to 
ground with a low impedance path), the current builds up rapidly to a high value and triggers the fast-trip 
response in each device. The devices use two thresholds for fast-trip protection – a user-adjustable threshold 
(ISFT = 2 × IOCP in steady-state or ISFT = 1.5 × ILIM during inrush) as well as a fixed threshold (IFFT only 
during steady-state). After the fast-trip, the TPS25990 relies on the SC_RETRY configuration bit setting in the 
DEVICE_CONFIG register to determine if the whole chain enters a latched fault or performs a fast recovery by 
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
120
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 121

restarting in current limit manner. If it enters a latched fault, the devices remain latched off till the device is power 
cycled or re-enabled, or auto-retry after a delay based on the RETRY_CONFIG register setting.
9.1.3 Multiple Devices, Independent Operation (Multi-zone)
Systems which need power from a common source to be distributed to different power zones can use multiple 
TPS25990 devices connected as shown in Figure 9-3 to provide independent monitoring and protection for each 
zone.
EN/UVLO
IN
IMON
VIN
VOUT1
TPS25990x
TEMP/CMP
ILIM
DVDT
IREF/DAC2
VDD
PG
PG1
SWEN
GND
OUT
FLT
FLT
FLT1
FLT1
EN
VLSTBY
VL
VL
SCL
SDA
SMBA#
VL
VL
VL
SCL
SDA
SMBA#
DAC1
EN/UVLO
IN
VOUT2
TPS25990x
TEMP/CMP
IREF/DAC2
VDD
PG
PG2
SWEN
OUT
FLT
FLT
FLT2
FLT2
VLSTBY
VL
VL
SCL
SDA
SMBA#
EN/UVLO
IN
VOUT3
TPS25990x
TEMP/CMP
IREF/DAC2
VDD
PG
PG3
SWEN
OUT
FLT
FLT
FLT3
FLT3
VLSTBY
VL
VL
SCL
SDA
SMBA#
ADDR1
ADDR0
IMON
ILIM
DVDT
GND
DAC1
ADDR1
ADDR0
IMON
ILIM
DVDT
GND
DAC1
ADDR1
ADDR0
Figure 9-3. Multiple TPS25990 Devices Delivering Power to Different Zones in a System
In this configuration, the following pins of each device are tied to the respective pins on the other devices.
1.
IN
2.
EN/UVLO
3.
SCL
4.
SDA
5.
SMBA#
Note
The EN/UVLO pins can be separated if each zone needs to have a different hardware control signal or 
UVLO threshold.
In this configuration, all the devices are monitored and controlled independently through the PMBus®. Because 
the devices share the same bus, they must have different device addresses, which can be set using different 
pin-strapping combinations on the ADDR0 and ADDR1 pins.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
121
Product Folder Links: TPS25990



---

## Page 122

9.2 Typical Application: 12-V, 4-kW Power Path Protection with PMBus® Interface in Datacenter 
Servers
This design example considers a 12 V system operating voltage with a tolerance of ±10%. The maximum 
steady-state load current is 333 A. If the load current exceeds 367 A, the eFuse circuit must allow transient 
overload currents up to a 10 ms interval. For persistent overloads lasting longer than that, the eFuse circuit must 
break the circuit and then latch-off. The eFuse circuit must charge a bulk capacitance of 50 mF and support 
approximately 7.5% of the steady-state load during start-up. Figure 9-4 shows the application schematic for this 
design example.
EN/UVLO
IN
OUT
IMON
ILIM
DVDT
ITIMER
VIN
VOUT
TEMP
IREF
VDD
PG
PG
TEMP
SWEN
GND
IMON
MODE
TPS25985x
FLT
FLT1
EN
FLTN
FLT2
EN/UVLO
IN
OUT
IMON
ILIM
DVDT
ITIMER
TEMP
IREF
VDD
PG
SWEN
GND
MODE
TPS25985x
FLT
EN/UVLO
IN
OUT
IMON
ILIM
DVDT
TEMP
IREF
VDD
PG
SWEN
GND
TPS25990x
FLT
10   
2.2 µF  
10 
   
2.2 µF  
10 
  
2.2 µF  
R1
R2
10 k  
VDD-PULLUP
10 k  
22 pF
eFuse - 1
eFuse - 2
eFuse - N
RILIM1
RILIM2
RILIMN
CDVDT
1 nF
22 pF
RIMON
0
  
0.1 µF
0.1 µF
0.1 µF
2.2 µF
2.2 µF
2.2 µF
1 nF
100 k  
VDD-PULLUP
VSWEN* 
(2.5 V 
to 5 V)
SMBA#
SDA
SCL
SCL
SDA
SMBA#
ADDR1
ADDR0
10 pF
AUX
AUX
*Power supply input to 
the eFuse(s) must be 
used to derive VSWEN.
Maximum Clamping Voltage VC 
specification of the selected TVS 
diode at Ipp (10/1000 s) (V) must 
be lower than the absolute 
maximum rating of the power
input (IN) pin for safe operation of 
the eFuse.
VDD-PULLUP should be less than 5V. 
VDD-PULLUP and VSWEN can be the same 
pullup supply if both are generated 
from the input (VIN) of the eFuse(s).
The non-repetitive peak 
forward surge current (IFSM) 
of the selected diode must 
be more than the fast-trip
threshold (2 × IOCP(TOTAL)). 
Two or more Schottky 
diodes in parallel must be 
used if a single Schottky
diode is unable to meet the 
required IFSM rating.
SCL
SMBA#
SDA
10 k  
VDD-µC
10 k	  
10 k
  
10 pF
N = 6 [One (1) TPS25990 eFuse 
+ Five (5) TPS25985 eFuses)
R1 = 1 M

R2 = 124 k

RIMON = 150 

RILIM1 = 422 

RILIM2 = 316 

RILIM3 = 316 

RILIM4 = 316 

RILIM5 = 316 

RILIM6 = 316 

CDVDT = 33 nF
VDD-PULLUP
10 k  
VDD-PULLUP
10 k

  
Figure 9-4. Application Schematic for a 12-V, 4-kW Power Path Protection Circuit with PMBus® Interface
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
122
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 123

9.2.1 Design Requirements
Table 9-1 shows the design parameters for this application example.
Table 9-1. Design Parameters
PARAMETER
VALUE
Input voltage range (VIN)
10.8 V – 13.2 V
Maximum DC load current (IOUT(max))
333 A
Maximum output capacitance (CLOAD)
50 mF
Are all the loads off until the PG is asserted?
No
Load at start-up (RLOAD(Startup))
0.48 Ω (equivalent to approximately 7.5% of the maximum steady-
state load)
Maximum ambient temperature
55°C
Transient overload blanking timer
10 ms
Output voltage slew rate
1.2 V/ms
Need to survive a “hot-short” on output condition?
Yes
Need to survive a “power up into short” condition?
Yes
Can the board be hotplugged in or power cycled?
Yes
Load current monitoring needed?
Yes
Need PMBus® interface
for telemetry, control, and configurability?
Yes
Fault response
Latch-off
9.2.2 Detailed Design Procedure
•
Determining the number of eFuse devices to be used in parallel
As the design must have PMBus® functionality or interface for telemetry, control, and configuration, the 
TPS25990 eFuse must be used as a primary device in parallel with TPS25985x eFuse(s) as secondary 
devices in order to support the required steady-state thermal design current. By factoring in a small variation 
in the junction to ambient thermal resistance (RθJA), each TPS25990 eFuse and TPS25985x eFuse is rated 
at maximum RMS currents of 50 A and 60 A respectively with a maximum junction temperature of 125 °C. 
Therefore, Equation 26 can be used to calculate the number of TPS25985x eFuses (N-1) to be in parallel 
with a TPS25990 eFuse to support the maximum steady state DC load current (ILOAD(max)), for which the 
solution must be designed.
N −1 ≥
IOUT max −50  
60
(26)
According to Table 9-1, IOUT(max) is 333 A. Therefore, one (1) TPS25990 and five (5) TPS25985x eFuses are 
connected in parallel to support the desired steady-state load current.
•
Setting up the primary and secondary devices in a parallel combination of TPS25990 and TPS25985x 
eFuses
The TPS25990 functions as a primary device by default. By connecting the MODE pin of all the TPS25985x 
eFuses to GND, they are configured as secondary devices.
•
Selecting the CDVDT capacitor to control the output slew rate and start-up time
For a robust design, the junction temperature of the device must be kept below the absolute maximum rating 
during both dynamic (start-up) and steady-state conditions. Typically, dynamic power stresses are orders of 
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
123
Product Folder Links: TPS25990



---

## Page 124

magnitude greater than static stresses, so it is crucial to establish the right start-up time and inrush current 
limit for the capacitance in the system and the associated loads to avoid thermal shutdown during start-up.
Table 9-2 summarizes the formulas for calculating the average inrush power loss on the eFuses in the 
presence of different loads during start-up if the power good (PG) signal is not used to turn on all the 
downstream loads.
Table 9-2. Calculation of Average Power Loss During Inrush
Type of Loads During Start-Up
Expressions to Calculate the Average Inrush Power Loss
Only output capacitor of CLOAD (µF)
VIN
2 CLOAD
2Tss
(27)
Output capacitor of CLOAD (µF) and constant resistance 
of RLOAD(Startup) (Ω) with turn-ON threshold of VRTH (V)
VIN
2 CLOAD
2Tss
+
VIN
2
RLOAD Startup
1
6 −
1
2
VRTH
VIN
2
+
1
3
VRTH
VIN
3
(28)
Output capacitor of CLOAD (µF) and constant current of 
ILOAD(Startup) (A) with turn-ON threshold of VCTH (V)
VIN
2 CLOAD
2Tss
+ VINILOAD Startup
1
2 −
VCTH
VIN
+
1
2
VCTH
VIN
2
(29)
Output capacitor of CLOAD (µF) and constant power of 
PLOAD(Startup) (W) with turn-ON threshold of VPTH (V)
VIN
2 CLOAD
2Tss
+ PLOAD Startup ln
VPTH
VIN
+
VPTH
VIN
−1
(30)
Where VIN is the input voltage and Tss is the start-up time.
With the different combinations of loads during start-up, the total average inrush power loss (PINRUSH) can be 
calculated using the formulas described in Table 9-2. For a successful start-up, the system must satisfy the 
condition stated in Equation 31.
PINRUSH W
Tss s < 8 + 12 N −1
(31)
Where N denotes the total number of eFuses in parallel and 8 W√s and 12 W√s are the safe operating 
area (SOA) limits of a TPS25990 eFuse and a TPS25985x eFuse respectively. This equation can be used to 
obtain the maximum allowed Tss.
Note
TI recommends to use a Tss in the range of 5 ms to 120 ms to prevent start-up issues.
A capacitor (CDVDT) must be added at the TPS25990 DVDT pin to GND to set the required value of Tss as 
calculated above. Equation 32 is used to compute the value of CDVDT. The DVDT pins of all the eFuses in a 
parallel chain must be connected together.
CDVDT pF =
42000 × k
VIN V /Tss ms
(32)
Refer to Section 8.3.4.1 section for more details. In this design example, CLOAD = 50 mF, RLOAD(Startup) = 0.48 
Ω, VRTH = 0 V, VIN = 12 V, and Tss = 10 ms. PINRUSH is calculated to be 410 W using the equations provided 
in the Table 9-2. It is verified that the system satisfies the condition stated in Equation 31 and therefore 
capable of having a successful start-up. If Equation 31 does not hold true, start-up loads or Tss must be 
tuned to prevent the chances of thermal shutdown during start-up. Using VIN = 12 V, Tss = 10 ms, k= 1, and 
Equation 32, the required CDVDT value can be calculated to be 35 nF. The closest standard value of CDVDT is 
33 nF with 10% tolerance and DC voltage rating of 25 V.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
124
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 125

Note
In some systems, there can be active load circuits (for example, DC-DC converters) with low turn-
on threshold voltages which can start drawing power before the eFuse has completed the inrush 
sequence. This action can cause additional power dissipation inside the eFuse during start-up and 
can lead to thermal shutdown. TI recommends using the Power Good (PG) pin of the eFuse to 
enable and disable the load circuit. This action ensures that the load is turned on only when the 
eFuse has completed its start-up and is ready to deliver full power without the risk of hitting thermal 
shutdown.
•
Selecting the VIREF to set the reference voltage for overcurrent protection and active current sharing
The reference voltage (VIREF) for overcurrent protection and active current sharing will be at 1 V by default. 
However, it can be programmed via PMBus® using the VIREF register if another reference voltage is needed 
in the range of 0.3 V to 1.2 V. When the voltage at the IMON pin (VIMON) is used as an input to an ADC to 
monitor the system current or to implement the Platform Power Control (Intel PSYS) functionality inside the 
VR controller, VIREF must be set to half of the maximum voltage range of the ISYS_IN input of the controller. 
This action provides the necessary headroom and dynamic range for the system to accurately monitor the 
load current up to the fast-trip threshold (2 × IOCP(TOTAL)). For improved noise immunity, place a 1 nF ceramic 
capacitor from the IREF pin to GND.
Note
Maintain VIREF within the recommended voltage to ensure proper operation of overcurrent 
detection circuit.
•
Selecting the RIMON resistor to set the overcurrent (circuit-breaker) and fast-trip thresholds during 
steady-state
TPS25990 eFuse responds to the output overcurrent conditions during steady-state by turning off the output 
after a user-adjustable transient fault blanking interval. This eFuse continuously senses the total system 
current (IOUT) and produces a proportional analog current output (IIMON) on the IMON pin. This generates a 
voltage (VIMON) across the IMON pin resistor (RIMON) in response to the load current, which is defined as 
Equation 33.
VIMON = IOUT × GIMON × RIMON
(33)
GIMON is the current monitor gain (IIMON : IOUT), whose typical value is 18.18 µA/A. The overcurrent condition 
is detected by comparing the VIMON against the VIREF as a threshold. The circuit-breaker threshold during 
steady-state (IOCP(TOTAL)) can be calculated using Equation 34.
IOCP TOTAL =
VIREF
GIMON × RIMON
(34)
In this design example, IOCP(TOTAL) is considered to be around 1.1 times IOUT(max). Hence, IOCP(TOTAL) is 
required to be set at 367 A, and RIMON can be calculated to be 150 Ω with GIMON as 18.18 µA/A and VIREF 
as 1 V. The value of RIMON is 150 Ω with 0.1% tolerance and power rating of 100 mW. This results in a 
circuit-breaker threshold of 367 A. For noise immunity, place a 22 pF ceramic capacitor from the IMON pin to 
GND.
Note
The total system output current (IOUT) must be considered when selecting RIMON, not the current 
carried by each individual device.
•
Selecting the RILIM resistor to set the current limit and fast-trip thresholds during start-up and the 
active sharing threshold during steady-state
RILIM is used in setting up the active current sharing threshold during steady-state and the overcurrent limit 
during startup among the devices in a parallel chain. Each device continuously monitors the current flowing 
through it (IDEVICE) and outputs a proportional analog output current on its own ILIM pin. This in turn produces 
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
125
Product Folder Links: TPS25990



---

## Page 126

a proportional voltage (VILIM) across the respective ILIM pin resistor (RILIM), which is expressed as Equation 
35.
VILIM = IDEVICE × GILIM × RILIM
(35)
GILIM is the current monitor gain (IILIM : IDEVICE), whose typical value is 18.18 μA/A.
–
Active current sharing during steady-state: This mechanism operates only after the device reaches 
steady-state and acts independently by comparing its own load current information (VILIM) with the Active 
Current Sharing reference (CLREFLIN) threshold, defined as Equation 36.
CLREFLIN =
1.1 × VIREF
3
(36)
The typical values of RDSON for TPS25990 and TPS25985x eFuses are 0.79 mΩ and 0.59 mΩ 
respectively. Therefore, when one (1) TPS25990 eFuse and one (1) TPS25985x eFuse are in parallel, 
it is expected that the TPS25990 eFuse will carry 0.75 times the current flowing through the TPS25985x 
eFuse in steady-state. Therefore, RLIM(TPS25990) must be calculated using Equation 37 to define the active 
current sharing threshold as 3×IOCP(TOTAL)/(4N-1) for TPS25990 eFuse, where N is the total number of 
devices in parallel (1 × TPS25990 + (N - 1) × TPS25985x). Whereas, Equation 38 needs to be followed 
to obtain the value of RLIM(TPS25985) in setting up the active current sharing threshold as 4×IOCP(TOTAL)/
(4N-1) for each TPS25985x eFuse. Using N = 6, RIMON = 150 Ω, and Equation 37, RILIM(TPS25990) can be 
calculated to be 421.6 Ω. The closest standard value of 422 Ω with 0.1% tolerance and power rating of 
100 mW resistance is selected as RILIM(TPS25990) for TPS25990 eFuse. Using Equation 38, RILIM(TPS25985) 
is obtained as 316.2 Ω.The closest standard value of 316 Ω with 0.1% tolerance and power rating of 100 
mW resistances are selected as RILIM(TPS25985) for five (5) TPS25985x eFuses.
RILIM TPS25990 =
1.1 × 4N −1 × RIMON
9
(37)
RILIM TPS25985 =
1.1 × 4N −1 × RIMON
12
(38)
Note
To determine the value of RILIM, Equation 39 must be used if a different threshold for active 
current sharing (ILIM(ACS)) is desired.
RILIM =
1.1 × VIREF
3 × GILIM × ILIM ACS
(39)
When computing the current limit threshold during start-up in the next sub-section, ensure to 
use this RILIM value.
–
Overcurrent limit during start-up: During inrush, the overcurrent condition for each device is detected 
by comparing its own load current information (VILIM) with a scaled reference voltage as depicted in 
Equation 40.
CLREFSAT =
0.7 × VIREF
3
(40)
The current limit threshold during start-up can be calculated using Equation 41.
IILIM Startup =
CLREFSAT
GILIM × RILIM
(41)
By using a RILIM(TPS25990) value of 422 Ω, the start-up current is limited to 30 A for TPS25990 with 
VIREF of 1 V. Whereas, the start-up current is limited to 40 A for TPS25985x with VIREF of 1 V using 
a RILIM(TPS25985) value of 316 Ω. Hence, the total start-up current limit becomes ~230 A for this design 
example.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
126
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 127

Note
The active current limit block employs a foldback mechanism during start-up based on VOUT. 
When VOUT is below the foldback threshold (VFB) of 2 V, the current limit threshold is further 
lowered.
•
Selecting the overcurrent blanking timer duration (tOC_TIMER)
The overcurrent blanking timer duration (tOC_TIMER) for the entire parallel chain is controlled by TPS25990 
and is set to 2.18 ms by default. However, it can be programmed via PMBus® using the OC_TIMER (E6h) 
register to a different value in the range of 0 ms to 27.8 ms in 100 μs steps. The ITIMER pin for all the 
secondary TPS25985x devices must be left open.
•
Selecting the resistors to set the undervoltage lockout threshold
The undervoltage lockout (UVLO) threshold is adjusted by employing the external voltage divider network 
of R1 and R2 connected between IN, EN/UVLO, and GND pins of the device as described in Undervoltage 
protection section. The resistor values required for setting up the UVLO threshold are calculated using 
Equation 42.
VIN UV = VUVLO R
R1 + R2
R2
(42)
To minimize the input current drawn from the power supply, TI recommends using higher resistance values 
for R1 and R2. The current drawn by R1 and R2 from the power supply is IR12 = VIN / (R1 + R2). However, 
the leakage currents due to external active components connected to the resistor string can add errors to 
these calculations. So, the resistor string current, IR12 must be 20 times greater than the leakage current at 
the EN/UVLO pin (IENLKG). From the device electrical specifications, IENLKG is 0.1 µA (maximum) and UVLO 
rising threshold VUVLO(R) = 1.2 V. From the design requirements, VINUVLO = 10.8 V. First choose the value of 
R1 = 1 MΩ and use Equation 13 to calculate R2 = 125 kΩ. Use the closest standard 1% resistor values: R1 
= 1 MΩ and R2 = 124 kΩ. For noise reduction, place a 1 nF ceramic capacitor across the EN/UVLO pin and 
GND.
•
Selecting the R-C filter between VIN and VDD for TPS25990 and TPS25985x
VDD pin is intended to power the internal control circuitry of the eFuse with a filtered and stable supply, not 
affected by system transients. Therefore, use an R (10 Ω) – C (2.2 µF) filter from the input supply (IN pin) to 
the VDD pin. This helps to filter out the supply noises and to hold up the controller supply during severe faults 
such as short-circuit at the output. In a parallel chain, this R-C filter must be employed for each device.
•
Selecting the pullup resistors and power supplies for SWEN, PG and FLT pins
FLT, PG, and CMPOUT are open drain outputs. If these logic signals are used, the corresponding pins must 
be pulled up to the appropriate voltages (< 5 V) through 10 kΩ pull-up resistances.
Note
–
SWEN pin must be pulled up to a voltage in the range of 2.5 V to 5 V through a 100-kΩ 
resistance. This pullup power supply must be generated from the input to the eFuse and 
available before the eFuse is enabled as discussed in Section 9.3, without which the eFuse 
does not start up.
–
There can be some threshold or timing mismatches between devices leading to PG assertion 
in a staggered manner. Therefore, it is advisable to connect the PG pins of all the devices in 
parallel. This will ensure that the combined PG signal becomes high only after all devices have 
released their PG pulldowns.
•
Selecting the pullup resistors for PMBus® SCL, SDA, and SMBA# lines
The SCL, SDA, and SMBA# lines can be pulled up to potentials less than 5 V in general with pull-up resistors 
of 10 kΩ. However, to obtain the appropriate values of these pull-up resistors in accordance with the system 
specifications, please refer to I2C Bus Pullup Resistor Calculation.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
127
Product Folder Links: TPS25990



---

## Page 128

•
Configuring the PMBus® target device address
Place appropriate resistors across ADDR0 and ADDR1 to GND or leave these pins floating or connect them 
to GND as described in Section 8.3.14.1 to set the preferred device address. To improve the noise immunity 
for correct address decoding, connect 10 pF ceramic capacitors in parallel with the resistors on ADDR0 and 
ADDR1.
•
Selection of TVS diode at input and Schottky diode at output
In the case of a short circuit and overload current limit when the device interrupts a large amount of current 
instantaneously, the input inductance generates a positive voltage spike on the input, whereas the output 
inductance creates a negative voltage spike on the output. The peak amplitudes of these voltage spikes 
(transients) are dependent on the value of inductance in series with the input or output of the device. Such 
transients can exceed the absolute maximum ratings of the device and eventually lead to failures due to 
electrical overstress (EOS) if appropriate steps are not taken to address this issue. Typical methods for 
addressing this issue include:
1.
Minimize lead length and inductance into and out of the device.
2.
Use a large PCB GND plane.
3.
Addition of the Transient Voltage Suppressor (TVS) diodes to clamp the positive transient spike at the 
input.
4.
Using Schottky diodes across the output to absorb negative spikes.
Refer to TVS Clamping in Hot-Swap Circuits and Selecting TVS Diodes in Hot-Swap and ORing Applications 
for details on selecting an appropriate TVS diode and the number of TVS diodes to be in parallel to effectively 
clamp the positive transients at the input below the absolute maximum ratings of the IN pin (20 V). These 
TVS diodes also help to limit the transient voltage at the IN pin during the Hot Plug event. Four (4) SMDJ12A 
are used in parallel in this design example.
Note
Maximum Clamping Voltage VC specification of the selected TVS diode at Ipp (10/1000 μs) (V) 
must be lower than the absolute maximum rating of the power input (IN) pin for safe operation of 
the eFuse.
Selection of the Schottky diodes must be based on the following criteria:
–
The non-repetitive peak forward surge current (IFSM) of the selected diode must be more than the fast-trip 
threshold (2 × IOCP(TOTAL)). Two or more Schottky diodes in parallel must be used if a single Schottky 
diode is unable to meet the required IFSM rating. Equation 43 calculates the number of Schottky diodes 
(NSchottky) that must be used in parallel.
NScℎottky >
2 × IOCP TOTAL
IFSM
(43)
–
Forward Voltage Drop (VF) at near to IFSM must be as small as possible. Ideally, the negative transient 
voltage at the OUT pin must be clamped within the absolute maximum rating of the OUT pin (–1 V).
–
DC Blocking Voltage (VRM) must be more than the maximum input operating voltage.
–
Leakage current (IR) must be as small as possible.
Three (3) SBR10U45SP5 are used in parallel in this design example.
•
Selecting CIN and COUT
TI recommends to add ceramic bypass capacitors to help stabilize the voltages on the input and output. The 
value of CIN must be kept small to minimize the current spike during hot-plug events. For each device, 0.1 µF 
of CIN is a reasonable target. Because COUT does not get charged during hot-plug, a larger value such as 2.2 
µF can be used at the OUT pin of each device.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
128
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 129

9.2.3 Application Performance Plots
All the waveforms below are captured on an evaluation setup with one (1) TPS25990 eFuse and five (5) 
TPS25985x eFuses in parallel. All the pullup supplies are derived from a separate standby rail.
DVDT
VOUT
VIN
Input Current
Figure 9-5. Input Hot Plug: VIN Stepped Up from 0 
V to 12 V, CLOAD = 50 mF, RLOAD(Start-up) = 0.48 Ω, 
CDVDT = 33 nF, VIREF = 1 V, RILIM(TPS25990) = 422 Ω, 
and RILIM(TPS25985) = 316 Ω
Figure 9-6. Start-up with EN/UVLO: VIN = 12 V, EN/
UVLO Stepped Up From 0 V to 3 V, CLOAD = 50 mF, 
RLOAD(Start-up) = 0.48 Ω, CDVDT = 33 nF, VIREF = 1 V, 
RILIM(TPS25990) = 422 Ω, and RILIM(TPS25985) = 316 Ω
Figure 9-7. Power Up into Short: VIN = 12 V, EN/
UVLO Stepped Up From 0 V to 3 V, VIREF = 1 V, 
RILIM(TPS25990) = 422 Ω, RILIM(TPS25985) = 316 Ω, and 
OUT Shorted to GND
Figure 9-8. Power Up into Short (Current 
distribution among six devices in parallel): VIN = 
12 V, EN/UVLO Stepped Up From 0 V to 3 V, VIREF 
= 1 V, RILIM(TPS25990) = 422 Ω, RILIM(TPS25985) = 316 Ω, 
and OUT Shorted to GND
Figure 9-9. Transient Overload: VIN = 12 V, tOC_TIMER 
= 10 ms, CLOAD = 50 mF, RIMON = 150 Ω, VIREF = 1 
V, and Load Current Stepped from 333 A to 500 A 
then 333 A within 8.5 ms
Figure 9-10. Transient Overload (Current 
distribution among six devices in parallel): VIN = 
12 V, tOC_TIMER = 10 ms, CLOAD = 50 mF, RIMON = 150 
Ω, VIREF = 1 V, and Load Current Stepped from 333 
A to 500 A then 333 A within 8.5 ms
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
129
Product Folder Links: TPS25990



---

## Page 130

Figure 9-11. Circuit-Breaker Response: VIN = 12 V, 
tOC_TIMER = 10 ms, CLOAD = 50 mF, RIMON = 150 Ω, 
VIREF = 1 V, and Load Current Stepped from 333 A 
to 530 A for more than 10 ms
Figure 9-12. Circuit-Breaker Response (Current 
distribution among six devices in parallel): VIN = 
12 V, tOC_TIMER = 17 ms, CLOAD = 50 mF, RIMON = 150 
Ω, VIREF = 1 V, and Load Current Stepped from 333 
A to 530 A for more than 17 ms
Figure 9-13. Output Hot-Short Response: VIN = 12 
V, RIMON = 150 Ω, VIREF = 1 V, and OUT Shorted to 
GND
Figure 9-14. One (1) TPS25990 eFuse and one (1) 
TPS25985x eFuse in Parallel: Temperature Rise 
with 110-A DC Current at Room Temperature (No 
Air-Flow)
9.3 Best Design Practices
TPS25990 needs the SWEN pin to be pulled up to a supply rail which is powered up before the device is 
enabled. Failing this, the device is not able to turn on the output. The SWEN pullup supply must not be derived 
from the output of the eFuse. Use one of the following options to derive the pullup supply rail for SWEN.
1.
Use an existing standby rail in the system, which is derived from the main power input and comes up before 
the eFuse is turned on.
2.
Use an LDO (3.3 V or 5 V) powered from the main power input.
IN
eFuse Input 
Supply
GND
OUT
VSWEN
100 k  
SWEN  
LDO
0.1 µF
0.1 µF
Figure 9-15. LDO Used as Pullup Supply for SWEN
3.
Use a Zener regular powered from the main power input.
eFuse Input 
Supply
SWEN  
100 k
  
100 k   
0.1 µF
4.7 V Zener 
Diode
Figure 9-16. Zener Regulator Used as Pullup Supply for SWEN
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
130
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 131

4.
Use the ITIMER pin of one of the secondary eFuses (TPS25985x). Ensure the ITIMER pin does not have 
excess loading which can interfere with the normal overcurrent blanking timer functionality.
ITIMER of secondary 
TPS25985 eFuse
100 k
  
SWEN  
Figure 9-17. ITIMER Pin Used as Pullup Supply for SWEN
The ground connections for the various components around the TPS25990 & TPS25985 must be wired directly 
to each other and the GND pins of respective eFuses. This must be followed by connecting them to the system 
ground at one point. For more details, refer to TPS25990EVM eFuse Evaluation Board. Do not connect the 
various component grounds through the high current system ground line.
9.4 Power Supply Recommendations
The TPS25990 devices are designed for a supply voltage in the range of 2.9 V to 16 V on the IN pin and 4.5 V 
to 16 V on the VDD pin. TI recommends using a minimum capacitance of 0.1 μF on the IN pin of each device in 
parallel chain to avoid coupling of high slew rates during hot plug events. TI also recommends using an R-C filter 
from the IN supply to the VDD pin to filter out supply noise and to hold up the controller supply during severe 
faults such as short-circuit.
Note
1.
If in-system programming of configuration register non-volatile memory is needed, then TI 
recommends using a minimum supply of 10 V on VDD.
2.
The device can be used with VIN voltage rails down to 2.9 V as long as the VDD rail is supplied 
with an independent bias voltage of 4.5 V or higher.
9.4.1 Transient Protection
In the case of a short-circuit or circuit-breaker event, when the device interrupts current flow, the input 
inductance generates a positive voltage spike on the input, and the output inductance generates a negative 
voltage spike on the output. The peak amplitude of voltage spikes (transients) is dependent on the value of 
inductance in series to the input or output of the device. Such transients can exceed the absolute maximum 
ratings of the device if steps are not taken to address the issue. Typical methods for addressing transients 
include:
•
Minimize lead length and inductance into and out of the device.
•
Use a large PCB GND plane.
•
Connect a Schottky diode from the OUT pin ground to absorb negative spikes.
•
Connect a low ESR capacitor of 2.2 μF or higher at the OUT pin very close to the device.
•
Connect a ceramic capacitor CIN = 0.1 μF or higher at the IN pin very close to the device to dampen the rise 
time of input transients. The capacitor voltage rating must be at least twice the input supply voltage to be able 
to withstand the positive voltage excursion during inductive ringing.
The approximate value of input capacitance can be estimated with Equation 44.
VSPIKE Absolute = VIN + ILOAD ×
LIN
CIN
(44)
VIN is the nominal supply voltage.
ILOAD is the load current.
LIN equals the effective inductance seen looking into the source.
CIN is the capacitance present at the input.
•
Some applications can require the addition of a Transient Voltage Suppressor (TVS) to prevent transients 
from exceeding the absolute maximum ratings of the device. In some cases, even if the maximum amplitude 
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
131
Product Folder Links: TPS25990



---

## Page 132

of the transients is below the absolute maximum rating of the device, a TVS can help to absorb the excessive 
energy dump and prevent it from creating very fast transient voltages on the input supply pin of the IC, which 
can couple to the internal control circuits and cause unexpected behavior.
The circuit implementation with optional protection components is shown in Figure 9-18.
EN/UVLO
IN
IMON
VIN
VOUT
TPS25990x
TEMP/CMP
ILIM
DVDT
IREF/DAC2
VDD
PG
PG
SWEN
GND
IMON
OUT
FLT
FLT
FLT
FLT
EN
VLSTBY
VL
VL
ADDR1
AUX
SCL
SDA
SMBA#
ADDR0
VL
VL
VL
SCL
SDA
SMBA#
DAC1
*
*
*
Figure 9-18. Circuit Implementation with Optional Protection Components
9.4.2 Output Short-Circuit Measurements
It is difficult to obtain repeatable and similar short-circuit testing results. The following contribute to variation in 
results:
•
Source bypassing
•
Input leads
•
Circuit layout
•
Component selection
•
Output shorting method
•
Relative location of the short
•
Instrumentation
The actual short exhibits a certain degree of randomness because it microscopically bounces and arcs. Ensure 
that configuration and methods are used to obtain realistic results. Do not expect to see waveforms exactly like 
those in this data sheet because every setup is different.
9.5 Layout
9.5.1 Layout Guidelines
•
For all applications, TI recommends a ceramic decoupling capacitor of 0.1 μF or greater between the IN 
terminal and GND terminal.
•
For all applications, TI recommends a ceramic decoupling capacitor of 2.2 μF or greater between the OUT 
terminal and GND terminal.
•
The optimal placement of the decoupling capacitor is closest to the IN and GND terminals of the device. Care 
must be taken to minimize the loop area formed by the bypass-capacitor connection, the IN terminal, and the 
GND terminal of the IC. See Figure below for a PCB layout example.
•
High current-carrying power-path connections must be as short as possible and must be sized to carry at 
least twice the full-load current.
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
132
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 133

•
The GND terminal must be tied to the PCB ground plane at the terminal of the IC. The PCB ground must be a 
copper plane or island on the board.
•
The IN and OUT pins are used for Heat Dissipation. Connect to as much copper area as possible with 
thermal vias.
•
Locate the following support components close to their connection pins:
–
CIN
–
COUT
–
CVDD
–
CTEMP
–
RILIM
–
RIMON
–
CIREF
–
CDVDT
–
Resistors for the EN/UVLO pin
–
Resistors for the ADDR0, ADDR1 pins
•
Connect the other end of the component to the GND pin of the device with shortest trace length. The trace 
routing for the ADDR0, ADDR1, CIN, COUT, CVDD, CIREF, RILIM, RIMON, CTEMP and CDVDT components to the 
device must be as short as possible to reduce parasitic effects on the current limit and soft-start timing. These 
traces must not have any coupling to switching signals on the board.
•
Because the IMON, ILIM and IREF pins directly control the overcurrent protection behavior of the device, the 
PCB routing of these nodes must be kept away from any noisy (switching) signals.
•
TI recommends to keep the parasitic loading on SWEN pin to a minimum to avoid synchronization issues.
•
Protection devices such as TVS, snubbers, capacitors, or diodes must be placed physically close to the 
device they are intended to protect. These protection devices must be routed with short traces to reduce 
inductance. For example, TI recommends a protection Schottky diode to address negative transients due to 
switching of inductive loads, and it must be physically close to the OUT pins.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
133
Product Folder Links: TPS25990



---

## Page 134

9.5.2 Layout Example
Top Signal GND layer
Bottom Power layer
Top Power layer
+
-
VIN
VOUT
Top Power GND layer
TPS25990
TPS25985
Figure 9-19. TPS25990 and TPS25985x Parallel Devices Layout Example
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
www.ti.com
134
Submit Document Feedback
Copyright © 2023 Texas Instruments Incorporated
Product Folder Links: TPS25990



---

## Page 135

10 Device and Documentation Support
TI offers an extensive line of development tools. Tools and software to evaluate the performance of the device, 
generate code, and develop solutions are listed below.
10.1 Documentation Support
10.1.1 Related Documentation
For related documentation see the following:
•
Texas Instruments, TPS25990EVM eFuse Evaluation Board
•
Texas Instruments, TPS25990x Design Calculator
10.2 Receiving Notification of Documentation Updates
To receive notification of documentation updates, navigate to the device product folder on ti.com. Click on 
Subscribe to updates to register and receive a weekly digest of any product information that has changed. For 
change details, review the revision history included in any revised document.
10.3 Support Resources
TI E2E™ support forums are an engineer's go-to source for fast, verified answers and design help — straight 
from the experts. Search existing answers or ask your own question to get the quick design help you need.
Linked content is provided "AS IS" by the respective contributors. They do not constitute TI specifications and do 
not necessarily reflect TI's views; see TI's Terms of Use.
10.4 Trademarks
SMBus™ is a trademark of Intel.
TI E2E™ is a trademark of Texas Instruments.
PMBus® is a registered trademark of SMIF.
Intel® is a registered trademark of Intel.
All trademarks are the property of their respective owners.
10.5 Electrostatic Discharge Caution
This integrated circuit can be damaged by ESD. Texas Instruments recommends that all integrated circuits be handled 
with appropriate precautions. Failure to observe proper handling and installation procedures can cause damage.
ESD damage can range from subtle performance degradation to complete device failure. Precision integrated circuits may 
be more susceptible to damage because very small parametric changes could cause the device not to meet its published 
specifications.
10.6 Glossary
TI Glossary 
This glossary lists and explains terms, acronyms, and definitions.
11 Mechanical, Packaging, and Orderable Information
The following pages include mechanical, packaging, and orderable information. This information is the most 
current data available for the designated devices. This data is subject to change without notice and revision of 
this document. For browser-based versions of this data sheet, refer to the left-hand navigation.
www.ti.com
TPS25990
SLVSGG4B – SEPTEMBER 2022 – REVISED JUNE 2023
Copyright © 2023 Texas Instruments Incorporated
Submit Document Feedback
135
Product Folder Links: TPS25990



---

## Page 136

PACKAGE OPTION ADDENDUM
www.ti.com
9-Nov-2025
PACKAGING INFORMATION
Orderable part number
Status
(1)
Material type
(2)
Package | Pins
Package qty | Carrier
RoHS
(3)
Lead finish/
Ball material
(4)
MSL rating/
Peak reflow
(5)
Op temp (°C)
Part marking
(6)
TPS25990ARQPR
Active
Production
VQFN-HR (RQP) | 26
3000 | LARGE T&R
Yes
SN
Level-2-260C-1 YEAR
-40 to 125
T25990
Z2
TPS25990ARQPR.A
Active
Production
VQFN-HR (RQP) | 26
3000 | LARGE T&R
Yes
SN
Level-2-260C-1 YEAR
-40 to 125
T25990
Z2
 
(1) Status:  For more details on status, see our product life cycle.
 
(2) Material type:  When designated, preproduction parts are prototypes/experimental devices, and are not yet approved or released for full production. Testing and final process, including without limitation quality assurance,
reliability performance testing, and/or process qualification, may not yet be complete, and this item is subject to further changes or possible discontinuation. If available for ordering, purchases will be subject to an additional
waiver at checkout, and are intended for early internal evaluation purposes only. These items are sold without warranties of any kind.
 
(3) RoHS values:  Yes, No, RoHS Exempt. See the TI RoHS Statement for additional information and value definition.
 
(4) Lead finish/Ball material:  Parts may have multiple material finish options. Finish options are separated by a vertical ruled line. Lead finish/Ball material values may wrap to two lines if the finish value exceeds the maximum
column width.
 
(5) MSL rating/Peak reflow:  The moisture sensitivity level ratings and peak solder (reflow) temperatures. In the event that a part has multiple moisture sensitivity ratings, only the lowest level per JEDEC standards is shown.
Refer to the shipping label for the actual reflow temperature that will be used to mount the part to the printed circuit board.
 
(6) Part marking:  There may be an additional marking, which relates to the logo, the lot trace code information, or the environmental category of the part.
 
Multiple part markings will be inside parentheses. Only one part marking contained in parentheses and separated by a "~" will appear on a part. If a line is indented then it is a continuation of the previous line and the two
combined represent the entire part marking for that device.
 
Important Information and Disclaimer:The information provided on this page represents TI's knowledge and belief as of the date that it is provided. TI bases its knowledge and belief on information provided by third parties, and
makes no representation or warranty as to the accuracy of such information. Efforts are underway to better integrate information from third parties. TI has taken and continues to take reasonable steps to provide representative
and accurate information but may not have conducted destructive testing or chemical analysis on incoming materials and chemicals. TI and TI suppliers consider certain information to be proprietary, and thus CAS numbers
and other limited information may not be available for release.
 
In no event shall TI's liability arising out of such information exceed the total purchase price of the TI part(s) at issue in this document sold by TI to Customer on an annual basis.
 
Addendum-Page 1



---

## Page 137

PACKAGE MATERIALS INFORMATION
 
 
www.ti.com
7-Dec-2023
TAPE AND REEL INFORMATION
Reel Width (W1)
REEL DIMENSIONS
A0
B0
K0
W
Dimension designed to accommodate the component length
Dimension designed to accommodate the component thickness
Overall width of the carrier tape
Pitch between successive cavity centers
Dimension designed to accommodate the component width
TAPE DIMENSIONS
K0
 P1
B0 W
A0
Cavity
QUADRANT ASSIGNMENTS FOR PIN 1 ORIENTATION IN TAPE
Pocket Quadrants
Sprocket Holes
Q1
Q1
Q2
Q2
Q3
Q3
Q4
Q4
User Direction of Feed
P1
Reel
Diameter
 
*All dimensions are nominal
Device
Package
Type
Package
Drawing
Pins
SPQ
Reel
Diameter
(mm)
Reel
Width
W1 (mm)
A0
(mm)
B0
(mm)
K0
(mm)
P1
(mm)
W
(mm)
Pin1
Quadrant
TPS25990ARQPR
VQFN-
HR
RQP
26
3000
330.0
12.4
4.8
5.3
1.15
8.0
12.0
Q2
Pack Materials-Page 1



---

## Page 138

PACKAGE MATERIALS INFORMATION
 
 
www.ti.com
7-Dec-2023
TAPE AND REEL BOX DIMENSIONS
Width (mm)
W
L
H
 
*All dimensions are nominal
Device
Package Type
Package Drawing
Pins
SPQ
Length (mm)
Width (mm)
Height (mm)
TPS25990ARQPR
VQFN-HR
RQP
26
3000
360.0
360.0
36.0
Pack Materials-Page 2



---

## Page 139

NOTES:
1.
All linear dimensions are in millimeters. Any dimensions in parenthesis are for reference only. Dimensioning and tolerancing
per ASME Y14.5M.
2.
This drawing is subject to change without notice.
PACKAGE OUTLINE
4225325/B   10/2020
www.ti.com
VQFN-HR - 1 mm max height
PLASTIC QUAD FLATPACK-NO LEAD
RQP0026A
A
0.08 C
0.1
C A B
0.05
C
B
0.0 PKG 
0.0 PKG 
5.1
4.9
4.6
4.4
PIN 1 IDENTIFICATION
1.0
0.8
0.05
0.00
SEATING PLANE
C
8X 2.55
2.35
4X 0.45
0.35
4X TYP (0.15)
4X TYP (0.35)
4X 0.4
0.3
0.1
C A B
0.05
C
14X 0.25
0.15
0.1
C A B
0.05
C
8X 0.3
0.2
18X 0.6
0.4
4X 0.85
0.65
4X 1.7
4X 1.2
4X 0.8
4X 0.4
1.5825
0.6775
1.1325
0.2275
0.2275
1.1325
0.6775
1.5825
4X 2.175
TYP (0.1)
PIN1 ID
(OPTIONAL)
1
9
10
14
22
23
26
13



---

## Page 140

EXAMPLE BOARD LAYOUT
4225325/B   10/2020
www.ti.com
VQFN-HR - 1 mm max height
RQP0026A
PLASTIC QUAD FLATPACK-NO LEAD
(0.0)
PKG 
(0.0)
 PKG 
LAND PATTERN EXAMPLE
EXPOSED METAL SHOWN
SCALE: 15X
NON- SOLDER MASK
DEFINED
(PREFERRED)
SOLDER MASK
DEFINED
SOLDER MASK DETAILS
NOT TO SCALE
EXPOSED METAL
METAL
SOLDER MASK
OPENING
0.05 MAX
ALL AROUND
0.05 MIN
ALL AROUND
SOLDER MASK
OPENING
METAL UNDER
SOLDER MASK
EXPOSED METAL
4X (0.4)
4X (0.35)
14X (0.2)
18X (0.7)
8X (0.25)
4X (0.95)
8X
(2.65)
(1.1325)
(0.2275)
(0.6775)
(1.5825)
(2.175)
4X (1.7)
4X (1.2)
4X (0.8)
4X (0.4)
(1.125)
(1.975)
(2.35)
(1.5825)
(0.6775)
(0.2275)
(1.1325)
(1.975)
(2.35)
(2.175)
(1.125)
1
9
10
13
14
22
23
26
(R0.05) TYP
NOTES: (continued)
3.
For more information, see Texas Instruments literature number SLUA271 (www.ti.com/lit/slua271).
4.
Solder mask tolerances between and around signal pads can vary based on board fabrication site.



---

## Page 141

EXAMPLE STENCIL DESIGN
4225325/B   10/2020
www.ti.com
VQFN-HR - 1 mm max height
RQP0026A
PLASTIC QUAD FLATPACK-NO LEAD
SOLDER PASTE EXAMPLE
BASED ON 0.1mm THICK STENCIL
PIN 1,9,14 & 22: 96%; PIN 10-13 & 23-26: 77%
SCALE: 15X
(0.0)
PKG 
(0.0)
PKG 
4X (0.35)
4X (0.35)
14X (0.2)
18X (0.7)
16X (0.21)
4X (0.95)
16X
(1.225)
(1.1325)
(0.2275)
(0.6775)
(1.5825)
(2.175)
4X (1.675)
4X (1.2)
4X (0.8)
4X (0.4)
(1.975)
(2.35)
(1.5825)
(0.6775)
(0.2275)
(1.1325)
(1.975)
(2.35)
(2.175)
1
9
10
13
14
22
23
26
(R0.05) TYP
2X (0.4)
2X (1.8)
METAL TYP
NOTES: (continued)
5. 
Laser cutting apertures with trapezoidal walls and rounded corners may offer better paste release. IPC-7525 may have alternate 
design recommendations.
(0.2)



---

## Page 142

IMPORTANT NOTICE AND DISCLAIMER
TI PROVIDES TECHNICAL AND RELIABILITY DATA (INCLUDING DATASHEETS), DESIGN RESOURCES (INCLUDING REFERENCE 
DESIGNS), APPLICATION OR OTHER DESIGN ADVICE, WEB TOOLS, SAFETY INFORMATION, AND OTHER RESOURCES “AS IS” 
AND WITH ALL FAULTS, AND DISCLAIMS ALL WARRANTIES, EXPRESS AND IMPLIED, INCLUDING WITHOUT LIMITATION ANY 
IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT OF THIRD 
PARTY INTELLECTUAL PROPERTY RIGHTS.
These resources are intended for skilled developers designing with TI products. You are solely responsible for (1) selecting the appropriate 
TI products for your application, (2) designing, validating and testing your application, and (3) ensuring your application meets applicable 
standards, and any other safety, security, regulatory or other requirements.
These resources are subject to change without notice. TI grants you permission to use these resources only for development of an 
application that uses the TI products described in the resource. Other reproduction and display of these resources is prohibited. No license 
is granted to any other TI intellectual property right or to any third party intellectual property right. TI disclaims responsibility for, and you fully 
indemnify TI and its representatives against any claims, damages, costs, losses, and liabilities arising out of your use of these resources.
TI’s products are provided subject to TI’s Terms of Sale, TI’s General Quality Guidelines, or other applicable terms available either on 
ti.com or provided in conjunction with such TI products. TI’s provision of these resources does not expand or otherwise alter TI’s applicable 
warranties or warranty disclaimers for TI products. Unless TI explicitly designates a product as custom or customer-specified, TI products 
are standard, catalog, general purpose devices.
TI objects to and rejects any additional or different terms you may propose.
IMPORTANT NOTICE
Copyright © 2025, Texas Instruments Incorporated
Last updated 10/2025
