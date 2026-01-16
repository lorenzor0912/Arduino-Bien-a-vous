# Kaboom Radar MkII

An advanced ultrasonic radar system with LCD display, buzzer alerts, and SD card logging.

## Features

- HC-SR04 ultrasonic sensor for distance measurement
- RGB LCD display with visual feedback
- Configurable buzzer alerts based on distance
- Automatic SD card logging every second
- Enhanced startup sequence with progress animation
- Real-time distance visualization with bar graph
- Improved error handling for SD card operations

## Hardware Requirements

- Arduino Uno/Nano
- HC-SR04 ultrasonic sensor
- RGB LCD (16x2) with I2C interface
- Buzzer
- Adafruit-compatible SD card shield
- Jumper wires

## Pin Connections

- Ultrasonic sensor: Pin 7 (digital)
- Buzzer: Pin 8 (digital)
- SD Card CS: Pin 4 (standard for Adafruit shields)
- LCD: I2C (A4/A5 or SDA/SCL pins)

## Logging Format

The system automatically logs distance readings to "radarlog.txt" on the SD card in CSV format:
- Timestamp (milliseconds since start)
- Date (simulated based on uptime)
- Time (simulated based on uptime)
- Distance (cm)

## Error Handling

- Shows "NO SD CARD!" on LCD if SD card is not detected during startup
- Displays "SD CARD REMOVED!" if SD card is removed during operation
- System continues to function normally without SD card
- All other functionality remains operational regardless of SD card status


## Sommaire

- 📡 [Communications](#communications)
- 🔥 [Test rapide](#test-rapide)

### 📡 Communications
Ici le contenu...

### 🔥 Test rapide
Ça descend bien quand tu cliques sur 🔥 Test rapide ?
