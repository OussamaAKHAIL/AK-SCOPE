<div align="center">

<img src="https://github.com/OussamaAKHAIL/AK-SCOPE/blob/main/photos/AK-SCOPE%20LOGO.png?raw=true" alt="AK-SCOPE Logo" width="220"/>

# 🔭 AK-SCOPE

### An Open-Source, Autoguided Dobsonian Telescope

*Democratising astronomy through 3D-printed mechanics, dual-Arduino electronics, and spherical trigonometry.*

<p align="center">
  <a href="https://www.instructables.com/Autoguided-Telescope/"><img src="https://img.shields.io/badge/Featured%20on-Instructables-FFB300?style=for-the-badge&logo=instructables&logoColor=white" alt="Instructables"/></a>
  <a href="https://github.com/OussamaAKHAIL/AK-SCOPE/blob/main/LICENSE"><img src="https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge" alt="License: MIT"/></a>
  <img src="https://img.shields.io/badge/Status-Functional%20Prototype-brightgreen?style=for-the-badge" alt="Status"/>
  <img src="https://img.shields.io/badge/Platform-Arduino%20Nano-00979D?style=for-the-badge&logo=arduino&logoColor=white" alt="Arduino"/>
  <img src="https://img.shields.io/badge/Python-3.10%2B-3776AB?style=for-the-badge&logo=python&logoColor=white" alt="Python"/>
  <img src="https://img.shields.io/badge/C%2B%2B-Firmware-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++"/>
  <img src="https://img.shields.io/badge/CAD-Onshape-1750A4?style=for-the-badge" alt="Onshape"/>
</p>

<p align="center">
  <a href="https://github.com/OussamaAKHAIL/AK-SCOPE/stargazers"><img src="https://img.shields.io/github/stars/OussamaAKHAIL/AK-SCOPE?style=social" alt="Stars"/></a>
  <a href="https://github.com/OussamaAKHAIL/AK-SCOPE/network/members"><img src="https://img.shields.io/github/forks/OussamaAKHAIL/AK-SCOPE?style=social" alt="Forks"/></a>
  <a href="https://github.com/OussamaAKHAIL/AK-SCOPE/issues"><img src="https://img.shields.io/github/issues/OussamaAKHAIL/AK-SCOPE" alt="Issues"/></a>
  <a href="https://github.com/OussamaAKHAIL/AK-SCOPE/pulls"><img src="https://img.shields.io/github/issues-pr/OussamaAKHAIL/AK-SCOPE" alt="PRs"/></a>
  <img src="https://img.shields.io/github/last-commit/OussamaAKHAIL/AK-SCOPE" alt="Last commit"/>
  <img src="https://img.shields.io/github/repo-size/OussamaAKHAIL/AK-SCOPE" alt="Repo size"/>
</p>

<img src="https://github.com/OussamaAKHAIL/AK-SCOPE/blob/main/photos/Design%20sans%20titre.jpg?raw=true" alt="AK-SCOPE Hero Poster" width="85%"/>

</div>

---

## 📑 Table of Contents

- [About the Project](#about-the-project)
- [Showcase](#showcase)
- [Key Features](#key-features)
- [System Architecture](#system-architecture)
- [Mathematical Foundation](#mathematical-foundation)
- [Bill of Materials](#bill-of-materials)
- [Build Guide — 13 Steps from Instructables](#build-guide)
- [Repository Structure](#repository-structure)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Pin Assignments & Wiring](#pin-assignments-wiring)
- [Software Stack](#software-stack)
- [Roadmap & Future Improvements](#roadmap)
- [Contributing](#contributing)
- [Top Contributors](#top-contributors)
- [Acknowledgements](#acknowledgements)
- [Citation](#citation)
- [License](#license)
- [Contact](#contact)

---
<a name="about-the-project"></a>
## 🌌 About the Project

AK-SCOPE is a fully open-source Autoguided Dobsonian Telescope designed and built within the Orange Digital Center FabLab — Morocco. It combines 3D-printed mechanics, dual-Arduino microcontrollers, and a Python-based GUI to automatically aim and track celestial objects using rigorous spherical trigonometry.

The project's central ambition is to democratise observational astronomy — to demonstrate that a GoTo-class instrument, traditionally costing thousands of dollars, can be reproduced from PVC tubes, plexiglass plates, two Arduino Nanos, and a pair of NEMA 17 stepper motors. Every CAD model, schematic, firmware file, GUI script, and the underlying theoretical report (LaTeX) is published in this repository so any maker, hobbyist, or student can replicate, modify, or extend the system.

> 📰 **Featured on Instructables** — *"Autoguided Telescope: 13 Steps (with Pictures)"*
> Published by the **Orange Digital Center** community. View the original step-by-step build guide here:
> 🔗 **[Autoguided-Telescope on Instructables](https://www.instructables.com/Autoguided-Telescope/)**

### 🎯 Project Goals

- 💸 **Affordable** — entire BOM achievable with FabLab-grade tooling and recycled materials.
- 🧩 **Modular** — every mechanical and electronic subsystem can be replaced or upgraded independently.
- 🧠 **Educational** — bundled LaTeX report explains the astronomy, optics, and embedded-systems theory.
- 🌐 **Hybrid Online/Offline** — works with or without a host PC and internet connection.
- ♾️ **Open Forever** — released under the MIT License.

---
<a name="showcase"></a>
## 📸 Showcase

| Mechanical Design (Onshape CAD) | Assembled Telescope |
|---|---|
| <img src="https://github.com/OussamaAKHAIL/AK-SCOPE/blob/main/photos/Screenshot%202026-05-19%20132845.png?raw=true" width="100%"/> | <img src="https://github.com/OussamaAKHAIL/AK-SCOPE/blob/main/photos/Screenshot%202026-06-11%20142301.png?raw=true" width="100%"/> |

| Remote Control GUI (Python / Tkinter) | 3D-Printed Remote Enclosure |
|---|---|
| <img src="https://github.com/OussamaAKHAIL/AK-SCOPE/blob/main/photos/F51UJS4M3SR4LW2.png?raw=true" width="100%"/> | <img src="https://github.com/OussamaAKHAIL/AK-SCOPE/blob/main/photos/Screenshot%202026-06-06%20141017.png?raw=true" width="100%"/> |

---
<a name="key-features"></a>
## ✨ Key Features

| Mode | Description | Hardware Used |
|---|---|---|
| 🛰️ Offline Mode | Pure embedded operation. The firmware contains a hardcoded catalog of 20 bright stars (Sirius, Vega, Betelgeuse, Polaris, …). The Arduino performs the floating-point trigonometry on-board. | Arduino #1 + RTC |
| 🌐 Online Mode | A Python/Tkinter desktop application uses Selenium WebDriver to scrape live Alt/Az coordinates from Stellarium Web and streams them over UART (`115200 baud`) to the telescope. | Python GUI + UART |
| 🎯 Tracking Mode | A "following" algorithm derives the spherical equations with respect to time to obtain the instantaneous angular velocities `d(Alt)/dt` and `d(Az)/dt`, allowing the telescope to follow celestial targets continuously — enabling long-exposure astrophotography. | Dual-axis steppers |
| 🕹️ Manual Mode | A 2-axis analog joystick streams variable-speed step commands directly to the motor drivers, ideal for framing and fine adjustment. | Joystick + Arduino #2 |
| 🔴 Green-Laser Aiming Aid | Auxiliary laser bore-sighted to the optical axis to help locate targets visually (added during final testing). | 5 mW green laser |

---
<a name="system-architecture"></a>
## 🧱 System Architecture

The electronics are deliberately split into a Dual-Arduino Architecture to isolate the noisy motor-driver power lines from the sensitive I²C/LCD/joystick analogue front-end. This separation eliminates the parasitic signals observed when the entire system was driven from a single 12 V rail.

```
                           ┌────────────────────────────┐
                           │   Python GUI (PC, Online)  │
                           │  Tkinter + Selenium scraper│
                           └──────────────┬─────────────┘
                                          │ USB-UART 115200 baud
                                          ▼
┌──────────────────────────┐   Galvanic   ┌──────────────────────────┐
│   ARDUINO #1 — REMOTE    │◀── ISO7221 ─▶│   ARDUINO #2 — MOTOR     │
│  • 16x2 I²C LCD          │   isolator   │  • 2× A4988 drivers      │
│  • Analog joystick       │              │  • NEMA 17 stepper × 2   │
│  • Mode/Settings buttons │              │  • Limit / home switch   │
│  • RTC clock             │              │  • 12 V / 3 A fuse rail  │
│  • Spherical maths       │              │  • Calibration logic     │
└──────────────────────────┘              └──────────────────────────┘
```

| Block | Role |
|---|---|
| Arduino #1 (Remote) | UI brain — handles LCD, joystick, push-buttons, RTC, and the heavy floating-point trigonometry. |
| Arduino #2 (Motors) | Dedicated power controller — receives Alt/Az targets via UART and drives the two NEMA 17 steppers through A4988 drivers in 1/32 microstepping. |
| ISO7221 Digital Isolator | Provides galvanic isolation between the two boards, preventing EMI from corrupting the LCD/analogue signals. |

**🖼️ Circuit Diagrams:**

| Motor Control Circuit (Arduino #2) | Remote Control Circuit (Arduino #1) |
|---|---|
| <img src="https://github.com/OussamaAKHAIL/AK-SCOPE/blob/main/photos/jj.drawio.png?raw=true" width="100%"/> | <img src="https://github.com/OussamaAKHAIL/AK-SCOPE/blob/main/photos/second%20ar.drawio.png?raw=true" width="100%"/> |

---
<a name="mathematical-foundation"></a>
## 📐 Mathematical Foundation

AK-SCOPE relies on a rigorous implementation of spherical trigonometry to convert absolute equatorial coordinates (Right Ascension `RA`, Declination `Dec`) into local horizontal coordinates (Altitude `Alt`, Azimuth `Az`).

**1. Local Sidereal Time (LST)**

Computed from the on-board RTC and the observer's geographical longitude:

```
LST = GST + longitude_east
```

**2. Hour Angle (HA)**

Position of the target relative to the local meridian:

```
HA = (LST − RA) × 15°
```

**3. Altitude & Azimuth (Spherical Law of Cosines on the PZS triangle)**

```
sin(Alt) = sin(Dec)·sin(Lat) + cos(Dec)·cos(Lat)·cos(HA)

cos(Az)  = ( sin(Dec) − sin(Alt)·sin(Lat) ) / ( cos(Alt)·cos(Lat) )
```

**4. Tracking — Time Derivatives**

For real-time tracking, the firmware differentiates the equations w.r.t. time to obtain `d(Alt)/dt` and `d(Az)/dt`, which set the per-axis stepper velocities.

> 📚 **Full derivation** of these equations and their numerical implementation is included in the LaTeX report (`main.tex`) bundled with this repository.

---
<a name="bill-of-materials"></a>
## 🛒 Bill of Materials (BOM)

### 🔌 Electronics

| Qty | Component | Purpose |
|---|---|---|
| 2 | Arduino Nano | Dual-MCU controller (Remote + Motor) |
| 2 | A4988 stepper driver | 1/32 microstepping motor control |
| 2 | NEMA 17 stepper motor (1.8°/step) | Altitude + Azimuth actuators |
| 1 | 16×2 I²C LCD | Status & menu display |
| 1 | Analog joystick (2-axis + push) | Manual control & menu navigation |
| 2 | Tactile push buttons | Mode-switch + Settings |
| 1 | ISO7221 digital isolator | Galvanic isolation between MCUs |
| 1 | DS3231 RTC module | Real-time clock for sidereal time |
| 1 | Limit / home switch | Calibration end-stop |
| 1 | 12 V DC power supply (≥ 3 A) | Main power rail |
| 1 | 3 A fuse (in-line) | Over-current protection |
| 1 | 5 mW green laser | Visual aiming aid |
| — | Hook-up wire, headers, JST connectors | Wiring |

### 🛠️ Mechanics & Optics

| Component | Specification |
|---|---|
| Mount type | Dobsonian (Alt-Azimuth) — chosen for stability & low CoG |
| Azimuth drive | GT2 timing belt as 393-tooth ring gear + 11-tooth pinion ⇒ 35.7 : 1 reduction |
| Altitude drive | 3D-printed 96-tooth half-gear + 11-tooth pinion ⇒ 8.7 : 1 reduction |
| Microstepping resolution | 1/32 step ⇒ ~5.7 arcsec/step in azimuth |
| Body | Concentric PVC tubes Ø 63 mm / Ø 50 mm with 3D-printed sliding rails |
| Objective lens | 1 diopter ⇒ f = 1000 mm |
| Eyepiece lens | 12 diopter ⇒ f ≈ 83 mm |
| Magnification | ≈ 12× (1000 / 83) — wide field of view |
| Plate material | Plexiglass (hot-bent to shape using a heat gun) |
| 3D-printed parts | Gears, lens holders, tube sliders, PCB & PSU brackets, laser holder, remote enclosure |

### 🧰 Fabrication Tools

- 3D printer (FDM, ≥ 200×200 mm bed)
- Laser cutter (for plexiglass — optional)
- Heat gun (to bend plexiglass)
- Soldering iron + multimeter + oscilloscope
- Calipers, hex/Allen keys, screwdrivers

---
<a name="build-guide"></a>
## 🛠️ Build Guide — 13 Steps from Instructables

The complete walkthrough is published on Instructables. Below is the summarised step-by-step roadmap, including the YouTube companion videos that accompany each step.

> ⚠️ The video links below need the actual YouTube URLs added — they were missing from the source file.

### 🧩 Step 1 — CAD Conception

The entire telescope is modelled in Onshape, an online CAD platform. Precise simulation of how parts fit together avoids costly mechanical reworks during physical assembly. The Onshape models cover the tube assembly, the Dobsonian mount, and the motor housings. Collaborative features of Onshape allowed iterative design refinement before any material was committed.

### 🔄 Step 2 — Building the Rotating Base (Z-Axis / Azimuth)

The azimuth base is split into two plexiglass desks:

- **Lower desk** — a GT2 toothed belt is glued around the circumference, acting as a giant 393-tooth ring gear.
- **Upper desk** — carries the stepper motor with its 11-tooth pinion meshing the belt, plus three bearings positioned at 120° for rotational stability and a central pivot bearing for axial load.

Result: a low-friction, high-reduction (35.7 : 1) azimuth drive.

🎥 **Watch:** Building the Rotating Base *(add video link)*

### ⛰️ Step 3 — Building the X-Axis Rotation (Altitude)

A compact gear-train provides up/down motion:

- 11-tooth pinion on the stepper motor.
- 96-tooth half-gear (only half printed to save filament and space).
- Two plexiglass plates clamp the gear-train; a third reinforcement plate damps vibration.
- The plexiglass is hot-bent with a heat gun to fit the motor profile.
- Reduction ratio: 8.7 : 1.

🎥 **Watch:** Building the X-Axis Rotation *(add video link)*

### 🔬 Step 4 — Lenses

Magnification follows: `M = f_objective / f_eyepiece`.

- Objective: 1 diopter → f = 1 m
- Eyepiece: 12 diopter → f ≈ 83 mm
- ⇒ Magnification ≈ 12×

This yields excellent results on the Moon (craters, mare boundaries) and large deep-sky comets (e.g. C/2023 A3), while remaining honest about the limits for planetary detail.

🎥 **Watch:** Lenses & Magnification *(add video link)*

### 🛢️ Step 5 — Telescope Body

The tube is built from two concentric PVC pipes (Ø 63 mm / Ø 50 mm). Two custom 3D-printed sliders allow the inner tube to translate inside the outer one for manual focusing while staying perfectly co-axial. A screw-nut + bearing fixture clamps the body to the altitude assembly. Lens holders are friction-fit (no glue), making the optics swap-friendly.

🎥 **Watch:** Telescope Body Assembly *(add video link)*

### 🧪 Step 6 — Testing Mechanism

Once the rotating base, altitude axis, and tube are integrated, the mechanism is dry-tested by hand to confirm:

- No binding in either axis.
- Backlash within tolerance.
- Smooth focus translation.
- Centre of gravity correctly balanced on the Dobsonian mount.

🎥 **Watch:** Testing Mechanism *(add video link)*

### ⚡ Step 7 — Wiring and Power Supply

- A 12 V supply feeds the stepper drivers and motors.
- A 3 A in-line fuse protects against over-current.
- Arduino Nano drives the two A4988 drivers.
- A limit / home switch on pin D6 of the motor Arduino provides one-time mechanical calibration: at startup, the altitude motor seeks the switch, sets that point as a known reference, then moves to 0° as the ready position. Thereafter the firmware keeps track of the position, so re-homing is needed only once per session — the switch then becomes an over-rotation safety stop.

**Pin map (Motor Arduino):**

| Pin | Function |
|---|---|
| D2 | STEP — Stepper #1 (top) |
| D3 | DIR — Stepper #1 |
| D4 | DIR — Stepper #2 (bottom) |
| D5 | STEP — Stepper #2 |
| D6 | Limit / home switch |
| 5 V | Logic supply for drivers |
| GND | Common ground |
| VMOT | 12 V motor rail |
| MS1/MS2/MS3 | Tied to 5 V → 1/16-step (lowest speed mode) |

### 🎮 Step 8 — Design of the Remote Control

The remote is built around three controls plus a 16×2 LCD:

- **Joystick** — menu navigation, target selection (click to confirm), and manual jogging.
- **Button #1** — Settings (date/time configuration).
- **Button #2** — Cycle modes: Offline / Online / Manual.

The layout is optimised for one-handed use in the dark; the LCD provides real-time feedback (current mode, selected star, tracking status).

🎥 **Watch:** Remote Control Design *(add video link)*

### 🧠 Step 9 — Remote Control System (Dual-Arduino Logic)

Initially the remote was wired into the motor Arduino, but the 12 V switching supply injected enough EMI to corrupt joystick reads and LCD I²C transactions even with twisted-pair wiring. The fix: a second Arduino Nano dedicated to the remote.

- Arduino #1 (motors) ↔ Arduino #2 (remote + maths).
- They share the joystick lines (each reads them independently).
- Three signalling pins synchronise the active mode: pins D9 / D8 on the Remote Arduino map to D10 / D11 on the Motor Arduino, advertising the current mode.
- UART is reserved for the calculated Alt / Az target stream.

This separation eliminated all interference and prevented accidental motor movement while navigating menus.

🎥 **Watch:** Remote Control System *(add video link)*

### 🔋 Step 10 — Power Supply and PCB Assembly

- The 12 V brick is wired through a detachable cable for transport.
- A 3D-printed PSU bracket suspends the supply clear of the rotating axis.
- A 3D-printed PCB holder mounts the electronics inside the body.
- A dedicated access hole in the body lets the user plug a USB cable into Arduino #2 when switching to Online Mode.

🎥 **Watch:** Power Supply & PCB *(add video link)*

### 🧮 Step 11 — The Math Behind Azimuth and Altitude

A primer on positional astronomy:

- **RA** → "celestial longitude"
- **Dec** → "celestial latitude"
- **Az** → horizon-referenced bearing (clockwise from north)
- **Alt** → angular height above the horizon

The firmware ingests target RA/Dec + observer Lat/Lon + current UTC and solves the spherical PZS triangle (see [Mathematical Foundation](#mathematical-foundation)). A simplifying assumption is made: distant stars' RA/Dec drift is negligible over short sessions, so precession/nutation/aberration are intentionally omitted to keep the on-board maths fast.

### 💻 Step 12 — Telescope and GUI Programming

The software stack has two halves:

**1) Python GUI (PC side)**

- Tkinter UI — list of sky objects, COM-port detector, animated background.
- Selenium WebDriver — scrapes live Alt/Az from Stellarium Web.
- pySerial — streams the coordinates to the Arduino at 115200 baud.

**2) Arduino firmware (telescope side) — three modes**

- **Online Mode** — receive Alt/Az over Serial, drive the steppers using the AccelStepper library with acceleration/deceleration profiles.
- **Offline Mode** — use the hardcoded star catalog plus on-board spherical maths.
- **Joystick Mode** — direct manual control with adjustable sensitivity thresholds.

> 💡 Because two Arduinos share a single USB-Serial port to the GUI, a **virtual serial-port splitter** (e.g., *Launch Virtual Serial Port Driver*) is recommended on Windows.

### 🌠 Step 13 — Final Test and Future Improvements

A green laser was bore-sighted to the optical axis with a 3D-printed bracket — this is invaluable because the eyepiece image is inverted, which can otherwise make targeting confusing.

**Night-time field results:**

- Excellent imaging of the Moon.
- Successful capture of comet C/2023 A3 (Tsuchinshan–ATLAS) near its peak appearance.

**Future improvements envisioned by the author:**

- Add a piggy-back 80× small telescope for higher magnification.
- Implement a complete sidereal tracking mode (now realised in the firmware).
- Add plate-solving for autonomous alignment.

🎥 **Watch:** Final Test & First Light *(add video link)*

---
<a name="repository-structure"></a>
## 📂 Repository Structure

```
AK-SCOPE/
├── codes/
│   ├── arduino1.cpp        # ➤ Remote / Logic Arduino firmware
│   ├── arduino2.cpp        # ➤ Motor controller Arduino firmware
│   └── software.py         # ➤ Python Tkinter GUI (Online Mode)
├── cad/                    # Onshape exports (STEP, STL)
├── electronics/            # Schematics (.drawio, PDF)
├── photos/                 # Build photos, renders, screenshots
├── report/
│   ├── main.tex            # LaTeX theoretical report
│   └── main.pdf             # Compiled PDF
├── LICENSE                 # MIT
└── README.md               # ← you are here
```

---
<a name="getting-started"></a>
## 🚀 Getting Started

### Prerequisites

- **Hardware** — completed assembly per [Build Guide](#build-guide).
- **Software**
  - Arduino IDE ≥ 1.8 (or 2.x)
  - Python ≥ 3.10
  - Google Chrome + matching `chromedriver` (Selenium dependency)
  - Arduino libraries: `AccelStepper`, `LiquidCrystal_I2C`, `Wire`, `RTClib`

### Installation

```bash
# 1) Clone the repository
git clone https://github.com/OussamaAKHAIL/AK-SCOPE.git
cd AK-SCOPE

# 2) Install Python dependencies
pip install pyserial selenium tkinter pillow

# 3) Upload firmware to the two Arduinos
#    - Open codes/arduino1.cpp in Arduino IDE → upload to the REMOTE board
#    - Open codes/arduino2.cpp in Arduino IDE → upload to the MOTOR board

# 4) (Windows) Install a virtual COM-port splitter such as
#    'Launch Virtual Serial Port Driver' to multiplex the two Arduinos.
```

---
<a name="usage"></a>
## ▶️ Usage

### 🌐 Online Mode (PC-connected)

```bash
python codes/software.py
```

1. The GUI lists every available COM port — pick the one assigned to Arduino #2 (motors).
2. Choose a celestial object from the catalog.
3. Click **Search** — Selenium fetches the live Alt/Az from Stellarium Web.
4. Coordinates are streamed to the telescope and the steppers begin slewing.

### 🛰️ Offline Mode (no PC)

1. Power up — wait for the calibration sequence (altitude axis seeks the home switch, then goes to 0°).
2. Press **Button #2** to cycle to Offline.
3. Scroll the joystick through the 20-star catalog; press to confirm — the telescope slews automatically.

### 🕹️ Manual Mode

1. Press **Button #2** to cycle to Manual.
2. Push the joystick — telescope slews at a speed proportional to deflection.

---
<a name="pin-assignments-wiring"></a>
## 🔌 Pin Assignments & Wiring

### Motor Arduino (Arduino #2)

| Pin | Net | Notes |
|---|---|---|
| D2 | STEP1 | Top stepper (altitude) |
| D3 | DIR1 | — |
| D4 | DIR2 | Bottom stepper (azimuth) |
| D5 | STEP2 | — |
| D6 | LIMIT_SW | Home / safety switch |
| D10/D11 | MODE_IN | From Remote Arduino |
| 5 V | VCC | Driver logic |
| GND | GND | Common |
| VMOT | +12 V | After 3 A fuse |

### Remote Arduino (Arduino #1)

| Pin | Net | Notes |
|---|---|---|
| A4 / A5 | SDA / SCL | I²C LCD + RTC |
| A0 / A1 | JOY_X / JOY_Y | Analogue joystick |
| D2 | JOY_BTN | Joystick click |
| D3 | BTN_SETTINGS | Settings button |
| D4 | BTN_MODE | Mode-cycle button |
| D8 / D9 | MODE_OUT | To Motor Arduino |
| TX/RX | UART | Through ISO7221 isolator |

---
<a name="software-stack"></a>
## 🧰 Software Stack

| Layer | Technology |
|---|---|
| Embedded firmware | C++ (Arduino) — `AccelStepper`, `LiquidCrystal_I2C`, `Wire`, `RTClib` |
| Desktop GUI | Python — `tkinter`, `pyserial`, `Pillow` |
| Web scraping | Python — `selenium`, headless Chromium |
| CAD | Onshape (cloud) |
| Schematics | drawio (.drawio) |
| Documentation | LaTeX (`main.tex`), Markdown (this file) |

---
<a name="roadmap"></a>
## 🗺️ Roadmap & Future Improvements

- [x] Spherical-trig Alt/Az conversion on-board
- [x] Offline mode with 20-star catalog
- [x] Online mode via Stellarium Web + Selenium
- [x] Manual joystick mode
- [x] Galvanically isolated dual-Arduino architecture
- [x] Sidereal tracking ("Following Algorithm")
- [ ] Piggy-back 80× refractor for high-mag observation
- [ ] Plate-solving autonomous alignment (via Raspberry Pi + ASTAP/astrometry.net)
- [ ] Wi-Fi / Bluetooth wireless control (ESP32 upgrade)
- [ ] Mobile app (Flutter) replacement for the desktop GUI
- [ ] INDI / ASCOM driver for compatibility with mainstream astrophotography software (KStars, NINA, SharpCap)
- [ ] Polar-alignment assistant
- [ ] Auto-focus motorisation
- [ ] Extended catalog (Messier, NGC, IC, double stars)
- [ ] Closed-loop tracking using a guide CCD (PHD2-style)

See the [open issues](https://github.com/OussamaAKHAIL/AK-SCOPE/issues) for the full backlog of proposed features and known bugs.

---
<a name="contributing"></a>
## 🤝 Contributing

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Every contribution is warmly welcomed.

1. Fork the project
2. Create your feature branch (`git checkout -b feature/MyAmazingFeature`)
3. Commit your changes (`git commit -m 'Add MyAmazingFeature'`)
4. Push to the branch (`git push origin feature/MyAmazingFeature`)
5. Open a Pull Request

### Good first issues

- Translate the LCD strings to additional languages
- Expand the offline star catalog beyond 20 stars
- Add unit tests for the spherical-trig routines
- Improve the Tkinter GUI styling
- Document the Onshape models with step-by-step screenshots

### Code style

- **C++** — follow Arduino style; 2-space indent; `snake_case` for variables, `camelCase` for functions.
- **Python** — PEP 8; type hints encouraged; `black` formatting.

---
<a name="top-contributors"></a>
## 🌟 Top Contributors

Thanks goes to these wonderful people who contributed to this project:

<a href="https://github.com/OussamaAKHAIL/AK-SCOPE/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=OussamaAKHAIL/AK-SCOPE" alt="Contributors"/>
</a>

| Avatar | Contributor | Role |
|---|---|---|
| <img src="https://github.com/OussamaAKHAIL.png" width="60"/> | Oussama AK-HAIL | 👨‍🔬 Creator, Lead Developer, Mechanical & Electronic Designer, Firmware & GUI Author |
| ✨ | Mohammed Bsiss | 🎓 Engineering Internship Supervisor |

> Want to see your face here? Open a PR! Even small improvements — documentation typos, translated comments, additional schematic notes — earn you a slot in this list.

---
<a name="acknowledgements"></a>
## 🙏 Acknowledgements

This project was carried out as part of an engineering internship. A huge thanks to:

| Organisation | Contribution |
|---|---|
| 🟠 Orange Digital Center Agadir | FabLab access — 3D printers, laser cutters, oscilloscopes, mentoring |
| 🟢 Moussasoft | Electronic components, stepper motors, and integration expertise |
| 👨‍🏫 Mohammed Bsiss | Internship supervisor — mentoring and technical reviews |
| 📰 Instructables / Autodesk | Hosting the original step-by-step publication of this build |

Additional inspiration drawn from the broader DIY astronomy community — rDUINOScope, OpenAstroTracker, Stellarium, the AccelStepper library, and every Arduino telescope-mod thread on Cloudy Nights and r/telescopes.

---
<a name="citation"></a>
## 📑 Citation

If you use AK-SCOPE in research, education, or a derivative project, please cite it as:

```bibtex
@misc{akhail2024akscope,
  author       = {AK-HAIL, Oussama},
  title        = {AK-SCOPE: An Open-Source Autoguided Dobsonian Telescope},
  year         = {2024},
  howpublished = {\url{https://github.com/OussamaAKHAIL/AK-SCOPE}},
  note         = {Featured on Instructables: \url{https://www.instructables.com/Autoguided-Telescope/}}
}
```

---
<a name="license"></a>
## 📄 License

Distributed under the MIT License. See `LICENSE` for the full text.

> *Feel free to explore the code, modify it, build your own version of the telescope, or use any part of this project in your own work — commercial or not. A credit-back link to this repository is appreciated but not required.*

---
<a name="contact"></a>
## 📬 Contact

Oussama AK-HAIL — Creator & Lead Developer

- 🐙 GitHub: [@OussamaAKHAIL](https://github.com/OussamaAKHAIL)
- 🔗 Project Link: <https://github.com/OussamaAKHAIL/AK-SCOPE>
- 📰 Instructables: <https://www.instructables.com/Autoguided-Telescope/>

For questions, feature ideas, or build help, please open an [issue](https://github.com/OussamaAKHAIL/AK-SCOPE/issues) — that way the answer benefits the whole community.

---

<div align="center">

⭐ If AK-SCOPE helped you reach the stars, please give it a star on GitHub! ⭐

Look up, select your target, and let this telescope take you there — because the universe is yours to explore. 🌌

<sub>Built with ❤️, plexiglass, PVC tubes, and a lot of spherical trigonometry — at the Orange Digital Center FabLab, Morocco.</sub>

</div>
