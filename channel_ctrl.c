/**
 * @file channel_ctrl.c
 * @brief Channel PWM control — implements SW-LLR-05, SW-LLR-06, SW-LLR-12
 * @trace SW-LLR-05, SW-LLR-06, SW-LLR-10, SW-LLR-12
 */
#include "channel_ctrl.h"

static const uint8_t duty_table[6] = {0, 10, 30, 50, 70, 100};
static uint8_t channel_level[CHANNEL_COUNT];
static uint8_t fault_reg[CHANNEL_COUNT];

void Channel_SetIntensity(uint8_t ch, uint8_t level)
{
    if (ch >= CHANNEL_COUNT) {
        return;
    }
    if (level > 5U) {
        level = 5U;
    }
    channel_level[ch] = level;
    PWM_SetDuty(ch, duty_table[level]);
    if (level == 0U) {
        fault_reg[ch] = FAULT_OK;
    }
}

void Failsafe_AllOff(void)
{
    for (uint8_t i = 0U; i < CHANNEL_COUNT; i++) {
        channel_level[i] = 0U;
        PWM_SetDuty(i, 0U);
        fault_reg[i] = FAULT_FAILSAFE;
    }
}

uint8_t Channel_GetFault(uint8_t ch)
{
    return (ch < CHANNEL_COUNT) ? fault_reg[ch] : FAULT_OK;
}

void Channel_SetFault(uint8_t ch, uint8_t code)
{
    if (ch < CHANNEL_COUNT) {
        fault_reg[ch] = code;
    }
}
