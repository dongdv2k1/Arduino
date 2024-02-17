#include <HardwareSerial.h>
HardwareSerial SerialPort(2);

void setup() {
  // put your setup code here, to run once:
  SerialPort.begin(9600,SERIAL_8N1,16,17);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(SerialPort.available()){
    String Buffer=SerialPort.readString();
    Serial.print(Buffer);
  }
}
