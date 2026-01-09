#include <Wire.h>
#include "rgb_lcd.h"
#include "Ultrasonic.h"
#include <SPI.h>
#include <SD.h>
#include "config.h"

// Create objects
Ultrasonic ultrasonic(ULTRASONIC_PIN);
rgb_lcd lcd;

// SD card file object
File dataFile;

// Variables
unsigned long previousMillis = 0;

void setup() {
  // Initialize serial for debugging
  Serial.begin(9600);
  
  // Initialize LCD with 16 columns and 2 rows
  lcd.begin(16, 2);
  lcd.setRGB(0, 255, 255);  // Cyan backlight for startup
  
  // Show startup message
  lcd.print("  KABOOM RADAR");
  lcd.setCursor(0, 1);
  lcd.print("  MkII  [2025]");
  delay(1500);
  
  // Initialize SD card
  lcd.clear();
  lcd.print("  SD Init...");
  if (!SD.begin(SD_CS_PIN)) {
    lcd.setCursor(0, 1);
    lcd.print("SD FAIL!");
    Serial.println("SD card initialization failed!");
    // Continue without SD functionality
  } else {
    lcd.setCursor(0, 1);
    lcd.print("SD OK!");
    Serial.println("SD card initialized successfully!");
    delay(500);
  }
  
  // Animated loading screen
  lcd.clear();
  lcd.print("  Initializing");
  lcd.setCursor(0, 1);
  lcd.print("[              ]");
  
  // Progress bar animation
  for (int i = 0; i < 14; i++) {
    lcd.setCursor(i + 1, 1);
    lcd.write(255);  // Filled block
    
    // Change color as loading progresses
    if (i < 5) {
      lcd.setRGB(0, 255, 255);  // Red
    } else if (i < 10) {
      lcd.setRGB(0, 150, 255);  // Orange
    } else {
      lcd.setRGB(0, 100, 255);  // Green
    }
    
    // Beep sound for each step
    tone(BUZZER_PIN, 1000 + (i * 100), 50);
    delay(150);
  }
  
  // Loading complete message
  lcd.clear();
  lcd.setRGB(0, 255, 0);
  lcd.print("   SYSTEM OK!");
  lcd.setCursor(0, 1);
  lcd.print("  Starting...");
  tone(BUZZER_PIN, 2000, 100);
  delay(300);
  tone(BUZZER_PIN, 2500, 100);
  delay(1000);
  lcd.clear();
  
  // Setup buzzer pin
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  
  // Open file for logging data
  dataFile = SD.open("radarlog.txt", FILE_WRITE);
  if(dataFile) {
    dataFile.println("Time,Distance(cm)");
    dataFile.close();
    Serial.println("Log file created successfully");
  } else {
    Serial.println("Error creating log file");
  }
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Get distance measurement
  long distance = ultrasonic.MeasureInCentimeters();
  
  // Constrain distance to valid range
  distance = constrain(distance, MIN_DISTANCE, MAX_DISTANCE);
  
  // Calculate bar count (more bars = closer object)
  int bars = map(distance, MAX_DISTANCE, MIN_DISTANCE, 0, BAR_COUNT);
  bars = constrain(bars, 0, BAR_COUNT);
  
  // Update LCD backlight color based on distance
  updateBacklightColor(distance);
  
  // Buzzer beeping based on distance
  if (distance < 10) {
    tone(BUZZER_PIN, 2000);
    delay(150);
    noTone(BUZZER_PIN);
    tone(BUZZER_PIN, 1000);
    delay(150);
    noTone(BUZZER_PIN);
  } else if (distance < 15) {
    tone(BUZZER_PIN, 3000);
    delay(20);
    noTone(BUZZER_PIN);
    delay(20);
  } else if (distance < 30) {
    tone(BUZZER_PIN, 2000);
    delay(30);
    noTone(BUZZER_PIN);
    delay(30);
  } else if (distance < 40) {
    tone(BUZZER_PIN, 1800);
    delay(40);
    noTone(BUZZER_PIN);
    delay(40);
  } else if (distance < 70) {
    // Medium: slower beeping
    tone(BUZZER_PIN, 1500);
    delay(50);
    noTone(BUZZER_PIN);
    delay(50);
  } else {
    // Far: no beeping
    noTone(BUZZER_PIN);
    delay(100);
  }
  
  // Display distance on first row
  lcd.setCursor(0, 0);
  lcd.print("Distance:  ");
  
  // Print distance with padding for consistent display
  if (distance < 100) lcd.print(" ");
  if (distance < 10) lcd.print(" ");
  lcd.print(distance);
  lcd.print("cm");
  
  // Display bar graph on second row
  lcd.setCursor(0, 1);
  lcd.print("[");
  
  // Draw filled and empty bars
  for (int i = 0; i < BAR_COUNT; i++) {
    if (i < bars) {
      lcd.write(255);  // Filled block character
    } else {
      lcd.print("-");  // Empty segment
    }
  }
  lcd.print("]");
  
  // Check if it's time to log data to SD card
  if(currentMillis - previousMillis >= LOG_INTERVAL) {
    previousMillis = currentMillis;
    
    // Log distance to SD card
    logToSD(distance);
  }
  
  // Debug output to Serial Monitor
  Serial.print("Distance:  ");
  Serial.print(distance);
  Serial.print("cm | Bars: ");
  Serial.println(bars);
}

// Function to log data to SD card
void logToSD(int distance) {
  dataFile = SD.open("radarlog.txt", FILE_WRITE);
  
  if(dataFile) {
    // Write timestamp and distance to file
    dataFile.print(millis());
    dataFile.print(",");
    dataFile.println(distance);
    dataFile.close();
    Serial.print("Logged: ");
    Serial.print(millis());
    Serial.print("ms, ");
    Serial.print(distance);
    Serial.println("cm");
  } else {
    Serial.println("Error opening log file for writing");
  }
}

// Function to update LCD backlight based on distance
void updateBacklightColor(int distance) {
  if (distance < 30) {
    // Red - danger zone
    lcd.setRGB(255, 0, 0);
  } else if (distance < 80) {
    // Orange/Yellow - caution zone
    lcd.setRGB(255, 165, 0);
  } else {
    // Green - safe zone
    lcd.setRGB(0, 255, 10);
  }
}