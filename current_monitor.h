#ifndef CURRENT_MONITOR_H
#define CURRENT_MONITOR_H

#include <stdbool.h>
#include <stdint.h>

void ADC_Schedule(void);
void CurrentMonitor_Process(uint8_t ch, uint16_t current_ma, bool commanded_on);

#endif
