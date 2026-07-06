# ESP32 AI Voice Robot 🤖

Firmware architecture for an AI-powered Voice Robot built using the **ESP32** microcontroller and integrated with the [Xiaozhi AI platform](https://xiaozhi.dev/) for real-time LLM interaction and low-latency audio streaming.

---

## 📸 Hardware Showcase
<table align="center">
  <tr>
    <td align="center">
      <img src="robot1.jpg" alt="Robot Front" width="250px"/><br/>
      <sub><b>Tampak Depan</b></sub>
    </td>
    <td align="center">
      <img src="robot2.jpg" alt="Robot Detail" width="250px"/><br/>
      <sub><b>Detail Komponen</b></sub>
    </td>
    <td align="center">
      <img src="robot3.jpg" alt="Robot Setup" width="250px"/><br/>
      <sub><b>Sistem/Skema</b></sub>
    </td>
  </tr>
</table>

---

## 🚀 Features
* **Real-time Voice Interaction:** Low-latency audio streaming over Wi-Fi WebSocket.
* **AI-Powered Brain:** Integrated with Xiaozhi Dev for LLM orchestration and TTS.
* **Hardware Efficiency:** Optimized for ESP32 with external I2S audio modules.

## 🛠️ Hardware Setup & Pin Mapping
| Component | Pin Name | ESP32 GPIO |
|-----------|----------|------------|
| **INMP441 (Mic)** | WS | GPIO 25 |
| | SCK | GPIO 26 |
| | SD | GPIO 33 |
| **MAX98357A (DAC)**| LRC | GPIO 22 |
| | BCLK | GPIO 19 |
| | DIN | GPIO 21 |

## 💻 Software Configuration
1. Open the project inside VS Code with **PlatformIO**.
2. Configure your network and token credentials in `src/config.h`.
3. Build and Flash to your ESP32 board.

---
Developed with ❤️ by [immaculate](https://github.com/immaculaterabbit)
