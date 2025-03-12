#define INPUT_PIN_1 34
#define INPUT_PIN_2 35
#define INPUT_PIN_3 32
#define INPUT_PIN_4 33
#define INPUT_PIN_5 25
#define INPUT_PIN_6 26
#define INPUT_PIN_7 27
#define INPUT_PIN_8 14

const int LDR_COUNT = 8; 
const int LDR_PINS[LDR_COUNT] = {INPUT_PIN_1, INPUT_PIN_2, INPUT_PIN_3, INPUT_PIN_4, INPUT_PIN_5, INPUT_PIN_6, INPUT_PIN_7, INPUT_PIN_8};
int ldrValues[LDR_COUNT]; // Lưu giá trị ADC của các LDR

// Ngưỡng nhận line cho mỗi LDR
int thresholds[LDR_COUNT] = {2980, 3290, 3380, 2380, 3080, 3530, 3450, 2400}; 

void setup() {
  Serial.begin(115200); // Khởi tạo giao tiếp nối tiếp với tốc độ 115200 bps
  for (int i = 0; i < LDR_COUNT; i++) {
    pinMode(LDR_PINS[i], INPUT);
  }
}

void loop() {
  // Đọc giá trị từ các cảm biến LDR
  for (int i = 0; i < LDR_COUNT; i++) {
    ldrValues[i] = analogRead(LDR_PINS[i]);
  }

  // Kiểm tra nếu giá trị ADC của từng LDR lớn hơn ngưỡng
  for (int i = 0; i < LDR_COUNT; i++) {
    Serial.print("LDR ");
    Serial.print(i + 1);
    Serial.print(": ");
    if (ldrValues[i] > thresholds[i]) {
      Serial.println("Line detected");
    } else {
      Serial.println("No line detected");
    }
  }

  delay(1000); // Đợi 1 giây trước khi đọc lại
}
