#include <mpu6050.h>
#include <Wire.h>

#define MPU_ADDRESS 0x68 //  mpu6050 address is 0x69 if AD0 pin is powered -  otherwise it's 0x68

void setup(){
    Serial.begin(115200); // begin serial communication at 115200 baud
    Serial.println(wakeSensor(MPU_ADDRESS)); // wakes sensor from sleep mode
}

void loop(){
    
}