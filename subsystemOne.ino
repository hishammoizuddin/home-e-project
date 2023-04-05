// Home-E : Team Funtastic Four
// SUBSYSTEM 1 - The Door Latch System
// This subsystem receives data (inByte = 1) from Subsystem 2 via the HC-O5 Bluetooth module, which triggers the servo motor to open the door.
// It also sends data to Subsystem 4 (outByte = 1 or 0) which further triggers the air freshener dispenser to spray.
#include <Servo.h>
#include <SoftwareSerial.h>

#define rxPin 5
#define txPin 6

SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

Servo servo; 
int count = 0;
String inByte = "";
String outByte = "0";

void setup() {
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  servo.attach(10);
  Serial.begin(9600);
  mySerial.begin(19200);
}

void loop() {
  inByte = mySerial.read();
  if (mySerial.available() > 0) {
    if (inByte == "1") {
      outByte = "1";
      Serial.println(outByte);
      servoStopper();
    }
  }
  exit(0);
}

void servoStopper() {
    if (count == 0) {
    servo.write(0);
    delay(1500);
    servo.write(180);
    delay(1500);
    count = 1;
  } else {exit(0);}
}
