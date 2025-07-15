# Reflex-meter
Arduino‑based reaction‑time meter • MAX7219 LED matrix + 3D‑printed case
# Reflex Meter ⚡ ⏱️  
Measure your reaction time in milliseconds with an **Arduino Uno**, a **MAX7219 8×8 LED matrix** and a single push‑button.

[![YouTube Build Video](https://img.shields.io/badge/YouTube-Build_Video-red?logo=youtube)](https://youtu.be/XXXXXXXX)
*Full build tutorial premieres **Wednesday 20:00 (UTC+3)**—hit the bell so you don’t miss it!*

---

## Table of Contents
1. [Features](#features)  
2. [Bill of Materials](#bill-of-materials)  
3. [Wiring](#wiring)  
4. [3D Printing](#3d-printing)  
5. [Setup](#setup)  
6. [Usage](#usage)  
7. [Contributing](#contributing)  
8. [License](#license)

## Features
- **Millisecond‑accurate stopwatch** using hardware interrupts  
- Instant visual feedback (time + emoji) on the MAX7219 matrix  
- Single‑button start/stop for lightning‑fast tests  
- Snap‑fit 3D‑printed enclosure—no screws needed  
- Clean, well‑commented Arduino sketch (C++)

## Bill of Materials

| Qty | Part | Notes |
|-----|------|-------|
| 1 | Arduino Uno (clone OK) | ATmega328P |
| 1 | MAX7219 8 × 8 LED Matrix | FC‑16 module |
| 1 | 12 mm Momentary Push Button | SPST‑NO |
| 1 | 220 Ω Resistor | LED protection |
| 1 | 5 mm LED | “Ready” indicator |
| – | PLA Filament 

## Wiring
> `docs/wiring.png` will visualize these five lines:  
> **VCC → 5 V**, **GND → GND**, **DIN → D11**, **CS → D10**, **CLK → D13**

![Wiring diagram](docs/wiring.png)

## 3D Printing
STLs are in `/3d-models`.  
Recommended settings: 0.20 mm layer height, 15 % infill, no supports.

## Setup
```bash
git clone https://github.com/kocyunus/reflex-meter.git
cd reflex-meter/Arduino
open ReflexMeter.ino    # Arduino IDE
