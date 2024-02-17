#include <ESP32Servo.h>

Servo myServo;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(18);
//  Serial.begin(115200);
//  myServo.write(90);
//  delay(1000);
//  myServo.write(0);                                     
}

void loop() {
  // put your main code here, to run repeatedly:
  myServo.write(90);
  delay(1000);
  myServo.write(0);
}
