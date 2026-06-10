#ifndef MODBUS_SLAVE_H
#define MODBUS_SLAVE_H

#include <stdbool.h>
#include <stdint.h>

bool Modbus_ValidateFrame(const uint8_t *adu, uint16_t len);
bool Modbus_ParseFrame(const uint8_t *adu, uint16_t len);
void Modbus_HandleWrite(uint16_t reg, uint16_t value);
void Modbus_PushRxByte(uint8_t byte);
void Modbus_ProcessRx(uint32_t now_ms);
void Heartbeat_Update(uint32_t now_ms);

uint16_t Modbus_GetRegister(uint16_t reg);

#endif
