/**
 * @file current_monitor.c
 * @brief Lamp current monitoring — SW-LLR-07..10
 */
#include "current_monitor.h"
#include "channel_ctrl.h"

#define NOMINAL_MA       660U
#define OC_THRESHOLD_MA  726U   /* 110% */
#define OPEN_THRESHOLD   50U
#define OPEN_DEBOUNCE    200U   /* 2 s @ 10 ms */
#define OC_DEBOUNCE      10U    /* 100 ms */

static uint16_t open_cnt[CHANNEL_COUNT];
static uint16_t oc_cnt[CHANNEL_COUNT];

void CurrentMonitor_Process(uint8_t ch, uint16_t current_ma, bool commanded_on)
{
    if (!commanded_on) {
        open_cnt[ch] = 0U;
        oc_cnt[ch] = 0U;
        return;
    }

    if (current_ma < OPEN_THRESHOLD) {
        if (++open_cnt[ch] >= OPEN_DEBOUNCE) {
            Channel_SetFault(ch, FAULT_OPEN);
        }
    } else {
        open_cnt[ch] = 0U;
    }

    if (current_ma > OC_THRESHOLD_MA) {
        if (++oc_cnt[ch] >= OC_DEBOUNCE) {
            Channel_SetFault(ch, FAULT_OVERCURRENT);
            Channel_SetIntensity(ch, 0U);
        }
    } else {
        oc_cnt[ch] = 0U;
    }
}
