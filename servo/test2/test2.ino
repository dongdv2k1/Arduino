#include <Servo.h>

Servo myservo;          
 
int bientro = A0; 
int servo = 9;  

int giatribientro;
int vitriservo;

void setup() 
{
  myservo.attach(servo);

  Serial.begin(9600);
}

void loop() 
{
  giatribientro = analogRead (bientro);
  vitriservo = map (giatribientro,0,1023,0,180);

  myservo.write(vitriservo);
  
  Serial.print("Góc Servo: "); Serial.println(vitriservo);
  //delay(50);

}
