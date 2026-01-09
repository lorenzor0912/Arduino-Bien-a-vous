# Radar Sensor with SD Logging

This Arduino project implements an ultrasonic radar system with RGB LCD display, buzzer alerts, and automatic SD card logging of sensor readings.

## Features

- Ultrasonic distance measurement with HC-SR04 sensor
- RGB LCD display showing distance and bar graph
- Visual alerts via color-changing backlight
- Audible alerts via buzzer with distance-based tones
- Automatic logging to SD card every second
- Startup animation and system status indicators

## Hardware Requirements

- Arduino Uno/Nano/Pro Mini
- HC-SR04 Ultrasonic Sensor
- RGB LCD (16x2) with I2C interface
- Buzzer
- Adafruit-compatible SD card shield
- Jumper wires and breadboard

## Pin Configuration

- **Ultrasonic Sensor**: Pin 7 (Digital)
- **Buzzer**: Pin 8 (Digital)
- **SD Card CS**: Pin 4 (Digital)
- **RGB LCD**: Uses I2C (SDA/A4, SCL/A5)

## Functionality

The system continuously measures distance using the ultrasonic sensor and displays:
- Current distance reading on the first line of the LCD
- Bar graph representation on the second line
- Backlight color changes based on distance:
  - Red: < 30cm (Danger zone)
  - Orange: 30-80cm (Caution zone) 
  - Green: > 80cm (Safe zone)
- Buzzer alerts that vary in frequency based on distance
- Automatic logging of distance readings to "radarlog.txt" on SD card every second

## Data Logging Format

The SD card stores data in CSV format:
```
Time(ms),Distance(cm)
1000,15
2000,14
3000,16
...
```

## Dependencies

This project requires the following libraries:
- Wire.h (for I2C communication)
- SPI.h (for SD card communication)
- SD.h (for SD card operations)
- Custom libraries: rgb_lcd.h, Ultrasonic.h
