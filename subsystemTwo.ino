// Home-E : Team Funtastic Four
// SUBSYSTEM 2 - The LCD Display System
// This subsystem receives data ('working' variable) from Subsystem 3 (RFID Tap) via serial communication, which triggers it to display a welcome/denied message.
// This information is further sent to Subsystem 1 (Door latch) as outByte = 1 or 0 via bluetooth, depending on access granted or denied.

#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

const byte rxPin = 9;
const byte txPin = 10;

SoftwareSerial mySerial (rxPin, txPin);

char working[20];
String outByte = "";
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  mySerial.begin(19200);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Home-E");
}

void loop() {
  
  lcd.clear();
  Serial.readBytes(working, 1);
  if (working[0] == '1'){
      lcd.setCursor(0,0);
    lcd.print("Home-E");
    lcd.setCursor(0,1);
    lcd.print("Welcome Home!");
    working[0] = '2';
    outByte = "1";
    mySerial.println(outByte);  // sending data to subsystem 1
  } else if (working[0] == '0'){
      lcd.setCursor(0,0);
    lcd.print("Home-E");
    lcd.setCursor(0,1);
    lcd.print("Access Denied!");
    working[0] = '2';
    outByte = "0";
    mySerial.println(outByte);  // sending data to subsystem 1
  } else {
      lcd.setCursor(0,0);
    lcd.print("Home-E");
    lcd.setCursor(0,1);
    lcd.print("Please Tap");
  }
 
  delay(2500);
  lcd.noBlink();
  lcd.clear();
}
