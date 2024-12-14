/*
Code : Raghav Sharma, Mohammad Saifullah 
Title : Dual Axis Solar Tracking
Date : 11 December 2023 (final)
*/

#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Four LDRs
#define topLeft A0
#define topRight A1
#define bottomLeft A2
#define bottomRight A3

// OLED Screen Parameters
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int avgTop, avgBottom, avgLeft, avgRight, altitudeError, azimuthError, altitude, azimuth, altitudeNew, azimuthNew;

// ADC error tolerance
int tol = 45;

// Angle step for Servo rotation
int step = 3, altitudeStep, azimuthStep;

// Timekeeping
unsigned long elapsed;

// Two Servos: altitude (up-down) & azimuth (left-right)
Servo altitudeMotor, azimuthMotor;

void setup() {
  Serial.begin(9600);

  // Tracking angles (Servos go between 0 and 180 degrees)
  altitude = 90, azimuth = 90;

  // Initialize Servos
  altitudeMotor.attach(9);
  azimuthMotor.attach(10);
  altitudeMotor.write(altitude);
  azimuthMotor.write(azimuth);

  // Turn on screen
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Display allocation failed"));
  }
  delay(2000);
  display.setTextColor(WHITE);

}

void loop() {
  // elapsed = millis();
  
  // Read LDR values
  avgTop = round(0.5*(analogRead(topLeft)+analogRead(topRight)));
  avgBottom = round(0.5*(analogRead(bottomLeft)+analogRead(bottomRight)));
  avgLeft = round(0.5*(analogRead(topLeft)+analogRead(bottomLeft)));
  avgRight = round(0.5*(analogRead(topRight)+analogRead(bottomRight)));

  // Required corrections (maximize ADC values for maximum luminosity; bring erros close to 0)
  altitudeError = avgTop - avgBottom;
  azimuthError = avgLeft - avgRight;

  // Correct Altitude (Up-Down)
  if (abs(altitudeError) > tol) {
    altitudeStep = int(round(altitudeError/abs(altitudeError)) * step);
    altitudeNew = altitude + altitudeStep;
    
    if ((altitudeNew>20) && (altitudeNew<160)) {
      altitude = altitudeNew;
      altitudeMotor.write(altitude);
    }
  }

  // Correct Azimuth (Left-Right)
  if (abs(azimuthError) > tol) {
    azimuthStep = -int(round(azimuthError/abs(azimuthError)) * step);
    azimuthNew = azimuth + azimuthStep;

    if ((azimuthNew>20) && (azimuthNew<160)) {
      azimuth = azimuthNew;
      azimuthMotor.write(azimuth);
    }
  }

  // Display Solar Panel Voltage
  float solar_voltage = 2 * analogRead(A7) * 5 / 1024.0;
  solar_voltage = int(solar_voltage*10)/10.0;

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(7,5);
  display.println("Solar Panel Voltage");
  display.setTextSize(3);
  display.setCursor(12, 29);
  display.print(solar_voltage);
  display.println(" V");
  display.display();

  /*
  elapsed = millis() - elapsed;
  Serial.print("Elapsed Time (ms):");
  Serial.println(elapsed);
  */

  delay(10);
  // ~40 ms elapsed each loop (excluding final delay statement)
}
