// Home-E : Team Funtastic Four
// SUBSYSTEM 4 - The Air Freshener Dispenser system
// This subsystem receives data (inByte = 1 or 0) from the Subsystem 1 (Door Latch) via serial communication, and further triggers the air freshener to spray the mist.

#include <Servo.h> 
#include <SoftwareSerial.h>

#define rxPin 5
#define txPin 6
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

Servo servo; 
int count = 0;
String inByte = "";

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
    if (inByte == "1"){
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
