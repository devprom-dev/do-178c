#ifndef CHANNEL_CTRL_H
#define CHANNEL_CTRL_H

#include <stdint.h>

#define CHANNEL_COUNT 10U

#define FAULT_OK         0U
#define FAULT_OPEN       1U
#define FAULT_OVERCURRENT 2U
#define FAULT_FAILSAFE   3U

void Channel_SetIntensity(uint8_t ch, uint8_t level);
void Failsafe_AllOff(void);
uint8_t Channel_GetFault(uint8_t ch);
void Channel_SetFault(uint8_t ch, uint8_t code);

#endif
