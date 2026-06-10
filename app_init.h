#ifndef APP_INIT_H
#define APP_INIT_H

#include <stdbool.h>
#include <stdint.h>

void SystemInit(void);
void MX_USART2_UART_Init(void);
void App_Init(void);

uint32_t App_GetTickMs(void);
void App_Tick10ms(void);
void App_AdvanceTickMs(uint32_t delta_ms);

#endif
