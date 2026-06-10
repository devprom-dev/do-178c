#ifndef WATCHDOG_SVC_H
#define WATCHDOG_SVC_H

#include <stdint.h>

void Watchdog_Init(void);
void Watchdog_Service(uint32_t now_ms);

#endif
