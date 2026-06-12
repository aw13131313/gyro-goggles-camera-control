# Gyro Goggles Camera Control System for RC Surveillance Vehicles

## Overview

This project implements a wearable head-tracking system that enables real-time camera direction control on a remote-controlled (RC) surveillance vehicle. The system utilizes a gyroscope sensor mounted on wearable goggles to capture the user's head movements and translate them into pan and tilt commands for a camera mounted on the RC vehicle.

By providing intuitive camera control through natural head movements, the system enhances remote monitoring, exploration, and surveillance capabilities while improving user immersion and situational awareness.

---

## Features

* Real-time head motion tracking using MPU6050 gyroscope sensor
* Wireless communication using LoRa SX1278 modules
* Camera pan and tilt control using servo motors
* Wearable goggles-based user interface
* Low-latency wireless transmission
* Long-range communication capability
* Portable and low-power embedded system

---

## System Architecture

### Transmitter Unit (Wearable Goggles)

Components:

* Arduino Nano
* MPU6050 Gyroscope Sensor
* LoRa Ra-02 SX1278 (433 MHz)
* Calibration Button
* Battery Supply

Functions:

* Reads head movement data (Yaw and Pitch)
* Processes gyroscope measurements
* Transmits camera control commands wirelessly

### Receiver Unit (RC Vehicle)

Components:

* Arduino Uno
* LoRa Ra-02 SX1278 (433 MHz)
* Pan Servo Motor
* Tilt Servo Motor
* FPV Camera Module

Functions:

* Receives wireless commands from transmitter
* Converts commands into servo movement
* Adjusts camera direction according to user's head movement

### Video Transmission System

Components:

* Raspberry Pi 4B
* OV5647 Camera Module
* HDMI-to-AV Converter
* Eachine TS832 Video Transmitter
* Eachine VR009 FPV Goggles

Functions:

* Captures live video
* Transmits video feed to the operator
* Provides real-time visual feedback

---

## Technologies Used

* Arduino IDE
* C++
* MPU6050
* LoRa SX1278
* Raspberry Pi
* Servo Motor Control
* Wireless Communication
* Embedded Systems
* Internet of Things (IoT)

---

## Testing Parameters

The system was evaluated based on:

* Communication Range
* Transmission Delay
* Power Consumption

Testing environments included:

* Open Field Area
* Vegetated Area
* Dense Building Area

---

## Applications

* Remote Surveillance
* Environmental Monitoring
* Search and Rescue Operations
* Educational Robotics
* Research and Development
* Unmanned Ground Vehicle (UGV) Systems

---

## Documentation

Project documentation includes:

* System Architecture Diagram
* Wiring Diagram
* Flowchart
* Prototype Images
* Testing Results
* Final Thesis Report
* Presentation Slides

---

## Author

Mallyka Aurora Augest

Telecommunications Engineering

State Polytechnic of Malang

2025
