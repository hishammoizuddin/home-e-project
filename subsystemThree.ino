// Home-E : Team Funtastic Four
// SUBSYSTEM 3 - The RFID Key/tap system.
// This subsystem sends data (welcomeMsg and accessDenied) to Subsystem 2 (LCD Display) via serial communication. It also receives bluetooth signals from the Home-E Mobile app (as bluetoothVar) and further triggers the mechanism to proceed based on successful unlock.

#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>

const byte rxPin = 5;
const byte txPin = 6;

SoftwareSerial mySerial (rxPin, txPin);
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

bool isWorking = false, isAppWorking = false;
char welcomeMsg[4] = "1";
char accessDenied[4] = "0";
char bluetoothVar;

void setup() {
  Serial.begin(9600);
  mySerial.begin(19200);
  SPI.begin();
  mfrc522.PCD_Init();
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);
}


void loop() {
  
  if (mySerial.available() > 0) {
    bluetoothVar = mySerial.read();
    Serial.write(bluetoothVar);
    if (bluetoothVar == '1') {
      isWorking = true;
      Serial.write(welcomeMsg);
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(3, HIGH);
      delay(700);
      digitalWrite(3, LOW);
      isAppWorking = true;
    }
  }

  if (isAppWorking == false) {
  
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return;
    } if ( ! mfrc522.PICC_ReadCardSerial()) {
      return;
    } else {
      
      String finalUID= "";
      
      for (byte i = 0; i < mfrc522.uid.size; i++) {
         finalUID.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
         finalUID.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
        
      finalUID.toUpperCase();
        if ((finalUID.substring(1) == "43 92 12 1C"))  {
        isWorking = true;
        Serial.write(welcomeMsg);
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(3, HIGH);
        delay(700);
        digitalWrite(3, LOW);
      } else   {
        Serial.write(accessDenied);
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(2, HIGH);
        delay(700);
        digitalWrite(2, LOW);
      
      }
    }
  }
}
