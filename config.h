#ifndef CONFIG_H
#define CONFIG_H

// Pin definitions
#define ULTRASONIC_PIN 7
#define BUZZER_PIN 8
#define SD_CS_PIN 4  // Standard CS pin for Adafruit SD shield

// Configuration
const int MAX_DISTANCE = 100;  // Max distance in cm
const int MIN_DISTANCE = 5;    // Min distance in cm
const int BAR_COUNT = 14;      // Number of bars in display
const unsigned long LOG_INTERVAL = 1000; // Log every 1000 milliseconds (1 second)

#endif