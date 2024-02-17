int motorLPWM = 26; 
int motorRPWM = 27; 
int enablePin = 14; 
// thiet lap cac tham so cua PWM
const int freq = 5000;
const int pwmChannel = 0;
const int resolution = 8;
void setup() {
 pinMode(motorLPWM, OUTPUT); 
// thiết lập các chân là OUTPUT
 pinMode(motorRPWM, OUTPUT);
 pinMode(enablePin, OUTPUT);
 
// Cấu hình chức năng chân phát xung PWM
 ledcSetup(pwmChannel, freq, resolution);
 
// gán kênh PWM cho chân được chọn để phát xung
 ledcAttachPin(enablePin, pwmChannel); 
 Serial.begin(115200);
 
// kiểm tra trên terminal
 Serial.print("Testing DC Motor...");
delay(1000);
}
void loop() {
 int Pulse_Width; 
 int data=analogRead(A0);
 Pulse_Width = map(data,0,4095,0,4095);
 
 Serial.println("Dong co quay thuan");
 Serial.print("PWM_Width= ");
 Serial.println(Pulse_Width);
 digitalWrite(motorLPWM, LOW);
 digitalWrite(motorRPWM, HIGH); 
 ledcWrite(pwmChannel, Pulse_Width); 
 }
