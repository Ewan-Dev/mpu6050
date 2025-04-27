#include <mpu6050.h>
#include <Wire.h>

#define MPU_ADDRESS 0x68 //  mpu6050 address is 0x69 if AD0 pin is powered -  otherwise it's 0x68

float gX, gY, gZ; // initialise gyroscope variables

void setup(){
    Serial.begin(115200); // begin serial communication at 115200 baud
    wakeSensor(MPU_ADDRESS); // wakes sensor from sleep mode
    
}

void loop(){
    readGyroData(MPU_ADDRESS , gX, gY, gZ); // pass MPU6050 address and gyroscope values are written to 3 provided variables
    Serial.print(gX);
    Serial.print("/");
    Serial.print(gY);
    Serial.print("/");
    Serial.println(gZ);
    delay(250); // reads at 4Hz
}