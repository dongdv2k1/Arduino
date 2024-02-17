#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <ESP32Servo.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); 
Servo myServo;
int Buzzer = 32;   // còi      
int Gas_analog = 35;    // ga
//int Gas_digital = 34;   //
const uint8_t ROWS = 4; // hàng
const uint8_t COLS = 4; // cột
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

uint8_t colPins[COLS] = { 27, 13, 23, 4 };
uint8_t rowPins[ROWS] = { 33, 25, 26, 14 };

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String Password = "";  // mat khau 

void setup() {
  lcd.init(); // khởi động
  lcd.backlight(); 
  lcd.setCursor(3,0); //(côt, hàng)
  lcd.print("Nhap mat khau :");
  myServo.attach(18);//chân tín hiệu servo
  myServo.write(0);
  pinMode(2,INPUT_PULLUP); // tín hiệu chuyen dong
  pinMode(15, OUTPUT); // led chuyển động
  pinMode(Buzzer, OUTPUT);    // còi  
  pinMode(12, OUTPUT);// led hc 06
  pinMode(5, OUTPUT);
  pinMode(19, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //hc 06 bluetooth
    if (Serial.available()){// kết nối serial cổng com lấy gtri
        char bt; //khai báo biến giá trị
        bt=Serial.read();// đọc giá trị từ serial???
        Serial.println(bt);// in ra cổng com
    if (bt =='a'){
      digitalWrite(5,HIGH); // bật đèn
    }
    else if(bt =='b'){
      digitalWrite(5,LOW);// tắt đèn
    }
    if (bt =='c'){
      digitalWrite(12,HIGH); 
    }
    else if(bt =='d'){
      digitalWrite(12,LOW);
    }
    else if (bt =='e'){
      digitalWrite(19,HIGH); 
    }
    else if(bt =='f'){
      digitalWrite(19,LOW);
    }
  }
 // chuyển động
  int z=digitalRead(2);
  if(z==HIGH){
    digitalWrite(15, HIGH);// led sáng
  }else if(z==LOW){
    digitalWrite(15, LOW);// led tắt
  }
  // ga
  int gassensorAnalog = analogRead(Gas_analog);// đọc giá trị ga
  
  lcd.setCursor(3, 3);
  lcd.print("gas:     ");
  lcd.setCursor(8, 3);
  lcd.print(gassensorAnalog);
  if (gassensorAnalog > 1000) {
    digitalWrite (Buzzer, HIGH) ; //send tone
    delay(200);
    digitalWrite (Buzzer, LOW) ;  //no tone
  }
  // mật khẩu
  char key = keypad.getKey(); // lấy kí tự
  if (key) {
    if (key == '*') {  // xóa kí tự
      if (Password.length() > 0) {
        Password = Password.substring(0, Password.length() - 1);// trừ kí tự từ phải qua
        lcd.setCursor(5, 1);
        lcd.print(Password);
      }
    } else if (key == '#') { // enter
      if (Password == "11111111") {
        lcd.setCursor(7, 2);
        lcd.print("True");
        myServo.write(90);
      } else {
        lcd.setCursor(7, 2);
        lcd.print("False");
      }

      delay(1000); // Đợi 1 giây
      lcd.setCursor(5, 1);
      lcd.print("                "); // Xóa dòng 1
      lcd.setCursor(7, 2);
      lcd.print("     "); // xoa true false
      delay(3000); 
      myServo.write(0);
      Password = "";
    } else {
      Password += key;
      lcd.setCursor(5, 1);
      lcd.print(Password);
    }
  }
}
