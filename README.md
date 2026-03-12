\# 🚤 Fisherman Rescue at Ocean Borders



> A real-time wireless alert system that tracks fishing boats near maritime borders and triggers emergency alerts to prevent illegal crossings and save lives.



\---



\## ✦ The Problem



Fishermen often unknowingly cross maritime borders, leading to detention, loss of boats, and sometimes endangering their lives. There's rarely any real-time warning system to alert them before it's too late.



This project tackles that.



\---



\## ✦ What it does



The system continuously tracks a boat's GPS location and automatically triggers alerts when it approaches or crosses a maritime border — both on the boat (so the fisherman knows) and at the shore station (so rescue teams can respond).



```

Boat (Transmitter)                    Shore (Receiver)

──────────────────                    ────────────────

GPS Module                            NRF24L01 RF Module

&#x20; ↓ real-time coordinates             ↓ receives coordinates

NRF24L01 RF Module  ──── wireless ──→ checks against border limits

&#x20; ↓                                   ↓

LCD Display                           ALERT triggered if border crossed

(shows current location)              + two-way distress signal support

```



\---



\## ✦ Features



\- 📍 \*\*Real-time GPS tracking\*\* — continuous location monitoring on the boat

\- 📡 \*\*Wireless RF communication\*\* — NRF24L01 modules for two-way data transfer

\- 🖥️ \*\*LCD display\*\* on transmitter showing live coordinates

\- 🚨 \*\*Automatic border alerts\*\* at the shore receiver station

\- 🆘 \*\*Two-way distress signaling\*\* — fisherman can send SOS, shore can confirm

\- ⚡ Low power, field-deployable hardware setup



\---



\## ✦ Circuit Diagrams



\### Transmitter (Boat Side)

!\[Transmitter Circuit](TRANSMITTER-CIRCUIT.png)



\### Receiver (Shore Side)

!\[Receiver Circuit](RECEIVER-CIRCUIT.png)



\---



\## ✦ Tech Stack



!\[C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge\&logo=c%2B%2B\&logoColor=white)

!\[Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge\&logo=arduino\&logoColor=white)



| Component | Role |

|---|---|

| NRF24L01 RF Module | Wireless communication between boat and shore |

| GPS Module | Real-time location tracking |

| LCD Display | Show coordinates on the transmitter side |

| Arduino | Microcontroller for both transmitter and receiver |

| Embedded C++ | Core logic for both units |



\---



\## ✦ Project Structure



```

Fisherman-Rescue-at-OceanBorders/

├── transmitter.ino        # Boat-side code (GPS + RF transmit + LCD)

├── receiver.ino           # Shore-side code (RF receive + alert logic)

├── TRANSMITTER-CIRCUIT.png

└── RECEIVER-CIRCUIT.png

```



\---



\## ✦ How to Run



\### Prerequisites

\- Arduino IDE

\- NRF24L01 RF modules (x2)

\- GPS module (NEO-6M or similar)

\- LCD display (16x2)

\- Arduino boards (x2)



\### Setup

1\. Open `transmitter.ino` in Arduino IDE → upload to the \*\*boat Arduino\*\*

2\. Open `receiver.ino` in Arduino IDE → upload to the \*\*shore Arduino\*\*

3\. Power both units and watch the coordinates stream live on the LCD

4\. Move the transmitter GPS past the set border threshold → alert triggers



\---



\## ✦ Team



Built as a team project for our final year at college 🎓



\*\*\[Tanya Singh](https://github.com/tanya004)\*\* and team

