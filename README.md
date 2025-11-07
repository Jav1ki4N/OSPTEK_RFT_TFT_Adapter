# OSPTEK_RFT_TFT_Adapter
An adapter board for the Osptek ST7306 reflective TFT displays.
It allows you to interface the display directly with your MCU by connecting the corresponding pins.

**THE FPC CONNECTOR MUST BE TOP CONTACT**, that is, the FPC cable must be inserted with the contact pads facing up.

![](https://raw.githubusercontent.com/Jav1ki4N/OSPTEK_RFT_TFT_Adapter/refs/heads/main/2D_PCB/Top.png)
![](https://raw.githubusercontent.com/Jav1ki4N/OSPTEK_RFT_TFT_Adapter/refs/heads/main/2D_PCB/Buttom.png)

| Type       | Name                     | Value                                       | Quantity |
| ---------- | ------------------------ | ------------------------------------------- | -------- |
| Capacitor  | C1,C3,C5,C6,C7,C8,C9,C10 | 1uF                                         | 8        |
| Capacitor  | C2,C4                    | 0.1uF / 100nF                               | 2        |
| Resisiter  | 0R                       | 0Ω                                          | 1        |
| Resisiter  | R2                       | 1kΩ / 470Ω... ，depends on the choice of LED | 1        |
| LED        | POWER                    | -                                           | 1        |
| FPC dip    | FPC DIP                  | 24Pin 0.5mm                                 | 1        |
| Pin Header | -                        | 8  Pin 2.54mm                               | 1        |
| Screw      | -                        | M2                                          | 4        |
