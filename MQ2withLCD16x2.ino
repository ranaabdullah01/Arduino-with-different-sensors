#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Change 0x27 to your LCD's address

const int mq2Pin = A0;     // MQ-2 analog pin
const int buzzerPin = 8;   // Buzzer pin
const int ledPin = 9;      // LED pin

int mq2Value = 0;
int threshold = 400;       // Set your gas detection threshold

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Gas Alarm");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  mq2Value = analogRead(mq2Pin);
  
  // Display gas value on LCD
  lcd.setCursor(0, 0);
  lcd.print("Gas Level: ");
  lcd.print(mq2Value);
  lcd.print("   "); // Clear any leftover characters
  
  Serial.print("Gas Level: ");
  Serial.println(mq2Value);

  // Gas alarm logic
  if (mq2Value > threshold) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("!!! GAS ALERT !!!");
    
    // Additional info for Serial Monitor
    Serial.println("GAS DETECTED! ALARM ACTIVATED!");
  } else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Normal          ");
  }

  delay(500); // Update twice per second for better responsiveness
}