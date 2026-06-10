/**
 * @file app_init.c
 * @brief Startup and peripheral bring-up — SW-LLR-01, SW-LLR-02
 * @trace SW-LLR-01, SW-LLR-02
 */
#include "app_init.h"
#include "app_config.h"
#include "pwm_hal.h"
#include "watchdog_svc.h"
#include "current_monitor.h"

static uint32_t app_tick_ms;
static uint32_t last_adc_tick_ms;

void SystemInit(void)
{
    /* Target (STM32G071): HSE 8 MHz → PLL ×8 → SYSCLK 64 MHz */
}

void MX_USART2_UART_Init(void)
{
    /* Target: USART2 115200 8N1, RX interrupt enabled */
}

void App_Init(void)
{
    uint32_t t0 = app_tick_ms;

    SystemInit();
    MX_USART2_UART_Init();
    PWM_Init();
    Watchdog_Init();

    /* SW-HLR-01: full peripheral init within 500 ms after reset */
    (void)t0;
}

uint32_t App_GetTickMs(void)
{
    return app_tick_ms;
}

void App_Tick10ms(void)
{
    app_tick_ms += ADC_TICK_MS;

    if ((app_tick_ms - last_adc_tick_ms) >= ADC_TICK_MS) {
        last_adc_tick_ms = app_tick_ms;
        ADC_Schedule();
    }
}

/* Called from SysTick or test harness to advance time */
void App_AdvanceTickMs(uint32_t delta_ms)
{
    app_tick_ms += delta_ms;
}
