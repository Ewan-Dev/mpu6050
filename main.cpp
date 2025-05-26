// Copyright (c) 2025 Ewan McCairn "EwanDev" - MIT License

#include <Wire.h>
#include <stdint.h> 
#include "mpu6050.h" 

// enumeration for better readability of addresses
// these values are according to the MPU6050 data sheet
enum MPU6050_Registers : uint8_t
{ 
    PWR_MGMT_1  = 0x6B, // power management 1 (global)
    GYRO_XOUT_H = 0x43, // x-axis gyroscope - high byte
    ACCEL_XOUT_H = 0x3B, // x-axis accelerometer - high byte
    TEMP_OUT_H = 0x41 // temperature - high byte
};

// enumeration for better readability of I2C errors
enum I2C_Errors: uint8_t
{
    DATA_TOO_LONG_FOR_TRANSMIT_BUFFER = 1,
    ADDRESS_TRANSMIT_NACK = 2,
    DATA_TRANSMIT_NACK = 3,
    OTHER_ERROR = 4,
    TIMEOUT = 5
};
// wakes sensor from sleep mode
int wakeSensor(uint8_t address)
{
    Wire.begin();
    Wire.beginTransmission(address);
    Wire.write(PWR_MGMT_1); // global power management register
    Wire.write(0x00); // wakes sensor up
    uint8_t error =  Wire.endTransmission(true); // returns success/error code
    
    // I2C error are checked for and returned
    switch(error)
    {
        case 0: break; // success
        case 1: return DATA_TOO_LONG_FOR_TRANSMIT_BUFFER;
        case 2: return ADDRESS_TRANSMIT_NACK;
        case 3: return DATA_TRANSMIT_NACK;
        case 5: return TIMEOUT;
        default: return OTHER_ERROR; // case 4 is also OTHER_ERROR
    };

    return 0;
};

// reads gyroscope data
 int readGyroData(uint8_t address, float &gX, float &gY, float &gZ)

 {
    Wire.beginTransmission(address); 
    Wire.write(GYRO_XOUT_H); // used as starting address to read all other values
    uint8_t error = Wire.endTransmission(false); // stores success/error code in variable and keeps sensor active as we need to read data

    // I2C error are checked for and returned
    switch(error)
    {
        case 0: break; // success
        case 1: return DATA_TOO_LONG_FOR_TRANSMIT_BUFFER;
        case 2: return ADDRESS_TRANSMIT_NACK;
        case 3: return DATA_TRANSMIT_NACK;
        case 5: return TIMEOUT;
        default: return OTHER_ERROR; // case 4 is also OTHER_ERROR
    };

    Wire.requestFrom(address, 6, true); // requests 6 bytes - 3 high values and 3 low values from given address
    if (Wire.available() < 6) // check if at least all 6 bytes are sent
    {     
        return DATA_TRANSMIT_NACK; // not enough data sent from MPU6050
    };

    // reads high (most significant) byte,
    // shifts 8 places to make room for low byte
    // and then bitwise OR combines the low (least significant) byte to form a 2 byte gyroscope value
    float rawGyroX = Wire.read() << 8 | Wire.read(); 
    float rawGyroY = Wire.read() << 8 | Wire.read();
    float rawGyroZ = Wire.read() << 8 | Wire.read();

    gX = rawGyroX;
    gY = rawGyroY;
    gZ = rawGyroZ;
    return 0;
 };

// reads accelerometer data
 int readAccelData(uint8_t address, float &aX, float &aY, float &aZ)
 {
    Wire.beginTransmission(address);
    Wire.write(ACCEL_XOUT_H); // used as starting address to read all other values
    uint8_t error = Wire.endTransmission(false); // stores success/error code in variable and keeps sensor active as we need to read data

    // I2C error are checked for and returned
    switch (error)
    {
    case 0: break; // success
    case 1: return DATA_TOO_LONG_FOR_TRANSMIT_BUFFER;
    case 2: return ADDRESS_TRANSMIT_NACK;
    case 3: return DATA_TRANSMIT_NACK;
    case 4: return OTHER_ERROR;
    case 5: return TIMEOUT;
    default: return OTHER_ERROR; // case 4 is also OTHER_ERROR
    };

    Wire.requestFrom(address, 6, true); // requests 6 bytes - 3 high values and 3 low values from given address
        if (Wire.available() < 6) // check if at least all 6 bytes are sent
        {     
            return DATA_TRANSMIT_NACK; // not enough data sent from MPU6050
        };

    // reads high (most significant) byte,
    // shifts 8 places to make room for low byte
    // and then bitwise OR combines the low (least significant) byte to form a 2 byte accelerometer value
    float rawAccelX = Wire.read() << 8 | Wire.read(); 
    float rawAccelY = Wire.read() << 8 | Wire.read();
    float rawAccelZ = Wire.read() << 8 | Wire.read();

    aX = rawAccelX;
    aY = rawAccelY;
    aZ = rawAccelZ;
    return 0;
};

// reads temperature data
 int readTempData(uint8_t address, float &temp)
 {
    Wire.beginTransmission(address);
    Wire.write(TEMP_OUT_H);
    uint8_t error = Wire.endTransmission(false);

    // I2C error are checked for and returned
    switch (error)
    {
    case 0: break; // success
    case 1: return DATA_TOO_LONG_FOR_TRANSMIT_BUFFER;
    case 2: return ADDRESS_TRANSMIT_NACK;
    case 3: return DATA_TRANSMIT_NACK;
    case 4: return OTHER_ERROR;
    case 5: return TIMEOUT;
    default: return OTHER_ERROR; // case 4 is also OTHER_ERROR
    };

    Wire.requestFrom(address, 6, true); // requests 6 bytes - 3 high values and 3 low values from given address
        if (Wire.available() < 6) // check if at least all 6 bytes are sent
        {     
            return DATA_TRANSMIT_NACK; // not enough data sent from MPU6050
        };
    
    // reads high (most significant) byte,
    // shifts 8 places to make room for low byte
    // and then bitwise OR combines the low (least significant) byte to form a 2 byte temperature value
    float rawTemp = Wire.read() << 8 | Wire.read(); 

    temp = rawTemp;
    return 0;
 };


// calculates gyroscope values to º/s at ±250º/s 
int rawGyroToDPS(float rawGX, float rawGY, float rawGZ, float &dpsGX, float &dpsGY, float &dpsGZ)
{
    dpsGX = rawGX / 131.0; // calculates gyroscope values to º/s at ±250º/s according to data sheet
    dpsGY = rawGY / 131.0;
    dpsGZ = rawGZ / 131.0;
    return 0;
};

// calculates accelerometer values to g units º/s at ±2g 
int rawAccelToGForce(float rawAX, float rawAY, float rawAZ, float &gForceAX, float &gForceAY, float &gForceAZ)
{
    gForceAX = rawAX / 16384.0; // calculates accelerometer values to g force units at ±2g according to data sheet
    gForceAY = rawAY / 16384.0;
    gForceAZ = rawAZ / 16384.0;
    return 0;
};

int dpsToAngles(float dpsGX, float dpsGY, float dpsGZ, float &actGX, float &actGY, float &actGZ)
{
    static unsigned long previousTime = millis(); // initialises variable in function scope for first function call
    unsigned long currentTime = millis(); // called every time function is called to get current time in seconds
    float deltaTime = (currentTime - previousTime) / 1000.0; // time elapsed since last call
    previousTime = currentTime; // updates previous time for next time function runs
    
    // º/s = degrees / seconds
    actGX += dpsGX * deltaTime; // times degrees per second value by seconds passed during reading to get degrees value
    actGY += dpsGY * deltaTime;
    actGZ += dpsGZ * deltaTime;
    return 0;
};

int calculateGyroOffset(uint8_t address, double &gyroOffsetX, double &gyroOffsetY, double &gyroOffsetZ)
{
    float gX, gY, gZ;  //  raw gyroscope value variables
    float dpsGX, dpsGY, dpsGZ;  //  dps gyroscope value variables
    gyroOffsetX = 0;
    gyroOffsetY = 0;
    gyroOffsetZ = 0;

    // assumes gyroscope is placed level and then offset values are calculated
    for (int i = 0; i < 100; i++) 
    {
        readGyroData(address, gX, gY, gZ);
        rawGyroToDPS(gX, gY, gZ, dpsGX, dpsGY, dpsGZ);
        
        gyroOffsetX += dpsGX;
        gyroOffsetY += dpsGY;
        gyroOffsetZ += dpsGZ;
    };
    gyroOffsetX = gyroOffsetX / 100; // calculates average from 100 values
    gyroOffsetY = gyroOffsetY / 100;
    gyroOffsetZ = gyroOffsetZ / 100;
    return 0;
};

int calculateAnglesFromAccel(float aX, float aY, float aZ, float &pitch, float &roll) {
    // use trigonometry to calculate angles from accelerometer values then convert the values from radians to degrees
    pitch = atan2(-aX, sqrt(pow(aY, 2) + pow(aZ,2))) * RAD_TO_DEG; 
    roll  = atan2(aY, aZ) * RAD_TO_DEG;
    return 0;
};

int calculateAccelOffset(uint8_t address, double &accelOffsetX, double &accelOffsetY)
{
    float aX, aY, aZ;  // raw accelerometer value variables
    float gForceAX, gForceAY, gForceAZ; // initialise g force accelerometer variables
    float aPitch, aRoll; // initialise actual accelerometer variables
    accelOffsetX = 0;
    accelOffsetY = 0;

    // assumes gyroscope is placed level and then offset values are calculated
    for (int i = 0; i < 100; i++) 
    {
        readAccelData(address, aX, aY, aZ); // pass MPU6050 address and accelerometer values are written to 3 provided variables
        rawAccelToGForce(aX, aY, aZ, gForceAX, gForceAY, gForceAZ); // provide the 3 raw accelerometer values and returns them in their g force values
        calculateAnglesFromAccel(gForceAX, gForceAY, gForceAZ, aPitch, aRoll); // uses trigonometry to calculate angles with accelerometer values

        accelOffsetX += aPitch; // accumulate values 100 times
        accelOffsetY += aRoll;
    };
    accelOffsetX = accelOffsetX / 100; // calculates average from 100 values
    accelOffsetY = accelOffsetY / 100;
    return 0;
};

int complementaryFilter(float dpsGyro, float accelAngle, float alpha, float deltaTime, float &filteredAngle)
{
    filteredAngle = alpha * (filteredAngle + dpsGyro * deltaTime) + (1 - alpha) * accelAngle; // implements a complementary filter as found here: https://www.geekmomprojects.com/gyroscopes-and-accelerometers-on-a-chip/
    return 0;
};
