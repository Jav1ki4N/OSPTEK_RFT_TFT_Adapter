# OSPTEK RFT TFT Adapter

An adapter board designed for **Osptek ST7306 reflective TFT display**.
It allows you to directly interface the display with your MCU via simple pin connections.

> **Important:**
> The **FPC connector must be Top Contact**, meaning the display’s FPC cable should be inserted with the **contact pads facing upward**.

---

## PCB Overview

**Top View**
![](https://raw.githubusercontent.com/Jav1ki4N/OSPTEK_RFT_TFT_Adapter/refs/heads/main/2D_PCB/Top.png)

**Bottom View**
![](https://raw.githubusercontent.com/Jav1ki4N/OSPTEK_RFT_TFT_Adapter/refs/heads/main/2D_PCB/Buttom.png)

---

## BOM

| Type          | Name                            | Value / Description                   | Qty |
| ------------- | ------------------------------- | ------------------------------------- | --- |
| Capacitor     | C1, C3, C5, C6, C7, C8, C9, C10 | 1 µF                                  | 8   |
| Capacitor     | C2, C4                          | 0.1 µF / 100 nF                       | 2   |
| Resistor      | R1                              | 0 Ω (jumper)                          | 1   |
| Resistor      | R2                              | 1 kΩ ~ 470 Ω (depends on LED current) | 1   |
| LED           | POWER                           | Power indicator LED                   | 1   |
| FPC Connector | FPC DIP                         | 24 Pin – 0.5 mm Pitch – Top Contact   | 1   |
| Pin Header    | —                               | 8 Pin – 2.54 mm Pitch                 | 1   |
| Screw         | —                               | M2                                    | 4   |

---

## Assembly Notes

The display aligns perfectly with the board.
For a tighter fit, a **1 mm EVA foam tape** can be placed between the PCB and the display.

![](https://raw.githubusercontent.com/Jav1ki4N/OSPTEK_RFT_TFT_Adapter/refs/heads/main/Verification/HowItLooksLike.jpg)

---

## Verification

The adapter has been fully tested and confirmed working.
Below is a demonstration of the display running on an STM32F4 MCU in bare-metal mode:

![](https://raw.githubusercontent.com/Jav1ki4N/OSPTEK_RFT_TFT_Adapter/refs/heads/main/Verification/ItWorksOnMyDevice.gif)

可以，这段话我帮你润色成正式、自然的英文版本，保持简洁、技术风格一致，适合放在 README 的末尾使用：

---

## Quick Start

To test the display, simply call:

```c
LCD_Init();
Fill_Black();
```

The screen should then be completely filled with black pixels.

> **Note:**
> The provided code is **only intended for testing** on bare-metal STM32F4 platforms.
> For more complete and feature-rich implementations, you can find well-developed drivers for **ESP32** on GitHub.

--- 
