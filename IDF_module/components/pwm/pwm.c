#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "pwm.h"

void pwm_init() {
    // Cấu hình timer cho PWM với độ phân giải 8-bit
    ledc_timer_config_t pwm_timer = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_8_BIT,  // Đặt độ phân giải 8-bit
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 5000,
        .clk_cfg = LEDC_AUTO_CLK
    };
    esp_err_t err_timer = ledc_timer_config(&pwm_timer);
    if (err_timer != ESP_OK) {
        printf("Error configuring timer: %s\n", esp_err_to_name(err_timer));
    }

    // Cấu hình kênh PWM cho động cơ A
    ledc_channel_config_t pwm_channel_a = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = PWM_PIN_A,
        .duty = 0,
        .hpoint = 0
    };
    esp_err_t err_channel_a = ledc_channel_config(&pwm_channel_a);
    if (err_channel_a != ESP_OK) {
        printf("Error configuring channel A: %s\n", esp_err_to_name(err_channel_a));
    }

    // Cấu hình kênh PWM cho động cơ B
    ledc_channel_config_t pwm_channel_b = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_1,
        .timer_sel = LEDC_TIMER_0,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = PWM_PIN_B,
        .duty = 0,
        .hpoint = 0
    };
    esp_err_t err_channel_b = ledc_channel_config(&pwm_channel_b);
    if (err_channel_b != ESP_OK) {
        printf("Error configuring channel B: %s\n", esp_err_to_name(err_channel_b));
    }
}

void set_pwm_duty(uint32_t duty_a, uint32_t duty_b) {
    // Thiết lập duty cycle cho động cơ A
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, duty_a);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);

    // Thiết lập duty cycle cho động cơ B
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, duty_b);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1);
}
