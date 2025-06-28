/*
    Algorithm:
        - The robot will move straight if both center sensors detect the line.
        - The robot will turn left if the left sensors detect the line.
        - The robot will turn right if the right sensors detect the line.
        - The robot will stop if all sensors do not detect the line.
    How to caculate the threshold value:
        - The threshold value is the average value of the ADC readings when the sensor detects the line.
        - The threshold value is used to compare with the current ADC readings to determine if the sensor detects the line.
    Note:
        - The threshold values are set based on the environment and the line color.
        - The base speed and the adjustment factor are set based on the robot's performance.
        - The robot may need to adjust the threshold values, the base speed, and the adjustment factor to follow the line correctly.
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
#define INPUT_PIN_8 14

// Định nghĩa chân GPIO cho động cơ
const int motorLeftPin = 15;  // GPIO 15 cho động cơ trái
const int motorRightPin = 4;   // GPIO 4 cho động cơ phải

// Cài đặt cho PWM
const int pwmFreq = 5000;       // Tần số PWM (Hz)
const int pwmResolution = 8;    // Độ phân giải PWM (bit)
// Ngưỡng nhận line cho mỗi LDR
// Nền nhà nâu 
int thresholds[LDR_COUNT] = {2940, 2940, 2940, 2026, 2653, 2853,  2880, 2050};  
//Nền Trắng
//int thresholds[LDR_COUNT] ={1950,2010,2088,1223,1370,1500,1586,2018,1250}:
// Tốc độ cơ bản
int base_speed = 80;

// Hệ số điều chỉnh tốc độ
int max_a = 40; // Hệ số "a" lớn nhất

// Mảng GPIO cảm biến
int vt_adc[] = {INPUT_PIN_1, INPUT_PIN_2, INPUT_PIN_3, INPUT_PIN_4,
                INPUT_PIN_5, INPUT_PIN_6, INPUT_PIN_7, INPUT_PIN_8};

void setup() {
    Serial.begin(115200);

    // Cài đặt GPIO cho các cảm biến
    for (int i = 0; i < LDR_COUNT; i++) {
        pinMode(vt_adc[i], INPUT);
    }
    // Cài đặt PWM cho động cơ
    ledcAttach(motorLeftPin, pwmFreq, pwmResolution);
    ledcAttach(motorRightPin, pwmFreq, pwmResolution);
    delay(3000);
    Serial.println("He thong san sang.");
}

void van_toc(int speed_motor1, int speed_motor2) {
    // Hàm điều khiển tốc độ động cơ
    ledcWrite(motorLeftPin, constrain(speed_motor1, 0, 255));
    ledcWrite(motorRightPin, constrain(speed_motor2, 0, 255));
}

void kiem_tra_line() {
    int sensorState[LDR_COUNT];
    int ldr_values[LDR_COUNT];

    // Đọc giá trị từ các cảm biến LDR
    for (int i = 0; i < LDR_COUNT; i++) {
        ldr_values[i] = analogRead(vt_adc[i]);
        sensorState[i] = (ldr_values[i] > thresholds[i]) ? 1 : 0; // 1: có line, 0: không có line
    }
    // Logic điều khiển xe
    if (sensorState[3] == 1 || sensorState[4] == 1) {
        // Cả hai cảm biến trung tâm (LDR 4 và LDR 5) đều có line -> đi thẳng
        van_toc(base_speed/3, base_speed/3);
    } 
    if (sensorState[7] || sensorState[6] || sensorState[5]) {
      van_toc(5,255);
        // Line nằm ở bên trái
        int a = 0; // Hệ số tăng tốc
        int slow_down = 0; // Hệ số giảm tốc

        if (sensorState[5]) {
          van_toc(5,255);
            a = max_a / 2;
            slow_down = base_speed / 3; // Giảm nhẹ bánh không rẽ
        } if (sensorState[6]) {
          van_toc(5,255);
            a = (3 * max_a) / 4;
            slow_down = base_speed / 2;
        } if (sensorState[7]) {
            a = 3*max_a;
            slow_down =  3*base_speed / 4; // Giảm nhiều hơn để hỗ trợ rẽ gấp
            van_toc(5, 255);
          
        }
        van_toc(base_speed - (a/2) - slow_down, 2*base_speed + 3*a); // Quay trái
    }
    if (sensorState[0] || sensorState[1] || sensorState[2]) {
      van_toc(255,5);
        // Line nằm ở bên phải
        int a = 0; // Hệ số tăng tốc
        int slow_down = 0; // Hệ số giảm tốc

        if (sensorState[2]) {
            a = max_a / 2;
            slow_down = base_speed / 3; // Giảm nhẹ bánh không rẽ
            van_toc(255,5);
        } if (sensorState[1]) {
            a = (3 * max_a) / 4;
            slow_down = base_speed / 2;
            van_toc(255,5);
        } if (sensorState[0]) {
            a = 3*max_a;
            slow_down = 3*base_speed / 4; // Giảm nhiều hơn để hỗ trợ rẽ gấp
            van_toc(255, 5);
        }
        van_toc(2*base_speed + 3*a, base_speed - (a/2) - slow_down); // Quay phải

     }
       bool stop;
      for (int i = 0; i < LDR_COUNT; i++) {
      // Nếu giá trị ADC của LDR vượt qua ngưỡng, tức LDR state = 1
      if (sensorState[i]==1) {
        stop = false;
        break;  // Thoát vòng lặp ngay khi phát hiện có ít nhất 1 LDR state = 1
      }
      else stop = true;
    }

     if(stop){
      van_toc(0,0);
     }
}

void loop() {
    kiem_tra_line(); // Kiểm tra và điều chỉnh theo line
    delay(1);       // Tần số kiểm tra line
}
