#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"
#include "ldr.h"

// Định nghĩa mảng các kênh ADC của LDR
const adc_channel_t LDR_PINS[LDR_COUNT] = {
    ADC_CHANNEL_4, // GPIO 32 - ADC1_CHANNEL_4
    ADC_CHANNEL_5, // GPIO 33 - ADC1_CHANNEL_5
    ADC_CHANNEL_6, // GPIO 34 - ADC1_CHANNEL_6
    ADC_CHANNEL_7, // GPIO 35 - ADC1_CHANNEL_7
    ADC_CHANNEL_6, // GPIO 14 - ADC2_CHANNEL_6
    ADC_CHANNEL_7, // GPIO 27 - ADC2_CHANNEL_7
    ADC_CHANNEL_8, // GPIO 25 - ADC2_CHANNEL_8
    ADC_CHANNEL_9  // GPIO 26 - ADC2_CHANNEL_9
};

// Handles của ADC1 và ADC2
adc_oneshot_unit_handle_t adc1_handle, adc2_handle;

void adc_init() {
    esp_err_t ret;

    // Cấu hình cho ADC1
    adc_oneshot_unit_init_cfg_t adc1_config = {
        .unit_id = ADC_UNIT_1
    };
    ret = adc_oneshot_new_unit(&adc1_config, &adc1_handle);
    if (ret != ESP_OK) {
        ESP_LOGE("ADC", "Failed to initialize ADC1: %s", esp_err_to_name(ret));
        return;
    }

    // Cấu hình cho ADC2
    adc_oneshot_unit_init_cfg_t adc2_config = {
        .unit_id = ADC_UNIT_2
    };
    ret = adc_oneshot_new_unit(&adc2_config, &adc2_handle);
    if (ret != ESP_OK) {
        ESP_LOGE("ADC", "Failed to initialize ADC2: %s", esp_err_to_name(ret));
        return;
    }

    // Cấu hình các kênh
    adc_oneshot_chan_cfg_t chan_config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12, // Thay giá trị lỗi thời
    };

    // Cấu hình các kênh của ADC1
    for (int i = 0; i < 4; i++) {
        ret = adc_oneshot_config_channel(adc1_handle, LDR_PINS[i], &chan_config);
        if (ret != ESP_OK) {
            ESP_LOGE("ADC", "Failed to configure ADC1 channel %d: %s", LDR_PINS[i], esp_err_to_name(ret));
        }
    }

    // Cấu hình các kênh của ADC2
    for (int i = 4; i < LDR_COUNT; i++) {
        ret = adc_oneshot_config_channel(adc2_handle, LDR_PINS[i], &chan_config);
        if (ret != ESP_OK) {
            ESP_LOGE("ADC", "Failed to configure ADC2 channel %d: %s", LDR_PINS[i], esp_err_to_name(ret));
        }
    }
}