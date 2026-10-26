#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define RED_LED 23

// ==============================
// CURRENT DEMO VALUES
// ==============================
float voltage = 5.0;
float current = 0.3;
float power;

// ==============================
// DANGER LIMITS
// ==============================
float voltageLimit = 3.3;
float currentLimit = 0.3;


void setup() {

  // Red LED
  pinMode(RED_LED, OUTPUT);

  // I2C LCD
  Wire.begin(21, 22);

  lcd.init();
  lcd.backlight();

  // Serial Monitor
  Serial.begin(115200);

  // Startup screen
  lcd.setCursor(0, 0);
  lcd.print("CIRCUIT SPARKS");

  lcd.setCursor(0, 1);
  lcd.print("POWER MONITOR");

  delay(2000);
  lcd.clear();
}


void loop() {

  // ==============================
  // POWER CALCULATION
  // ==============================

  power = voltage * current;


  // ==============================
  // DANGER CONDITION
  // ==============================

  bool danger = false;

  // Voltage >= 3.3 OR Current >= 0.3
  if (voltage >= voltageLimit || current >= currentLimit) {
    danger = true;
  }


  // ==============================
  // RED LED CONTROL
  // ==============================

  if (danger == true) {
    digitalWrite(RED_LED, HIGH);
  }
  else {
    digitalWrite(RED_LED, LOW);
  }


  // ==============================
  // LCD LINE 1
  // ==============================

  lcd.setCursor(0, 0);

  lcd.print("V:");
  lcd.print(voltage, 1);

  lcd.print(" I:");
  lcd.print(current, 1);

  lcd.print("A ");


  // ==============================
  // LCD LINE 2
  // ==============================

  lcd.setCursor(0, 1);

  if (danger == true) {

    lcd.print("DANGER P:");
    lcd.print(power, 1);
    lcd.print("W");

  }
  else {

    lcd.print("NORMAL P:");
    lcd.print(power, 1);
    lcd.print("W");
  }


  // ==============================
  // SERIAL MONITOR
  // ==============================

  Serial.print("Voltage: ");
  Serial.print(voltage, 1);

  Serial.print(" V | Current: ");
  Serial.print(current, 1);

  Serial.print(" A | Power: ");
  Serial.print(power, 1);

  Serial.print(" W | ");

  if (danger) {
    Serial.println("DANGER - RED LED ON");
  }
  else {
    Serial.println("NORMAL - RED LED OFF");
  }

  delay(1000);
}