/**
 * @file pwm_hal.c
 * @brief TIM3 PWM backend — SW-LLR-06
 * @trace SW-LLR-06
 */
#include "pwm_hal.h"

static uint8_t pwm_duty[10U];

void PWM_Init(void)
{
    for (uint8_t i = 0U; i < 10U; i++) {
        pwm_duty[i] = 0U;
    }
    /* Target: TIM3 @ 25 kHz on STM32G071 — configured in app_init.c / CubeMX */
}

void PWM_SetDuty(uint8_t ch, uint8_t duty_percent)
{
    if (ch < 10U) {
        pwm_duty[ch] = duty_percent;
    }
    /* Target: __HAL_TIM_SET_COMPARE(&htim3, ch, duty_percent); */
}
