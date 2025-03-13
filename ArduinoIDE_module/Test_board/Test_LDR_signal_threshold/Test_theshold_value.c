/*
    Đọc giá trị từ các cảm biến LDR và kiểm tra xem có đường line nào được nhận diện hay không
    Nếu giá trị ADC của LDR lớn hơn ngưỡng thì được coi là có đường line được nhận diện
    Ngưỡng nhận line cho mỗi LDR được lưu trong mảng thresholds
*/
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
int thresholds[LDR_COUNT] = {2978, 3115, 3196, 2196, 2793, 3083,  2980, 2150};  
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

  // Kiểm tra trạng thái của từng LDR và in ra trên cùng 1 dòng:
  // Nếu giá trị ADC > threshold => in "1" (nhận line), ngược lại in "0"
  for (int i = 0; i < LDR_COUNT; i++) {
    if (ldrValues[i] > thresholds[i]) {
      Serial.print("1 ");
    } else {
      Serial.print("0 ");
    }
  }
  
  Serial.println();  // Xuống dòng sau khi in trạng thái của tất cả các LDR
  delay(5);          // Đợi 5ms trước khi thực hiện lần đo tiếp theo
}
