#define trigPin1 3

#define echoPin1 4

//#define echoPin2 7

//#define trigPin2 8

#define trigPin3 6

#define echoPin3 5

#define vibrator 10

#define vibrator1 8

long duration, distance, RightSensor,BackSensor,FrontSensor,LeftSensor;

 

void setup()

{

Serial.begin (9600);

pinMode(trigPin1, OUTPUT);

pinMode(echoPin1, INPUT);

//pinMode(trigPin2, OUTPUT);

//pinMode(echoPin2, INPUT);

pinMode(trigPin3, OUTPUT);

pinMode(echoPin3, INPUT);

pinMode(vibrator,OUTPUT);

pinMode(vibrator1,OUTPUT);

}

 

void loop() {

SonarSensor(trigPin1, echoPin1);

RightSensor = distance;

/*SonarSensor(trigPin2, echoPin2);

LeftSensor = distance;*/

SonarSensor1(trigPin3, echoPin3);

LeftSensor = distance;

Serial.print(LeftSensor);

Serial.print(” – “);

Serial.print(FrontSensor);

Serial.print(” – “);

Serial.println(RightSensor);

}

void SonarSensor(int trigPin,int echoPin)

{

digitalWrite(trigPin, LOW);

delayMicroseconds(2);

digitalWrite(trigPin, HIGH);

delayMicroseconds(10);

digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);

distance = duration*0.034/2;

 

if(distance<3)

analogWrite(vibrator,0);

else if(distance>=3 && distance<5)

analogWrite(vibrator,255);

else if(distance>=5 && distance<7)

analogWrite(vibrator,210);

else if(distance>=7 && distance<9)

analogWrite(vibrator,180);

else if(distance>=9 && distance<11)

analogWrite(vibrator,150);

else if(distance>=11 && distance<13)

analogWrite(vibrator,100);

else if(distance>=13 && distance<15)

analogWrite(vibrator,80);

else if(distance>=15 && distance<17)

analogWrite(vibrator,60);

else if(distance>=17 && distance<19)

analogWrite(vibrator,30);

else

analogWrite(vibrator,0);

}

void SonarSensor1(int trigPin,int echoPin)

{

digitalWrite(trigPin, LOW);

delayMicroseconds(2);

digitalWrite(trigPin, HIGH);

delayMicroseconds(10);

digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);

distance = duration*0.034/2;

 

if(distance<=3)

analogWrite(vibrator1,0);

else if(distance>3 && distance<5)

analogWrite(vibrator1,70);

else if(distance>=5 && distance<7)

analogWrite(vibrator1,100);

else if(distance>=7 && distance<9)

analogWrite(vibrator1,120);

else if(distance>=9 && distance<11)

analogWrite(vibrator1,150);

else if(distance>=11 && distance<13)

analogWrite(vibrator1,190);

else if(distance>=13 && distance<15)

analogWrite(vibrator1,210);

else if(distance>=15 && distance<17)

analogWrite(vibrator1,220);

else if(distance>=17 && distance<19)

analogWrite(vibrator1,240);

else

analogWrite(vibrator1,255);

}