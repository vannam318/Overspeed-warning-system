#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x26, 20, 4); // Khai báo màn hình LCD với địa chỉ I2C vàkích thước 20x4
const int potPin = A0; // Đầu vào analog cho cảm biến biến trở
const int motorSpeedPin = 9; // Chân điều khiển tốc độ động cơ
const int buzzerPin = 6; // Chân còi báo
int maximumSpeed = 90; // Tốc độ tối đa
void setup() {
Serial.begin(115200); // Khởi động kết nối Serial
lcd.init(); // Khởi tạo màn hình LCD
lcd.backlight(); // Bật đèn nền cho màn hình LCD
lcd.setCursor(0, 0); // Di chuyển con trỏ đến hàng 0 cột 0 trên LCD
lcd.print("Toc do toi da:"); // Hiển thị thông điệp
// Khai báo chân I/O
pinMode(potPin, INPUT);
pinMode(motorSpeedPin, OUTPUT);
pinMode(buzzerPin, OUTPUT);
}
void loop() {
int potValue = analogRead(potPin); // Đọc giá trị từ cảm biến biến trở (tay ga)
float motorSpeed = map(potValue, 220, 842, 0, 150); // Chuyển đổi giá trị tay ga
thành tốc độ động cơ
// Hiển thị tốc độ trên màn hình LCD
lcd.setCursor(0, 1); // Di chuyển con trỏ đến hàng 1 cột 0 trên LCD
lcd.print("Toc do: "); // Xóa dữ liệu cũ
lcd.setCursor(8, 1); // Di chuyển con trỏ đến cột 8 trên LCD
lcd.print(motorSpeed); // Hiển thị tốc độ mới
lcd.print("km/h"); // Hiển thị đơn vị
int motorSpeedValue = map(motorSpeed, 0, 150, 0, 255); // Chuyển đổi tốc độ thành
giá trị PWM
analogWrite(motorSpeedPin, motorSpeedValue); // Điều khiển tốc độ động cơ
// Kiểm tra và kích hoạt còi báo nếu vượt quá tốc độ tối đa
if (motorSpeed > maximumSpeed) {
digitalWrite(buzzerPin, HIGH);
} else {
digitalWrite(buzzerPin, LOW);
}
void loop() {
if (Serial.available() > 0) { // Kiểm tra xem có dữ liệu nào từ cổng Serial
không
String data = Serial.readStringUntil('\n'); // Đọc dữ liệu từ cổng Serial
cho đến khi gặp ký tự xuống dòng (\n)
if (data.startsWith("Speed Limit ")) { // Kiểm tra xem dữ liệu có bắt đầu
bằng "Speed Limit " không
maximumSpeed = data.substring(12).toInt(); // Cập nhật giới hạn tốc độ từdữ liệu Serial, bỏ qua phần "Speed Limit " và chuyển đổi thành số nguyên
}
}

}