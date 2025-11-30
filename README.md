# Kalem-RS485-5V-Basic

Non-isolated 5 V RS-485 transceiver module based on **MAX485**.  
Designed for easy connection between microcontrollers and RS-485 networks in industrial and hobby projects.

---

## Features

- Supply voltage: **5 V** (typ. 4.75–5.25 V)
- MAX485 half-duplex RS-485 transceiver
- **Non-isolated** module
- On-board **120 Ω termination** resistor (selectable by jumper)
- On-board **failsafe bias** network  
  – 680 Ω pull-up on A, 680 Ω pull-down on B  
- **SM712** TVS diode pair on A/B for surge and ESD protection  
- Local decoupling: **100 nF + 10 µF** on VCC  
- 2.54 mm pin header on MCU side, screw terminal on bus side
- Compact PCB: **32.766 × 12.700 mm**, 25.4 mm between pin rows (breadboard compatible)

---

## Pinout

### MCU side header

| Pin | Name | Direction | Description                                  |
|-----|------|-----------|----------------------------------------------|
| 1   | RO   | Out       | Receiver output (to MCU RX)                  |
| 2   | RE   | In        | Receiver enable, active LOW (*tied to DE*)   |
| 3   | DE   | In        | Driver enable, active HIGH (*tied to RE*)    |
| 4   | DI   | In        | Driver input (from MCU TX)                   |

> On this module **DE and /RE are connected together** and routed as a single
> direction signal (**DIR**).  
> - `DIR = 0` → receive mode (driver OFF, receiver ON)  
> - `DIR = 1` → transmit mode (driver ON, receiver OFF)

If separate control of DE and /RE is needed, the solder bridge between them
can be cut and wired individually.

### RS-485 bus screw terminal + headers

| Pin | Name | Description                          |
|-----|------|--------------------------------------|
| 1   | 5V   | Module supply voltage (5 V)         |
| 2   | B    | RS-485 B (–) line                    |
| 3   | A    | RS-485 A (+) line                    |
| 4   | GND  | Ground / reference                   |

---

## Typical connection

**MCU ↔ Kalem-RS485-5V-Basic:**

- MCU TX → `DI`  
- MCU RX ← `RO`  
- MCU GPIO (direction) → `DE/RE` (DIR)  
- MCU 5 V → `5V`  
- MCU GND → `GND`

**Bus side:**

- `A` and `B` go to the RS-485 twisted pair.
- Use 120 Ω termination only at **both ends** of the bus.  
  The onboard 120 Ω resistor can be enabled with the jumper when the module is at one end.

---

## Direction control

In firmware:

1. Set DIR pin **LOW** to listen (receive mode).
2. Before sending data:
   - Set DIR pin **HIGH**.
   - Send UART bytes.
   - Wait until transmission complete.
3. Set DIR pin **LOW** again to release the bus and receive.

---

