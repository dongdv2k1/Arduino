#include "DHT.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include "ArduinoJson.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Thông tin về wifi

//#define ssid "FPT"
//#define password "000000000"
//#define mqtt_server "192.168.1.26"// local broker
//#define ssid "BVH"
//#define password "aaaaaaaa"
//#define mqtt_server "172.20.10.2"// local broker
#define ssid "Duc"
#define password "tldu9760"
#define mqtt_server " 192.168.97.225"// local broker
LiquidCrystal_I2C lcd(0x27, 20, 4); // Địa chỉ i2c của màn hình 20x04

const uint16_t mqtt_port = 1883; //Port của MQTT

#define topic1 "temperature-humidity"

#define DHTPIN 13
#define DHTPIN1 12                                                                                                           
#define D1     19   //lvr  1
#define D2     5    //  2
#define D3     18   //  3
#define D5     35
#define D6     34
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
DHT dht1(DHTPIN1, DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);

float luminance;
float luminance1;
void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(8,0);
  lcd.print("IOT :");
  Serial.begin(115200);

  Wire.begin();
  pinMode(A0, INPUT); //gan A0 cho LDR


  setup_wifi();                             //thực hiện kết nối Wifi
  client.setServer(mqtt_server, mqtt_port); // cài đặt server và lắng nghe client ở port 1883
  client.setCallback(callback);             // gọi hàm callback để thực hiện các chức năng publish/subcribe
  client.subscribe("livingroomLight");
  client.subscribe("bedroomLight");
  client.subscribe("airVent");

  pinMode(D1, OUTPUT); // livingroomLight
  pinMode(D2, OUTPUT); // livingroomAirConditioner
  pinMode(D3, OUTPUT); // television
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
//  pinMode(27, OUTPUT);
  dht.begin();
}

// Hàm kết nối wifi
void setup_wifi()
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // in ra thông báo đã kết nối và địa chỉ IP của ESP8266
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// Hàm call back để nhận dữ liệu
void callback(char *topic, byte *payload, unsigned int length)
{
  //-----------------------------------------------------------------
  //in ra tên của topic và nội dung nhận được
  Serial.print("Co tin nhan moi tu topic: ");
  Serial.println(topic);
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  String message(p);

  if (String(topic) == "livingroomLight")
  {
    if (message == "On")
    {
      digitalWrite(D1, HIGH);
    }
    if (message == "Off")
    {
      digitalWrite(D1, LOW);
    }
  }
  
 if (String(topic) == "bedroomLight")
  {
    if (message == "bedroomLightOn")
    {
      digitalWrite(D2, HIGH);
    }
    if (message == "bedroomLightOFF")
    {
      digitalWrite(D2, LOW);
    }
  }


  if (String(topic) == "airVent")
  {
    if (message == "airVentOn")
    {
      digitalWrite(D3, HIGH);
    }
    if (message == "airVentOff")
    {
      digitalWrite(D3, LOW);
    }
  }
Serial.println(message);
  Serial.write(payload, length);
  Serial.println();
  //-------------------------------------------------------------------------
}

//Hàm reconnect thực hiện kết nối lại khi mất kết nối với MQTT Broker
void reconnect()
{
  while (!client.connected()) // Chờ tới khi kết nối
  {
    String clientId = "ESP8266Client-Mackcest";
    if (client.connect("ESP8266Client-Mackcest")) //kết nối vào broker
    {
        Serial.println("Đã kết nối:");
        //đăng kí nhận dữ liệu từ topic
        client.subscribe("livingroomLight");
        client.subscribe("livingroomAirConditioner");
        client.subscribe("television");
        client.subscribe("bedroomLight");
        client.subscribe("bedroomAirConditioner");
        client.subscribe("airVent");
      }
      else
      {
        // in ra trạng thái của client khi không kết nối được với broker
        Serial.print("Lỗi:, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        // Đợi 5s
        delay(5000);
      }
    }
  }

  unsigned long lastMsg = 0;
  void loop()
  {
    if (!client.connected()){// Kiểm tra kết nối
            reconnect();
    }
    client.loop();

    long now = millis();
    if (now - lastMsg > 1500)   // thoi gian pub du lieu
    {
      lastMsg = now;
      int h = dht.readHumidity();
      int t = dht.readTemperature();
      int h1 = dht1.readHumidity();
      int t1 = dht1.readTemperature();
      luminance = analogRead(D5);
      luminance1 = analogRead(D6);
      if( t > 30 ){
        digitalWrite(32, HIGH);
        delay(200);
        digitalWrite(32, LOW);
        }
      if( t1 > 30 ){
        digitalWrite(33, HIGH);
        delay(200);
        digitalWrite(33, LOW);
        }
      lcd.setCursor(0, 1);
      lcd.print("T:        ");
      lcd.setCursor(3, 1);
      lcd.print(t);
      lcd.setCursor(5, 1);
      lcd.print("C");
      lcd.setCursor(10, 1);
      lcd.print("T1:       ");
      lcd.setCursor(14, 1);
      lcd.print(t1);
      lcd.setCursor(16, 1);
      lcd.print("C");
      lcd.setCursor(0, 2);
      lcd.print("H:        ");
      lcd.setCursor(3, 2);
      lcd.print(h);
      lcd.setCursor(5, 2);
      lcd.print("%");
      lcd.setCursor(10, 2);
      lcd.print("H1:       ");
      lcd.setCursor(14, 2);
      lcd.print(h1);
      lcd.setCursor(16, 2);
      lcd.print("%");
      lcd.setCursor(0, 3);
      lcd.print("L:      ");
      lcd.setCursor(3, 3);
      lcd.print(luminance);
      lcd.setCursor(10, 3);
      lcd.print("L1:      ");
      lcd.setCursor(13, 3);
      lcd.print(luminance1);
      // kiem tra DHT duoc noi dung chan hay k
      if (isnan(h) || isnan(t))
      {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
      }
      if (isnan(h1) || isnan(t1))
      {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
      }
      char tempString[10];
      sprintf(tempString, "%d", t);
      char humiString[10];
      sprintf(humiString, "%d", h);
      char lightString[10];
      sprintf(lightString, "%f", luminance);
      
      char tempString1[10];
      sprintf(tempString1, "%d", t1);
      char humiString1[10];
      sprintf(humiString1, "%d", h1);
      char lightString1[10];
      sprintf(lightString1, "%f", luminance1);
      
      StaticJsonDocument<100> doc;
      doc["Temperature"] = t;
      doc["Humidity"] = h;
      doc["Light"] = luminance;
      doc["Temperature1"] = t1;
      doc["Humidity1"] = h1;
      doc["Light1"] = luminance1;

      char buffer[256];
      serializeJson(doc, buffer);
      client.publish("temperature-humidity", buffer);
      Serial.println(buffer);
    }
  }
 
