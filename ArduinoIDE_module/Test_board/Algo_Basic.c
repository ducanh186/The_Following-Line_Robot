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

// Ngưỡng của các LDR
int thresholds[LDR_COUNT] = {2870, 3220, 3310, 2250, 2830, 3480, 3390, 2370};  

// Tốc độ cơ bản
int base_speed = 20;

// Hệ số điều chỉnh tốc độ
int max_a = 100; // Hệ số "a" lớn nhất

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

    // In giá trị cảm biến và trạng thái ra Serial Monitor
    Serial.print("LDR Values: ");
    for (int i = 0; i < LDR_COUNT; i++) {
        Serial.print(ldr_values[i]);
        Serial.print(" ");
    }
    Serial.println();

    Serial.print("Sensor States: ");
    for (int i = 0; i < LDR_COUNT; i++) {
        Serial.print(sensorState[i]);
        Serial.print(" ");
    }
    Serial.println();

    // Logic điều khiển xe
    if (sensorState[3] == 1 || sensorState[4] == 1) {
        // Cả hai cảm biến trung tâm (LDR 4 và LDR 5) đều có line -> đi thẳng
        van_toc(base_speed, base_speed);
    } else if (sensorState[7] || sensorState[6] || sensorState[5]) {
        // Line nằm ở bên trái
        int a = 0; // Hệ số tăng tốc
        int slow_down = 0; // Hệ số giảm tốc

        if (sensorState[5]) {
            a = max_a / 3;
            slow_down = base_speed / 3; // Giảm nhẹ bánh không rẽ
        } else if (sensorState[6]) {
            a = (2 * max_a) / 3;
            slow_down = base_speed / 3;
        } else if (sensorState[7]) {
            a = max_a;
            slow_down = 2 * base_speed / 3; // Giảm nhiều hơn để hỗ trợ rẽ gấp
        }
        van_toc(base_speed - a - slow_down, base_speed + a); // Quay trái
    } else if (sensorState[0] || sensorState[1] || sensorState[2]) {
        // Line nằm ở bên phải
        int a = 0; // Hệ số tăng tốc
        int slow_down = 0; // Hệ số giảm tốc

        if (sensorState[2]) {
            a = max_a / 3;
            slow_down = base_speed / 3; // Giảm nhẹ bánh không rẽ
        } else if (sensorState[1]) {
            a = (2 * max_a) / 3;
            slow_down = base_speed / 3;
        } else if (sensorState[0]) {
            a = max_a;
            slow_down = 2 * base_speed / 3; // Giảm nhiều hơn để hỗ trợ rẽ gấp
        }
        van_toc(base_speed + a, base_speed - a - slow_down); // Quay phải
    } else {
        // Không có line -
        van_toc(base_speed, 0);
    }
}

void loop() {
    kiem_tra_line(); // Kiểm tra và điều chỉnh theo line
    delay(1);       // Tần số kiểm tra line
}
