#ifndef PWM_HAL_H
#define PWM_HAL_H

#include <stdint.h>

void PWM_Init(void);
void PWM_SetDuty(uint8_t ch, uint8_t duty_percent);

#endif
