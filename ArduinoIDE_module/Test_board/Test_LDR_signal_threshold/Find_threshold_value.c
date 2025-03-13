// The code is written in the Arduino IDE environment.
/*
This code reads analog values from 8 LDR sensors, performing 1000 scans per cycle.
For each sensor, it tracks the minimum and maximum readings and then calculates a threshold (the average value).
Finally, it prints the results to the serial monitor and repeats the measurement cycle.
*/

#define LDR_COUNT 8    // Số lượng cảm biến LDR
#define SCAN_COUNT 1000 // Số lần quét ADC
#define DELAY_MS 2     // Thời gian delay giữa mỗi lần đo (2ms)

// Định nghĩa chân GPIO cho các cảm biến LDR
#define INPUT_PIN_1 34
#define INPUT_PIN_2 35
#define INPUT_PIN_3 32
#define INPUT_PIN_4 33
#define INPUT_PIN_5 25
#define INPUT_PIN_6 26
#define INPUT_PIN_7 27
#define INPUT_PIN_8 14

// Mảng chứa các chân nối với LDR theo thứ tự từ LDR1 đến LDR8
int ldrPins[LDR_COUNT] = {INPUT_PIN_1, INPUT_PIN_2, INPUT_PIN_3, INPUT_PIN_4,
                          INPUT_PIN_5, INPUT_PIN_6, INPUT_PIN_7, INPUT_PIN_8};

// Mảng lưu giá trị min, max và threshold (giá trị trung bình) của mỗi LDR
int ldrMin[LDR_COUNT];
int ldrMax[LDR_COUNT];
int threshold[LDR_COUNT];

void setup() {
  Serial.begin(115200);
  // Nếu cần, cấu hình độ phân giải ADC (ESP32 có thể dùng 12-bit => giá trị max 4095)
  // analogReadResolution(12);
}

void loop() {
  // Khởi tạo giá trị min ban đầu là giá trị lớn nhất (dùng 4095 cho ESP32)
  // và max ban đầu là 0 cho mỗi LDR trước mỗi đợt đo
  for (int i = 0; i < LDR_COUNT; i++) {
    ldrMin[i] = 4095;
    ldrMax[i] = 0;
  }
  
  // Quét 1000 lần
  for (int scan = 0; scan < SCAN_COUNT; scan++) {
    for (int i = 0; i < LDR_COUNT; i++) {
      int adcValue = analogRead(ldrPins[i]);
      // Cập nhật giá trị min nếu giá trị đọc được nhỏ hơn
      if (adcValue < ldrMin[i]) {
        ldrMin[i] = adcValue;
      }
      // Cập nhật giá trị max nếu giá trị đọc được lớn hơn
      if (adcValue > ldrMax[i]) {
        ldrMax[i] = adcValue;
      }
    }
    delay(DELAY_MS); // Chờ 2ms giữa các lần đo
  }
  
  // Tính giá trị trung bình (threshold) cho mỗi LDR = (min + max) / 2
  for (int i = 0; i < LDR_COUNT; i++) {
    threshold[i] = (ldrMin[i] + ldrMax[i]) / 2;
  }
  
  // In ra kết quả của 1000 lần đo
  Serial.println("Kết quả đo 1000 lần:");
  Serial.println("LDR\t\tMin\tMax\tThreshold");
  // Nếu muốn in theo thứ tự vật lý (với LDR8 bên trái) có thể thay đổi thứ tự in
  for (int i = 0; i < LDR_COUNT; i++) {
    Serial.print("LDR ");
    Serial.print(i + 1);
    Serial.print(" (Pin ");
    Serial.print(ldrPins[i]);
    Serial.print("):\t");
    Serial.print(ldrMin[i]);
    Serial.print("\t");
    Serial.print(ldrMax[i]);
    Serial.print("\t");
    Serial.println(threshold[i]);
  }
  
  Serial.println("Đã kết thúc đo 500 lần, bắt đầu đợt đo tiếp theo.");
  Serial.println("=============================================");
  
  // Delay trước khi bắt đầu đợt đo mới (tùy chọn)
  delay(3000);
}
