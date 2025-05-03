#ifndef MPU6050_H
#define MPU6050_H

#include <Arduino.h>

int wakeSensor(uint8_t address);

int readGyroData(uint8_t address, float &gX, float &gY, float &gZ);
int readAccelData(uint8_t address, float &aX, float &aY, float &aZ);

#endif