#ifndef LDR_H
#define LDR_H

#include "esp_adc/adc_oneshot.h"

#define LDR_COUNT 8

// Mảng các kênh ADC của LDR
extern const adc_channel_t LDR_PINS[LDR_COUNT];

// Handles của ADC1 và ADC2
extern adc_oneshot_unit_handle_t adc1_handle, adc2_handle;

// Hàm cấu hình ADC
void adc_init();

#endif // LDR_H
