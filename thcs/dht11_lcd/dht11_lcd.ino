#include "DHT.h" // Thư viện cảm biến
#include <LiquidCrystal_I2C.h> // Thư viện hiển thị LCD
#include <Wire.h> // Thư viện cho chuẩn giao tiếp I2C
#define DHTPIN 4 // Digital pin (IO4) nối với DHT sensor
#define DHTTYPE DHT11 // DHT 11
int totalColumns = 20; // LCD 20x4
int totalRows = 4;
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, totalColumns, totalRows); 
 
// Địa chỉ I2C của LCD20x4 là 0x27
void setup() {
 Wire.begin(); //khởi động I2C
 dht.begin(); //khởi động DHT11
 Serial.begin(115200); 
// tốc độ truyền cổng //serial=115200 baud
 Serial.println("Thuc Hanh Co So PTIT.....");
 Serial.println("Message on LCD 20x4.....");
 Serial.println("DHT11 reading.....");
//********************************************************
// Hiển thị thông tin ban đầu
//********************************************************
 lcd.init(); 
 lcd.backlight(); 
// use to turn on and turn off LCD back light
 lcd.setCursor(0, 0);
 lcd.print(" Thuc Hanh Co So ");
 lcd.setCursor(0,2);
 lcd.print("I2C LCD 20x4 & ESP32");
 delay(5000);
 lcd.clear(); 
lcd.setCursor(0,1);
 lcd.print("I2C Address: 0x27"); 
 delay(1000);
 lcd.setCursor(0,3);
 lcd.print("I2C LCD communicated");
 delay(2000);
 lcd.clear(); 
 }
void loop() {
// Chờ cho cảm biến DHT11 sẵn sàng
//delay(2000)Chuẩn bị cho cảm biến DHT11 sawcn sàng thường 
//mất 2 giây
// Việc đọc nhiệt độ và độ ẩm từ DHT11 thường mất khoảng 
//250 milliseconds!
 float h = dht.readHumidity(); // đọc độ ẩm
 float t = dht.readTemperature(); 
// đọc nhiệt độ dưới dạng độ C (Celsius)- mặc định
 float f = dht.readTemperature(true); 
// đọc nhiệt độ //dưới dạng độ F
 
// (tham số: isFahrenheit = true) 
 if (isnan(h) || isnan(t) || isnan(f)) {
 Serial.println(F("Failed to read from DHT sensor!")); 
 
// Thông báo nếu lỗi đọc dữ liệu xảy ra
 return;
 }
Serial.print("Humidity: ");
 Serial.print(h);
 Serial.println("%"); // in thông báo độ ẩm trên terminal
 
 Serial.print("Temperature: ");
 Serial.print(t);
 Serial.println(" do-C "); 
// in thông báo nhiệt độ trên terminal dưới dạng độ C
 Serial.print("Temperature: ");
 Serial.print(f);
 Serial.println(" do-F"); 
//in thông báo nhiệt độ trên terminal dưới dạng độ F
lcd.setCursor(0,0); 
// in ra thông báo độ ẩm tại cột 0 dòng 0 trên LCD
 lcd.print("Humidity: ");
 lcd.print(h);
 lcd.print("%");
 lcd.setCursor(0,1); 
// in ra thông báo độ ẩm tại cột 0 dòng 1 dưới dạng độ C
 lcd.print("Temp: ");
 lcd.print(t);
 lcd.setCursor(14,1);
 lcd.print("do-C ");
 lcd.setCursor(0,2); 
// in ra thông báo độ ẩm tại //cột 0 dòng 2 dưới dạng độ F
 lcd.print(" ");
 lcd.print(f);
 lcd.setCursor(14,2);
 lcd.print("do-F ");
 }
