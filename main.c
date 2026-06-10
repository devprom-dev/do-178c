/**
 * @file main.c
 * @brief Application super-loop — orchestrates modules per SDD-001
 */
#include "app_init.h"
#include "app_config.h"
#include "watchdog_svc.h"
#include "modbus_slave.h"
#include "current_monitor.h"

int main(void)
{
    App_Init();

    for (;;) {
        uint32_t now = App_GetTickMs();

        Watchdog_Service(now);
        Heartbeat_Update(now);
        Modbus_ProcessRx(now);

        /* Target: __WFI() or short delay until next tick */
    }

    return 0;
}

/* 10 ms timer ISR entry — SW-LLR-07 */
void TIM6_DAC_IRQHandler(void)
{
    App_Tick10ms();
}
