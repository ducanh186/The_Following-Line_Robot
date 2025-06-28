#ifndef PWM_H
#define PWM_H
#include <stdint.h>

#define PWM_PIN_A 4  // Động cơ trái
#define PWM_PIN_B 15 // Động cơ phải 
#define MAX_DUTY  255 

void pwm_init();
void set_pwm_duty(uint32_t duty_a, uint32_t duty_b);

#endif 