const int trig = 8; 
const int echo = 7; 
const int motor = 9; 

//const int trig = 18; 
//const int echo = 5; 
//const int motor =19;

unsigned long thoigian; 
int khoangcach; 

void setup()
{
  Serial.begin(9600); 
  pinMode(trig, OUTPUT); 
  pinMode(echo, INPUT); 
  pinMode(motor, OUTPUT); 
}

void loop()
{
 
  digitalWrite(trig,0); 
  delayMicroseconds(2); 
  digitalWrite(trig,1); 
  delayMicroseconds(10); 
  digitalWrite(trig,0);


  thoigian = pulseIn (echo, HIGH);
  
  
  khoangcach = int (thoigian / 2 / 29.412); 

    if (khoangcach < 100) {
//      analogWrite(motor, 255);
    ledcWrite(motor, 255);  // 100%
  }
  else if ( 100 <= khoangcach && khoangcach < 200) {
    ledcWrite(motor, 51); // 204 :80%
  }
  else if (200 <= khoangcach && khoangcach < 300) {
    ledcWrite(motor, 127);  //50%
  }
  else if (300 <= khoangcach && khoangcach < 400) {
    ledcWrite(motor, 51); // 20%
  }
  else{ 
    ledcWrite(motor,0);
  }

  Serial.print("Khoảng cách: ");
  Serial.print(khoangcach);
  Serial.println("cm");
}
