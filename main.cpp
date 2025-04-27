#include <Wire.h>
#include "mpu6050.h"

// enumerate for better readability of addresses
enum MPU6050_Registers : uint8_t{ 
    PWR_MGMT_1  = 0x6B,
};

// wakes sensor from sleep mode
int wakeSensor(uint8_t address)
{
    Wire.beginTransmission(address);
    Wire.write(PWR_MGMT_1); // global power management register
    Wire.write(0x00); // wakes sensor up
    return Wire.endTransmission(true); // returns success/error code
};