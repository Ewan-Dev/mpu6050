//MIT License

//Copyright (c) 2025 Ewan McCairn "EwanDev"

//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#ifndef MPU6050_H
#define MPU6050_H

#include <Arduino.h>

int wakeSensor(uint8_t address);

int readGyroData(uint8_t address, float &gX, float &gY, float &gZ);
int readAccelData(uint8_t address, float &aX, float &aY, float &aZ);
int readTempData(uint8_t address, float &temp);

int rawGyroToDPS(float rawGX, float rawGY, float rawGZ, float &dpsGX, float &dpsGY, float &dpsGZ);
int rawAccelToGForce(float rawAX, float rawAY, float rawAZ, float &gForceAX, float &gForceAY, float &gForceAZ);

int dpsToAngles(float dpsGX, float dpsGY, float dpsGZ, float &actGX, float &actGY, float &actGZ);
int calculateGyroOffset(uint8_t address, double &gyroOffsetX, double &gyroOffsetY, double &gyroOffsetZ);
int calculateAnglesFromAccel(float aX, float aY, float aZ, float &pitch, float &roll);
int calculateAccelOffset(uint8_t address, double &accelOffsetX, double &accelOffsetY);

int complementaryFilter(float dpsGyro, float accelAngle, float alpha, float deltaTime, float &filteredAngle);
#endif