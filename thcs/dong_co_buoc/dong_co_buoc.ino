//* Điều khiển động cơ bước 28BYJ-48 -5Vdc
#include <Stepper.h>
const int stepsPerRevolution = 32; 
// thư viện Stepper điều khiển full step
const int GearedStepsPerRev = 2048; 
//32*64 do có hộp giảm tốc 1/64
// Khởi tạo thư viện trên các chân 16, 17, 18, 19
Stepper myStepper(stepsPerRevolution, 17,19,16,18); 
// chú ý thứ tự phải đúng
void setup() {
 
 myStepper.setSpeed(120); 
// Đặt tốc độ ở 120 vòng/phút
 Serial.begin(115200); 
// Khởi tạo cổng nối tiếp
}
void loop() {
 Serial.println("clockwise"); 
// Quay 1 vòng theo chiều kim đồng hồ
 myStepper.step(GearedStepsPerRev);
 delay(500); 
// nghỉ 0,5 giây
 Serial.println("counterclockwise"); 
// Quay 1 vòng ngược chiều kim đồng hồ
 myStepper.step(-GearedStepsPerRev);
 delay(500); 
// nghỉ 0,5 giây
}
