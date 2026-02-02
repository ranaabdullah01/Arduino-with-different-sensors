#include <LiquidCrystal_I2C.h>

#include <DHT.h>
#include<Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
// Pin and sensor type
#define DHTPIN 2       // Digital pin connected to AM2301A (D2)
#define DHTTYPE DHT21


DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

void setup() {
 
 lcd.print(F("AM2301A (DHT21) Test"));
  dht.begin();
   lcd.init();
  
  // Turn on the backlight
  lcd.backlight();
  
  // Print messages to the LCD
  lcd.setCursor(0, 0);          // Set cursor to column 0, row 0
  lcd.print("    Welcome    ");   // Print text
  
  lcd.setCursor(0, 1);          // Move cursor to column 0, row 1
  lcd.print("  Temp Sensor  ");    // Print text

}

void loop() {
  // Wait at least 2 seconds between readings (AM2301A requires this)
  delay(2000);

  // Read humidity (%)
  float humidity = dht.readHumidity();
  // Read temperature (Celsius)

  float tempC = dht.readTemperature();

  // Check if readings failed
  if (isnan(humidity) || isnan(tempC)) {
   lcd.print(F("Failed to read from AM2301A!"));
    return;
  }
  // Print data to lcd Monitor
 lcd.print(F("Hum: "));
 lcd.print(humidity);
 lcd.print(F("%  |  Temp: "));
 lcd.print(tempC);
 lcd.print(F("°C  |  "));


   lcd.clear();
  
  // Line 1: Temperature (centered)
  String tempStr = "Temp: " + String(tempC, 1) + "\x00"+"C";
  lcd.setCursor((16 - tempStr.length()) / 2, 0);
  lcd.print(tempStr);

  // Line 2: Humidity (centered)
  String humStr = "Hum: " + String(humidity, 1) + "%";
  lcd.setCursor((16 - humStr.length()) / 2, 1);
  lcd.print(humStr);
}