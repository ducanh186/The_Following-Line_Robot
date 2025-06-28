/*  main.c – phiên bản mới dùng 2 ngưỡng (hysteresis)
 *  ESP-IDF 5.x – robot dò line 8 LDR
 *
 *  – thresholdHigh : ngưỡng vào line
 *  – thresholdLow  : ngưỡng ra line
 *  – state[]       : lưu tình trạng line của từng LDR
 *
 *  Thuật toán điều khiển giữ nguyên ý tưởng cũ:
 *    •  LDR 3-4  (giữa)  : đi thẳng / nhích trái-phải nhỏ
 *    •  LDR 0-2  (bên trái)  : rẽ trái với mức độ tăng dần
 *    •  LDR 5-7  (bên phải) : rẽ phải với mức độ tăng dần
 *    •  Không thấy line    : tiếp tục rẽ theo hướng gần nhất
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "pwm.h"
#include "ldr.h"

/* ---------- NGƯỠNG TRÊN / DƯỚI ---------- */
static const int thresholdHigh[LDR_COUNT] = {2978, 3115, 3196, 2196,
                                             2793, 3083, 2980, 2150};
static const int thresholdLow[LDR_COUNT]  = {2829, 2959, 3036, 2086,
                                             2653, 2929, 2831, 2042};

/* ---------- THÔNG SỐ ĐIỀU KHIỂN ---------- */
#define MAX_SPEED   100          // tốc độ lớn nhất (duty)
#define BASE_SPEED  20           // tốc độ chạy thẳng mặc định

/* ---------- BIẾN TOÀN CỤC ---------- */
static bool sensorState[LDR_COUNT] = {0};   // 0: không line, 1: có line
static int  last_turn_direction    = 0;     // -1 trái | 1 phải | 0 không rẽ

/* ============================================================= */
/*  Đọc ADC -> cập nhật sensorState[] bằng hysteresis            */
static void update_sensor_state(void)
{
    int adc_val;
    for (int i = 0; i < LDR_COUNT; i++)
    {
        /* 4 kênh đầu ở ADC1, 4 kênh sau ở ADC2 */
        adc_oneshot_unit_handle_t unit = (i < 4) ? adc1_handle : adc2_handle;
        adc_oneshot_read(unit, LDR_PINS[i], &adc_val);

        /* áp dụng hai ngưỡng */
        if (!sensorState[i] && adc_val > thresholdHigh[i])
            sensorState[i] = true;           // 0 → 1
        else if (sensorState[i] && adc_val < thresholdLow[i])
            sensorState[i] = false;          // 1 → 0
    }
}

/* ============================================================= */
/*  Tính duty cho 2 bánh dựa vào sensorState[]                   */
static void line_follower(void)
{
    update_sensor_state();

    /* 1. Hai cảm biến trung tâm thấy line → đi thẳng / nhích */
    if (sensorState[3] || sensorState[4])
    {
        last_turn_direction = 0;

        if (sensorState[3] && !sensorState[4])          // hơi lệch trái
            set_pwm_duty(BASE_SPEED - 5, BASE_SPEED + 5);
        else if (sensorState[4] && !sensorState[3])     // hơi lệch phải
            set_pwm_duty(BASE_SPEED + 5, BASE_SPEED - 5);
        else                                            // cả hai đều thấy line
            set_pwm_duty(BASE_SPEED, BASE_SPEED);

        return;
    }

    /* 2. Rẽ trái (line ở cụm 0-2) */
    if (sensorState[0] || sensorState[1] || sensorState[2])
    {
        last_turn_direction = -1;

        int a = 0, b = 0;
        if (sensorState[2])        { a = MAX_SPEED / 2;      b = BASE_SPEED / 2; }
        else if (sensorState[1])   { a = (2 * MAX_SPEED)/3;  b = BASE_SPEED;     }
        else if (sensorState[0])   { a = (3 * MAX_SPEED)/4;  b = BASE_SPEED;     }

        set_pwm_duty(BASE_SPEED - b, BASE_SPEED + a);   // bánh trái chậm, phải nhanh
        return;
    }

    /* 3. Rẽ phải (line ở cụm 5-7) */
    if (sensorState[5] || sensorState[6] || sensorState[7])
    {
        last_turn_direction = 1;

        int a = 0, b = 0;
        if (sensorState[5])        { a = MAX_SPEED / 2;      b = BASE_SPEED / 2; }
        else if (sensorState[6])   { a = (2 * MAX_SPEED)/3;  b = BASE_SPEED;     }
        else if (sensorState[7])   { a = (3 * MAX_SPEED)/4;  b = BASE_SPEED;     }

        set_pwm_duty(BASE_SPEED + a, BASE_SPEED - b);   // bánh phải chậm, trái nhanh
        return;
    }

    /* 4. Không cảm biến nào thấy line → tiếp tục xoay theo hướng cũ */
    if (last_turn_direction == -1)          set_pwm_duty(0, BASE_SPEED * 2);
    else if (last_turn_direction ==  1)     set_pwm_duty(BASE_SPEED * 2, 0);
    else                                    set_pwm_duty(BASE_SPEED / 2, BASE_SPEED / 2);
}

/* ============================================================= */
/*  FreeRTOS task đọc line & điều khiển xe                        */
static void line_follow_task(void *arg)
{
    while (1)
    {
        line_follower();
        vTaskDelay(pdMS_TO_TICKS(5));   // lặp 200 Hz
    }
}

/* ============================================================= */
void app_main(void)
{
    pwm_init();
    adc_init();

    xTaskCreate(line_follow_task, "line_follow_task", 2048, NULL, 5, NULL);
}
