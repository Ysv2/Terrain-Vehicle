# Setup Guide

This guide provides step-by-step instructions on how to setup your laptop and program a stm32.

> **NOTE:** Read **all instructions carefully** before starting.

---

## Table of Contents

1. [Flash and Connect to the STM32](#how-to-flash-and-connect-to-the-stm32)

   * [Required Hardware](#required-hardware)
   * [Connection Table](#connection-table)
   * [Laptop Environment Setup](#laptop-environment-setup)
   * [Flashing Procedure](#flashing-procedure)

---

## How to Flash and Connect to the STM32

![USB to UART](/assets/uart_usb.jpg)

You will need a **USB-to-UART device** to connect to the STM32 via the RX and TX pins. Refer to [Bill of Materials](./Bill_of_Materials.md) for recommended models and purchasing details.

---

### Required Hardware

* STM32 Blue Pill (STM32F103C8)
* USB-to-UART converter (CP2102 module)
* Jumper wires
* Laptop with Arduino IDE installed

---

### Connection Table

| USB-UART Device | STM32 Board |
| --------------- | ----------- |
| VCC (5V)        | VCC         |
| GND             | GND         |
| RXD             | TX          |
| TXD             | RX          |

> ⚠️ **WARNING:** Only connect the 5V wire if the STM32 is **powered OFF**.

---

### Laptop Environment Setup

Refer to this guide for additional details:
[https://deepbluembedded.com/stm32-arduino-ide-blue-pill-stm32f103c8t6/](https://deepbluembedded.com/stm32-arduino-ide-blue-pill-stm32f103c8t6/)

#### 1. Install Arduino IDE

Download and install **Arduino IDE 2**:
[https://www.arduino.cc/en/software/](https://www.arduino.cc/en/software/)

---

#### 2. Install STM32CubeProgrammer

Download and install:
[https://www.st.com/en/development-tools/stm32cubeprog.html](https://www.st.com/en/development-tools/stm32cubeprog.html)

---

#### 3. Configure Arduino IDE

1. Open Arduino IDE
2. Go to **File → Preferences**
3. Add this URL under **Additional Boards Manager URLs**:

```
https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json
```

> If you already have URLs, separate them with commas.

4. Open **Board Manager** (left sidebar)
5. Search for **STM32**
6. Install **STM32 MCU based boards**

![STM32 Boards](/assets/STM32_howto.png)

---

### Flashing Procedure

#### 1. Configure Board Settings

Ensure Arduino IDE settings match the configuration below:

* Board: **STM32 BluePill F103C8**

![Configuration](/assets/Flashing_Config.png)

---

#### 2. Enter Programming Mode

Set the STM32 jumper to **Programming Mode** before flashing.

![Mode Switch](/assets/STM32_OperatingvsNormal.jpg)

---

#### 3. Upload Code

1. Click **Upload** in Arduino IDE
2. Press and release the **Reset button** on the STM32
3. Wait for the success message in the terminal

---

#### 4. Return to Operating Mode

After flashing:

* Switch STM32 back to **Operating Mode**
* Restart the board by pressing and releasing the **Reset button** on the STM32

---

## Notes & Tips

* Double-check RX/TX wiring if upload fails
* Ensure correct COM port is selected
* Avoid powering the board from multiple sources simultaneously

---
