/*
  Test 8 LDR with two thresholds (hysteresis)
  – ESP32 ADC 12-bit (0-4095)
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
const int LDR_PINS[LDR_COUNT] = {
  INPUT_PIN_1, INPUT_PIN_2, INPUT_PIN_3, INPUT_PIN_4,
  INPUT_PIN_5, INPUT_PIN_6, INPUT_PIN_7, INPUT_PIN_8
};

int thresholdHigh[LDR_COUNT] = {2978, 3115, 3196, 2196, 2793, 3083, 2980, 2150};

int thresholdLow[LDR_COUNT]  = {2829, 2959, 3036, 2086, 2653, 2929, 2831, 2042};

bool state[LDR_COUNT] = {false,false,false,false,false,false,false,false};

int adcVal[LDR_COUNT];

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < LDR_COUNT; i++) pinMode(LDR_PINS[i], INPUT);
}

void loop() {
  /* Đọc ADC và áp dụng hysteresis */
  for (int i = 0; i < LDR_COUNT; i++) {
    adcVal[i] = analogRead(LDR_PINS[i]);

    if (!state[i] && adcVal[i] > thresholdHigh[i])        // từ 0 → 1
        state[i] = true;
    else if (state[i] && adcVal[i] < thresholdLow[i])     // từ 1 → 0
        state[i] = false;
  }
  /* In 8 giá trị 0/1 trên cùng 1 dòng */
  for (int i = 0; i < LDR_COUNT; i++) {
    Serial.print(state[i] ? "1 " : "0 ");
  }
  Serial.println();
  delay(5);
}
