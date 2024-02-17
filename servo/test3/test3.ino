#include <Servo.h>

int servo = 9;
int vitri = 0;

Servo myservo;


void setup()
{
  myservo.attach(servo);
}


void loop()
{
  for(vitri = 0; vitri < 181; vitri++)
  {
    myservo.write(vitri);
    //delay(10);
  }
  delay (5000);


  for(vitri = 180; vitri > 0; vitri--)
  {
    myservo.write(vitri);
    //delay(10);
  }
  delay(3000);
}
