# Technical Guide

This guide provides detailed information on the electrical design and circuitry used on the terrain vehicle.

> **NOTE:** Read **all instructions carefully** before starting.

---

## Table of Contents

1. [Overview](#overview)
2. [Power distribution, Switches, Safety mechanism](#power-distribution-switches-safety-mechanism)
3. [Motor Controller](#motor-controller)
4. [Vehicle HeadLamps](#vehicle-headlamps)
5. [Receiver](#receiver)
6. [Transmitter](#transmitter)

---

## Overview

The electrical system can be split into 6 main parts:

- Power distribution, Switches, Safety mechanism (On the vehicle)
- Motor Controller (On the vehicle)
- Vehicle HeadLamps (On the vehicle)
- Receiver (On the vehicle)
- Transmitter (Remote Controller)

---

## Power distribution, Switches, Safety mechanism

There are a total of three 12V lead acid batteries used on this vehicle.

They are connected in this manner:

- 12V for electronics
- 24V for both motors

There are 2 switches and a E-Stop button. One switch controls power to the electronics such as the arduino and receiver and the other controls the power to the motors. The e-stop cuts power from the motors. The e-stop is wired in a way whereby it utilises 2 relays which is controlled by the e-stops normally open and normally closed switch state to ensure that the e-stop is wired and operational, else it will cuts power if a wire is loose or disconnected.

> **NOTE:** NRF24 module uses **3.3V** power.

> **NOTE:** Arduino uses **5V** logic whereas stm32 uses **3.3V** logic thus a logic level shifter is used.

![PowerDiagram](/assets/PowerCircuit.svg)

---

## Motor Controller

The vehicle has 2 electrical motors, each comes with its own logic board where we are able to interface with each motor to control it's direction and speed. An arduino Uno is used to recieve both velocity and lights commands from the stm32 microcontroller which is the receiver.

![MotorDriverBoard](/assets/motordriverboard.jpg)
![ArduinoUno](/assets/arduino_uno.jpg)
![ArduinoPinout](/assets/Arduino_pinout.png)


### Motor Driver Pinout Table

Below shows the connector used to interface with the motors and its functions.  
Wires highlighted in red have digital logic and depending and it's state changes the function of the motor. Refer to the images below for more information.

![MotorDriverPinOut](/assets/MotorDriverPinOut.jpg)
![MotorDriverPinOutTable](/assets/MotorDriverPinOutTable.png)
![RedFunction](/assets/RedFunction.png)

### Wire Connection Between Arduino and Motor

Seperate wires are used in between the arduino and motor board.

![WireConnection](/assets/WireConnectionBetweenArduinoAndMotor.jpg)

| Motor Driver | To Arduino          |
|------------- |---------------------|
| brown        | NO Wire             |
| red          | NO Wire             |
| orange       | Red (GND)           |
| yellow       | Yellow (GND)        |
| green        | Green (pin 11 & 10) |
| blue         | NO Wire             |
| purple       | NO Wire             |
| brown (red)  | Brown (5V)          |
| gray         | Gray (pin 7 & 4)    |
| white        | White (pin 6 & 3)   |
| black        | Black (pin 8 & 5)   |
| NC           | NO Wire             |

---

## Vehicle HeadLamps

![VehicleHeadLamp](/assets/vehicle_headlamp.jpg)

The vehicle has 4 lights in total, 2 front and 2 rear. White lights are used on the front whereas red is used at the rear. They can be turned on or off using the transmitter. The lights are controlled electrically by the arduino uno which recieves the light state commands from the receiver.

All 4 of this LED modules (WS2812 5050) are chained togther, thus only needing one data cable to communicate with all 4 of the light modules.

LED PIN: 4

---

## Receiver

The receiver can be found in the box where the power switches and e-stop are located. In there, you will see an Stm32 board and a nrf24 module (antenna). The stm32 board communicates with the transmitter via the nrf24 module using the SPI protocol. Based on the payload (information) recieved from the transmitter, the stm32 will process and send the relevant motor velocities & light commands to the arduino uno via the I2C protocol. The stm32 is also wired to a buzzer which sounds whenever the vehicle is switched to enabled.

> **NOTE:** Arduino uses **5V** logic whereas stm32 uses **3.3V** logic thus a logic level shifter is used between the 2 devices I2C lines (SDA & SCL Pins).

> ⚠️ **WARNING:** When flashing the Stm32 board for the reciever, if you are using 5V power from the flashing device **DISCONNECT** the power pins that receive 5V from the voltage regulator to prevent back feeding power which may **DAMAGE** the voltage regulator. Refer to `SetupGuide.md` for detailed information on how to flash the Stm32.

![STM23pinout](/assets/stm32_pinout.svg)
![Receiverpinout](/assets/receiver_pinout.png)

---

## Transmitter

The transmitter consists of a STM32, a NRF24 wireless module, 2 joysticks, a LCD display, a voltage regulator, a 9v Battery, 4 buttons and 2 switches.

| Component | Function               |
| --------- | ---------------------- |
| Switch 1  | Safety / Arming Switch |
| Switch 2  | Light Switch           |
| Button 1  | Menu / Enter Btn       |
| Button 2  | Up Btn                 |
| Button 3  | Down Btn               |
| Button 4  | Back Btn               |

The diagrams below showcase the electronic circuit used in the transmitter and the relevant pinouts.

> ⚠️ **WARNING:** When flashing the Stm32 board for the transmitter, if you are using 5V power from the flashing device **DISCONNECT** the power pins that receive 5V from the voltage regulator to prevent back feeding power which may **DAMAGE** the voltage regulator. Refer to `SetupGuide.md` for detailed information on how to flash the Stm32.

![TransmitterCircuit](/assets/TransmitterCircuit.svg)

![NRF24pinout](/assets/nrf24_pinout.svg)

![Transmitterpinout](/assets/transmitter_pinout.png)

---
