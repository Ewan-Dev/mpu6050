#include <mpu6050.h>

#define MPU_ADDRESS 0x68 //  mpu6050 address is 0x69 if AD0 pin is powered -  otherwise it's 0x68

float rawGX, rawGY, rawGZ; // initialise raw gyroscope variables
float dpsGX, dpsGY, dpsGZ; // initialise dps gyroscope variables
float gRoll, gPitch, gYaw; // initialise actual gyroscope variables
float rawAX, rawAY, rawAZ; // initialise raw accelerometer variables
float gForceAX, gForceAY, gForceAZ;  // initialise g force accelerometer variables
float aPitch, aRoll; // initialise actual accelerometer variables
double gyroOffsetX, gyroOffsetY, gyroOffsetZ;  // initialise gyroscope offset variables
double accelOffsetX, accelOffsetY, accelOffsetZ;  // initialise accelerometer offset variables

void setup(){
    Serial.begin(115200); // begin serial communication at 115200 baud
    wakeSensor(MPU_ADDRESS); // wakes sensor from sleep mode
    delay(1000);
    calculateGyroOffset(MPU_ADDRESS, gyroOffsetX, gyroOffsetY, gyroOffsetZ); // provide MPU6050 address and gyroscope values are written to 3 provided variables
    calculateAccelOffset(MPU_ADDRESS, accelOffsetX, accelOffsetY);
}

void loop(){
    // dynamically find delta time (Δt/dt)
    static unsigned long lastTime = millis(); // only set once
    unsigned long currentTime = millis(); 
    float dt = (currentTime - lastTime) / 1000; // finds Δt and converts to seconds from milliseconds
    lastTime = currentTime; // last time updated for next loop's calculations

    readGyroData(MPU_ADDRESS, rawGX, rawGY, rawGZ); // pass MPU6050 address and gyroscope values are written to 3 provided variables
    rawGyroToDPS(rawGX, rawGY, rawGZ, dpsGX, dpsGY, dpsGZ); // provide the 3 raw gyroscope values and returns them in their dps (degrees per second) values
    readAccelData(MPU_ADDRESS, rawAX, rawAY, rawAZ); // pass MPU6050 address and accelerometer values are written to 3 provided variables
    rawAccelToGForce(rawAX, rawAY, rawAZ, gForceAX, gForceAY, gForceAZ); // provide the 3 raw accelerometer values and returns them in their g force values
    calculateAnglesFromAccel(gForceAX, gForceAY, gForceAZ, aPitch, aRoll); // uses trigonometry to calculate angles with accelerometer values 

    dpsGX = dpsGX - gyroOffsetX; // adjust gyroscope values to compensate for offset values
    dpsGY = dpsGY - gyroOffsetY;
    dpsGZ = dpsGZ - gyroOffsetZ;

    aPitch = aPitch - accelOffsetX; // adjust accelerometer values to compensate for offset values
    aRoll = aRoll - accelOffsetY;

    // alpha is the weight for the gyroscope compared the accelerometer
    // helps tune the value although common values are 0.95 - 0.98
    // -- GUIDE TO WEIGHTING --
    // The higher the alpha the quicker the responsiveness and less noise 
    // but drift over time more and are more susceptible to gyro bias if offsets are offset
    float alpha = 0.95; 

    float filteredPitch = aPitch;
    float filteredRoll = aRoll;

    complementaryFilter(dpsGX, aPitch, alpha, dt, filteredPitch);
    complementaryFilter(dpsGY, aRoll, alpha, dt, filteredRoll);

    // prints mpu6050 values in the terminal
    Serial.print("filtered pitch:");
    Serial.print(filteredPitch);
    Serial.print("/");
    Serial.print("filtered Roll:");
    Serial.println(filteredRoll);
    
    delay(10); // reads at 4Hz
}

