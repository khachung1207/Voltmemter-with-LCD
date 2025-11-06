#include <Wire.h>
#define SDA_PIN 21 // Chân SDA
#define SCL_PIN 23 // Chân SCL
#include <LiquidCrystal_I2C.h>
// Khai báo màn hình LCD
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
// Khai báo chân ADC và thông số
const int adcPinVoltage = 36; // Chân ADC đo điện áp/dòng điện (GPIO36)
const int adcPin = 34; // Chân ADC (GPIO34)
const float Vcc = 3.3; // Điện áp cung cấp (3.3V)
const float Rref = 1000.0; // Điện trở tham chiếu (1kΩ)
const int ACS712_PIN = 32;
// Khai báo chân ADC và thông số
// Biến lưu trạng thái nút nhấn và trạng thái màn hình
int buttonstate =0; //trạng thái nút nhấn đầu tiên
int lastbuttonstate=0; //trạng thái nút nhấn trước đó
int lcdstate =0; //trạng thái màn hình
// Khai báo chân nút nhấn
const int BUTTON = 16; //khai báo chân input button
void setup() {
Wire.begin(SDA_PIN, SCL_PIN); // Khởi tạo I2C
Serial.begin(9600); // Khởi động Serial Monitor
lcd.init(); // Khởi động màn hình LCD
lcd.backlight(); // Bật đèn nền LCD
pinMode(BUTTON, INPUT_PULLUP); // Cấu hình chân nút nhấn
}
void loop() {
//lấy nút nhấn tích cực thấp
buttonstate = digitalRead(BUTTON);
if(buttonstate == LOW && lastbuttonstate == HIGH){
lcdstate++;
if(lcdstate > 2) lcdstate = 0;
delay(50);
}

lastbuttonstate = buttonstate; //lưu lại trạng thái nút nhấn
//switch case cho các trường hợp nút nhấn
switch(lcdstate){
lcd.clear();
case 0:
Voltage();
break;
case 1:
Current();
break;
case 2:
Resistance();
break;
default:
lcd.setCursor(0,0);
lcd.print("Click Button");
break;
}
}
// Hàm hiển thị điện áp
void Voltage() {
float total = 0;
float data = 0;
for(int i=0; i<200; i++){
data = analogRead(adcPinVoltage);
total = data + total;
delay(1);
}

total = total / 200;
float voltage = total * 15 * (28205 / 27000) *1.1 / 4096;
lcd.clear();
lcd.setCursor(0, 0); 
lcd.print("Voltage:");
lcd.print(voltage, 2);
lcd.print("V");
}
// Hàm hiển thị dòng điện
void Current() {
float voltotal = 0;
float data1 =0;
for ( int i=0; i<200; i++){
data1 = analogRead(ACS712_PIN);
voltotal = voltotal + data1;
delay(1);
}
float voltage = voltotal / 200;
voltage = voltage /4095 *3.3;
float currentvalue = (voltage - 2.5)/0.185 + 0.81333;
delay(1000);
lcd.clear();
lcd.setCursor(0, 0); 
lcd.print("Current:");
lcd.print(currentvalue, 2);
lcd.print("mA");
delay(1);
}
// Hàm hiển thị giá trị điện trở
void Resistance() {
float data = 0;
float total = 0;
for(int i=0; i<100; i++){
data = analogRead(adcPin);
total = data + total;
delay(1);
}
float adcValue = total / 100;
float Vout = adcValue * Vcc / 4095;
float Rx = Rref * (Vout / (Vcc - Vout)) * 1.2;
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Resistance:"); 
lcd.print(Rx, 1);
lcd.print(" ohm");
delay(1000);
}