/*
  * Đọc giá trị ADC của các cảm biến LDR
  * Su dung bo chia ap 10k ohm va LDR de doc gia tri ADC
  * Su dung ESP32 ADC co do phan giai 12-bit (0-4095)
  * Ket noi cac chan ADC cua LDR theo thu tu tu phai sang trai
*/
#define LDR_COUNT 8 // Số lượng cảm biến LDR

// Định nghĩa chân GPIO cho các cảm biến LDR
#define INPUT_PIN_1 34
#define INPUT_PIN_2 35
#define INPUT_PIN_3 32
#define INPUT_PIN_4 33
#define INPUT_PIN_5 25
#define INPUT_PIN_6 26
#define INPUT_PIN_7 27
#define INPUT_PIN_8 14 // Bên trái

// Mảng chứa các chân nối theo thứ tự LDR1 -> LDR8
int ldrPins[LDR_COUNT] = {INPUT_PIN_1, INPUT_PIN_2, INPUT_PIN_3, INPUT_PIN_4, INPUT_PIN_5, INPUT_PIN_6, INPUT_PIN_7, INPUT_PIN_8};

void setup() {
  Serial.begin(115200);  // Khởi tạo Serial Monitor với tốc độ 115200 bps
  // Nếu sử dụng ESP32, bạn có thể điều chỉnh độ phân giải ADC nếu cần:
  analogReadResolution(12);
}

void loop() {
  Serial.println("Đọc giá trị ADC của các cảm biến LDR:");
  
  // Vì LDR8 (kết nối với chân INPUT_PIN_8) được đặt ở vị trí tận cùng bên trái,
  // ta in kết quả theo thứ tự từ LDR8 đến LDR1.
  for (int i = LDR_COUNT - 1; i >= 0; i--) {
    int adcValue = analogRead(ldrPins[i]);
    Serial.print("LDR ");
    Serial.print(i + 1);
    Serial.print(" (Pin ");
    Serial.print(ldrPins[i]);
    Serial.print("): ");
    Serial.print(adcValue);
    Serial.print("\t");
  }
  
  Serial.println("\n---------------------------------");
  delay(1000); // Đợi 1 giây trước khi thực hiện lần đọc tiếp theo
}
