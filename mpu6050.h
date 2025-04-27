#ifndef MPU6050_H
#define MPU6050_H

#include <Arduino.h>
#include <Wire.h>

int wakeSensor(uint8_t address);

int readGyroData(uint8_t address, float &gX, float &gY, float &gZ);

#endif