#include <Servo.h>

int nutnhando = 2;
int nutnhanxanh = 3;

int servo = 9;
int vitri = 0;

Servo myservo;

void setup()
{
  myservo.attach(servo);
  myservo.write (0);
  
  Serial.begin(9600);
  pinMode(nutnhando, INPUT_PULLUP);
  pinMode(nutnhanxanh, INPUT_PULLUP);
}


void loop()
{
  int trangthaido = digitalRead(nutnhando);
  int trangthaixanh = digitalRead(nutnhanxanh);
  
  Serial.print("Trạng thái đỏ: ");
  Serial.print(trangthaido);
  Serial.print("    ");
  Serial.print("Trạng thái xanh: ");
  Serial.print(trangthaixanh);
  Serial.print("    ");
  Serial.print("Góc Servo: ");
  Serial.println(vitri);
  delay(200);

  
  if (trangthaido == 0 && trangthaixanh == 1)   //Đỏ bấm, xanh không bấm
  {
    myservo.write (vitri += 10);       //Thay thành vitri += 10 xem kết quả
    if (vitri > 180)
      {
        vitri = 180;
      }
  }

  else if (trangthaixanh == 0 && trangthaido == 1)  //Xanh bấm, đỏ không bấm
  {
    myservo.write (vitri -= 10);
    if (vitri < 0)
      {
        vitri = 0;
      }
  }
  
}
