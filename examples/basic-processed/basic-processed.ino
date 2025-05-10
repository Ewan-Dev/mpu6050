#include <mpu6050.h>

#define MPU_ADDRESS 0x68 //  mpu6050 address is 0x69 if AD0 pin is powered -  otherwise it's 0x68

float rawGX, rawGY, rawGZ; // initialise raw gyroscope variables
float rawAX, rawAY, rawAZ; // initialise raw accelerometer variables
float dpsGX, dpsGY, dpsGZ; // initialise dps gyroscope variables
float gForceAX, gForceAY, gForceAZ; // initialise g force accelerometer variables

void setup(){
    Serial.begin(115200); // begin serial communication at 115200 baud
    wakeSensor(MPU_ADDRESS); // wakes sensor from sleep mode
}

void loop(){
    readGyroData(MPU_ADDRESS, rawGX, rawGY, rawGZ); // pass MPU6050 address and gyroscope values are written to 3 provided variables
    rawGyroToDPS(rawGX, rawGY, rawGZ, dpsGX, dpsGY, dpsGZ); // provide the 3 raw gyroscope values and returns them in their dps (degrees per second) values
    readAccelData(MPU_ADDRESS, rawAX, rawAY, rawAZ); // pass MPU6050 address and accelerometer values are written to 3 provided variables
    rawAccelToGForce(rawAX, rawAY, rawAZ, gForceAX, gForceAY, gForceAZ); // provide the 3 raw accelerometer values and returns them in their g force values
    Serial.print("gX:");
    Serial.print(dpsGX);
    Serial.print("/");
    Serial.print("gY:");
    Serial.print(dpsGY);
    Serial.print("/");
    Serial.print("gZ:");
    Serial.println(dpsGZ);
    Serial.print("aX:");
    Serial.print(gForceAX);
    Serial.print("/");
    Serial.print("aY:");
    Serial.print(gForceAY);
    Serial.print("/");
    Serial.print("aZ:");
    Serial.println(gForceAZ);
    delay(250); // reads at 4Hz
}