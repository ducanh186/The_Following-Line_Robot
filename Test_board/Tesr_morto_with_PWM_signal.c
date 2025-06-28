/*
  Su dung PWM de dieu khien toc do cua 2 motor DC
  Su dung ESP32, co the dieu chinh tan so va do phan giai PWM
  Ket noi 2 motor voi ESP32 theo thu tu:
  - Motor trai: GPIO 15 (PWM)
  - Motor phai: GPIO 4 (PWM)
  => Tang duty cycle tu 0 den 255 de tang toc do motor
  => Giam duty cycle tu 255 ve 0 de giam toc do motor
*/
const int pwmFreq = 5000;  // Tần số PWM (Hz)
const int pwmResolution = 8; // Độ phân giải PWM (bit)
const int pwmLedChannel1 = 15; // Kênh PWM cho GPIO 15 -- morto trái
const int pwmLedChannel2 = 4; // Kênh PWM cho GPIO 4 -- morto phải

void setup() {
  // Cấu hình GPIO 15 cho PWM
  ledcAttach(pwmLedChannel1, pwmFreq, pwmResolution);
  // Cấu hình GPIO 4 cho PWM
  ledcAttach(pwmLedChannel2, pwmFreq, pwmResolution);
}

void loop() {
  // Tăng dần chu kỳ xung từ 0 đến 255
  for (int dutyCycle = 0; dutyCycle <=20; dutyCycle++) {
    ledcWrite(pwmLedChannel1, dutyCycle*12); // Cập nhật chu kỳ xung cho GPIO 15
   ledcWrite(pwmLedChannel2, dutyCycle*12); // Cập nhật chu kỳ xung cho GPIO 4
    delay(1); // Đợi 10ms trước khi tăng tiếp
  }

  // Giảm dần chu kỳ xung từ 255 về 0
  for (int dutyCycle = 20; dutyCycle >= 0; dutyCycle--) {
    ledcWrite(pwmLedChannel1, dutyCycle*12); // Cập nhật chu kỳ xung cho GPIO 15
    ledcWrite(pwmLedChannel2, dutyCycle)*12; // Cập nhật chu kỳ xung cho GPIO 4
    delay(1); // Đợi 10ms trước khi giảm tiếp
  }
}
