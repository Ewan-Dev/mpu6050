#include <mpu6050.h>

#define MPU_ADDRESS 0x68 //  mpu6050 address is 0x69 if AD0 pin is powered -  otherwise it's 0x68

float rawGX, rawGY, rawGZ; // initialise raw gyroscope variables
float dpsGX, dpsGY, dpsGZ; // initialise dps gyroscope variables
float gRoll, gPitch, gYaw; // initialise actual gyroscope variables
double gyroOffsetX, gyroOffsetY, gyroOffsetZ;  // initialise gyroscope offset variables

void setup(){
    Serial.begin(115200); // begin serial communication at 115200 baud
    wakeSensor(MPU_ADDRESS); // wakes sensor from sleep mode
    delay(1000);
    calculateGyroOffset(MPU_ADDRESS, gyroOffsetX, gyroOffsetY, gyroOffsetZ); // provide MPU6050 address and gyroscope values are written to 3 provided variables
}

void loop(){
    readGyroData(MPU_ADDRESS, rawGX, rawGY, rawGZ); // pass MPU6050 address and gyroscope values are written to 3 provided variables
    rawGyroToDPS(rawGX, rawGY, rawGZ, dpsGX, dpsGY, dpsGZ); // provide the 3 raw gyroscope values and returns them in their dps (degrees per second) values

    dpsGX = dpsGX - gyroOffsetX; // adjust gyroscope values to compensate for offset values
    dpsGY = dpsGY - gyroOffsetY;
    dpsGZ = dpsGZ - gyroOffsetZ;

    dpsToAngles(dpsGX, dpsGY, dpsGZ, gPitch, gRoll, gYaw);
    
    Serial.print("gX:");
    Serial.print(gPitch);
    Serial.print("/");
    Serial.print("gY:");
    Serial.print(gRoll);
    Serial.print("/");
    Serial.print("gZ:");
    Serial.println(gYaw);
    
    delay(250); // reads at 4Hz
}
