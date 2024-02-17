#define trigger 16 // chân trig cua US-015
#define echo 17 // chân echo cua US-015
#define RL_ON 25
#define PWM 26
float time_go=0,distance=0;
void setup()
{
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(RL_ON,OUTPUT);
  pinMode(PWM,OUTPUT);
  Serial.begin(115200); // Khoi tao cong noi tiep
  digitalWrite(PWM,HIGH);
}
void loop()
{
digitalWrite(trigger,LOW);
delayMicroseconds(2);
digitalWrite(trigger,HIGH); // chân trigger lên mức cao
delayMicroseconds(10); //trễ 10µs
digitalWrite(trigger,LOW); //chân trigger xuống thấp
delayMicroseconds(2);
time_go=pulseIn(echo,HIGH); 
//hàm tính độ rộng xung thu chân ECHO theo thời gian
distance=time_go*346.5*100/1000000/2; 
// vận tốc sóng siêu //âm cỡ ~344m/s
if (distance >=100) //100cm
{
 Serial.print("Khoang Cach: ");
 Serial.print(distance);
 Serial.println("cm");
 Serial.println("BAT BOM");
 digitalWrite(RL_ON,HIGH);
 }
if (distance <=10) //10cm
{
 Serial.print("Khoang Cach: ");
 Serial.print(distance);
Serial.println("cm");
 Serial.println("TAT BOM");
 digitalWrite(RL_ON,LOW);
 }
 if (distance <=0) //100cm
{
 Serial.println("ERROR !");
 digitalWrite(RL_ON,HIGH);
 }
delay(100);
}
