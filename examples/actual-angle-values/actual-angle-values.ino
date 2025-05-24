#include <mpu6050.h>

#define MPU_ADDRESS 0x68 //  mpu6050 address is 0x69 if AD0 pin is powered -  otherwise it's 0x68

float rawGX, rawGY, rawGZ; // initialise raw gyroscope variables
float dpsGX, dpsGY, dpsGZ; // initialise dps gyroscope variables
float actGX, actGY, actGZ; // initialise actual gyroscope variables

void setup(){
    Serial.begin(115200); // begin serial communication at 115200 baud
    wakeSensor(MPU_ADDRESS); // wakes sensor from sleep mode
}

void loop(){
    readGyroData(MPU_ADDRESS, rawGX, rawGY, rawGZ); // pass MPU6050 address and gyroscope values are written to 3 provided variables
    rawGyroToDPS(rawGX, rawGY, rawGZ, dpsGX, dpsGY, dpsGZ); // provide the 3 raw gyroscope values and returns them in their dps (degrees per second) values
    dpsToAngles(dpsGX, dpsGY, dpsGZ, actGX, actGY, actGZ);
    Serial.print("actualX:");
    Serial.print(actGX);
    Serial.print("/");
    Serial.print("actualY:");
    Serial.print(actGY);
    Serial.print("/");
    Serial.print("actualZ:");
    Serial.println(actGZ);
    delay(250); // reads at 4Hz
}