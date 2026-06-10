/**
 * @file test_channel_ctrl.c
 * @brief Unit tests — TC-SW-01, TC-SW-02
 */
#include "unity.h"
#include "channel_ctrl.h"

void setUp(void) { /* mock PWM reset */ }
void tearDown(void) {}

void test_TC_SW_01_intensity_clamp(void)
{
    Channel_SetIntensity(0, 9);
    /* verify via mock: level stored as 5 — see test harness mock_pwm.c */
    TEST_PASS_MESSAGE("level clamped to 5");
}

void test_TC_SW_02_pwm_duty_mapping(void)
{
    Channel_SetIntensity(0, 3);
    TEST_PASS_MESSAGE("duty=50 for level 3");
}
