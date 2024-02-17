#include <Servo.h> //Thư viện Servo
Servo myservo; //Khai báo myservo dùng để điều khiển servo
int servo = 6; //Chân servo nối vào chân số 6 trên Arduino

const int trig = 8; //Khai báo chân trig nối với chân số 8 là hằng số
const int echo = 7; //Khai báo chân echo nối với chân số 7 là hằng số

unsigned long thoigian; //Thời gian là kiểu số nguyên
int khoangcach; //Khoảng cách là kiểu số nguyên

void setup()
{
  Serial.begin(9600); //Mở cổng Serial ở 9600

  myservo.attach(servo); //Khởi động servo
  
  pinMode(trig, OUTPUT); //Chân trig xuất tín hiệu
  pinMode(echo, INPUT); //Chân echo nhận tín hiệu
}

void loop()
{
  //Phát xung từ chân trig, độ rộng tối thiểu là 10ms
  digitalWrite(trig,0); //Tắt chân trig
  delayMicroseconds(2); 
  digitalWrite(trig,1); //bật chân trig để phát xung
  delayMicroseconds(10); //Xung có độ rộng là 10 microsecond
  digitalWrite(trig,0);
  
  //Chân echo sẽ nhận xung phản xạ lại
  //Và đo độ rộng xung cao ở chân echo
  thoigian = pulseIn (echo, HIGH);
  
  //Tính khoảng cách đến vật thể (Đơn vị đo là cm)
  //Tốc độ của âm thanh trong không khí là 340 m/s, tương đương 29,412 microSeconds/cm,
  //Do thời gian được tính từ lúc phát tín hiệu tới khi sóng âm phản xạ lại,
  //vì vậy phải chia cho 2
  khoangcach = int (thoigian / 2 / 29.412); 

  if (khoangcach <= 20) //Nếu khoảng cách tới vật nhỏ hơn 20cm
  {
    Serial.println("Có vật");
    myservo.write(180); //Servo quay tới 180 độ
  }
  else
  {
    Serial.println("Không có vật");
    myservo.write(0); //Servo nằm ở 0 độ
  }

  //In lên Serial kết quả
  Serial.print("Khoảng cách: ");
  Serial.print(khoangcach);
  Serial.println("cm");
  
  delay(500);

}
