#include <ModbusMaster.h>   //thư viện modbus
#include <Wire.h>  // thư viện i2c để hiển thị LCD
#include <LiquidCrystal_I2C.h>  
LiquidCrystal_I2C lcd(0x27,16,2);   // địa chỉ i2c lcd là 0x27
#define DE  3 // chân DE được nối với chân số 3 arduino
#define RE  2 // chân RE được nối với chân số 2 arduino
ModbusMaster node;        
void preTransmission()           
{
  digitalWrite(RE, 1);  //Đưa chân RE lên mức cao           
  digitalWrite(DE, 1);  // Đưa chân DE lên mức cao
}
void postTransmission()
{
  digitalWrite(RE, 0);
  digitalWrite(DE, 0);
}
void setup()
{
  lcd.init();
  lcd.backlight();// bật tắt màn hình LCD
  lcd.print("Hello");
  delay(2000);
  lcd.clear();
  lcd.print("");
  lcd.setCursor(0,1);
  lcd.print("Giao tiep Modbus");
  delay(3000);
  lcd.clear();
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  
  pinMode(4,INPUT);// Chân cảm biến hồng ngoại được nối với chân số 4 arduino

  digitalWrite(RE, 0);//Đưa chân RE xuống mức thấp
  digitalWrite(DE, 0);//Đưa chân DE xuống mức thấp

  Serial.begin(115200);  //tốc độ baud 115200

node.begin(1, Serial);  //Slave có ID là 1
node.preTransmission(preTransmission);  
node.postTransmission(postTransmission);
}
void loop()
{
float value = analogRead(A0);// Gán giá trị cb độ ẩm đất cho biến value
node.writeSingleRegister(0x40000,value);   // lưu giá trị cảm biến đó vào thanh ghi có địa chỉ 0x40000
  
  lcd.setCursor(0,0);
  lcd.print("GTCBD :");
  lcd.print(value);
  int gtcb= digitalRead(4);   // đọc giá trị cảm biến hồng ngoại lưu vào biến gtcb

  if (gtcb == 1)
  {
    node.writeSingleRegister(0x40001,1);// lưu giá trị cảm biến đó vào thanh ghi có địa chỉ 0x40001
    lcd.setCursor(0,1);
    lcd.print("CBHN: 1");
  }
  else
  {
    node.writeSingleRegister(0x40001,0); // lưu giá trị cảm biến đó vào thanh ghi có địa chỉ 0x40001
    lcd.setCursor(0,1);
    lcd.print("CBHN: 0");
  }
  }
