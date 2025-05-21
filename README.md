# 🧠 DIY Macropad
This is a DIY macro pad project built around an Arduino Pro Micro, designed to help me learn more about electronics and hardware development as someone who typically works in software.

The macro pad features:
- 🟫 Mechanical switches (Outemu Browns)
- 🔁 Rotary encoder 
- 🔴🟡🟢 State LEDs to indicate current mode
- 🧾 Custom PCB designed and included in this repo (Gerber files provided)

## 💡 Project Purpose

This project started as a way to push myself out of my comfort zone and dive into more of the hardware side, electronics, and embedded systems. It’s helped me develop skills in:

- Soldering and prototyping
- Designing custom PCBs
- Working with electronics equipment
- Embedded C/C++ programming for microcontrollers

## 🧰 Components Used

- 2 Arduino Pro Micro (ATmega32U4) Killed 1 already
- 11 Outemu Brown tactile switches (Pack of 30)
- Rotary encoder (KY-040)
- 3 LEDs (Red, Yellow, Green)
- 1N4148 diodes (for switch matrix)
- Custom PCB (Gerber files provided)
- Misc: resistors, headers, wires

## 🖨️ PCB Design

The PCB has been custom-designed in EasyEDA and includes:
- Matrix layout for switches
- Component footprints
- Header slots for extra pins not used + more PWR & GND pins

You can find the `Macropad_Gerber_V1.zip` file in this repository to use with your choice of PCB fabrication service.

## 🚧 Current Status

- [x] Switch matrix tested and working
- [x] Rotary encoder reads direction correctly
- [x] Killing atleast 1 component in the process
- [x] Components connected with PCB
- [x] Layering System implemented
- [-] Assigning Macros
- [ ] Layer LEDs light up based on current layout
- [-] Final case/enclosure (WIP)

## 🛠️ Future Ideas

- Add QMK/VIA support for easy reprogramming
- Build a 3D printed case
- Experiment with OLED displays or sound feedback

## 📷 Gallery

Coming Soon..

## 📁 Files in This Repo

- `/src/macroPad.cpp` — Arduino code for controlling the macro pad
- `Macropad_Gerber_V1.zip` — Gerber to use my PCB
- `README.md` — You’re reading it!


---

