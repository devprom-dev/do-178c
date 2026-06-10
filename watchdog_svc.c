/**
 * @file watchdog_svc.c
 * @brief Independent watchdog feed — SW-LLR-13 / SW-HLR-11
 * @trace SW-LLR-13, SW-HLR-11
 */
#include "watchdog_svc.h"
#include "app_config.h"

static uint32_t last_feed_ms;

void Watchdog_Init(void)
{
    last_feed_ms = 0U;
    /* Target: IWDG prescaler/reload for 1000 ms timeout */
}

static void hal_iwdg_refresh(void)
{
    /* Target: HAL_IWDG_Refresh(&hiwdg); */
}

void Watchdog_Service(uint32_t now_ms)
{
    if ((now_ms - last_feed_ms) >= WATCHDOG_FEED_MS) {
        hal_iwdg_refresh();
        last_feed_ms = now_ms;
    }
}
