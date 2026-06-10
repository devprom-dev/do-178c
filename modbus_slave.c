/**
 * @file modbus_slave.c
 * @brief Modbus RTU slave — SW-LLR-03, SW-LLR-04, SW-LLR-11
 */
#include "modbus_slave.h"
#include "channel_ctrl.h"

static uint16_t heartbeat_reg;
static uint32_t hb_last_change_ms;
static uint32_t hb_last_value;

static uint16_t modbus_crc(const uint8_t *buf, uint16_t len)
{
    uint16_t crc = 0xFFFFU;
    for (uint16_t i = 0U; i < len; i++) {
        crc ^= buf[i];
        for (uint8_t b = 0U; b < 8U; b++) {
            if ((crc & 1U) != 0U) {
                crc = (uint16_t)((crc >> 1) ^ 0xA001U);
            } else {
                crc = (uint16_t)(crc >> 1);
            }
        }
    }
    return crc;
}

bool Modbus_ValidateFrame(const uint8_t *adu, uint16_t len)
{
    if (len < 4U) {
        return false;
    }
    uint16_t rx_crc = (uint16_t)(adu[len - 1U] | ((uint16_t)adu[len - 2U] << 8));
    return modbus_crc(adu, (uint16_t)(len - 2U)) == rx_crc;
}

void Heartbeat_Update(uint32_t now_ms)
{
    if (heartbeat_reg != hb_last_value) {
        hb_last_value = heartbeat_reg;
        hb_last_change_ms = now_ms;
    } else if ((now_ms - hb_last_change_ms) >= 3000U) {
        Failsafe_AllOff();
    }
}
