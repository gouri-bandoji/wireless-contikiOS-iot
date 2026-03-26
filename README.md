# wireless-contikiOS-iot
# Contiki-NG Wireless Light Monitoring System

## Overview
This project implements a low-power IoT-based wireless light monitoring system using Contiki-NG and UDP communication between sensor nodes.

The system demonstrates real-time data transmission and processing in a wireless sensor network environment.

## Key Features
- Embedded C development using Contiki-NG
- UDP-based wireless communication
- Light sensor integration
- LED-based feedback system
- Event-driven architecture

## System Architecture
Sender Node → UDP Communication → Receiver Node → LED Control

## Technologies Used
- C Programming
- Contiki-NG OS
- Wireless Sensor Networks
- UDP Communication
- Embedded Systems Design

## How It Works
1. Sender node reads light intensity using onboard sensor
2. Data is transmitted via UDP every 10 seconds
3. Receiver node processes incoming data
4. LEDs indicate light intensity levels:
   - Low → Blue
   - Medium → Green
   - High → Red

## Applications
- Smart lighting systems
- Environmental monitoring
- IoT-based automation
- Wireless sensor networks

## Project Structure
- sender/ → Transmitter code
- receiver/ → Receiver code
- docs/ → System documentation
- images/ → Project visuals
- results/ → Output and observations
