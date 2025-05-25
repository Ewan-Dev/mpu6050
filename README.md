# mpu6050
![MIT License](https://img.shields.io/github/license/Ewan-Dev/mpu6050?color=blue)
Easy-to-use, minimal and lightweight Arduino library for MPU6050s

## 🚀 Usage 
For full example code, check the [`examples/`](./examples) folder.

## 🧑‍💻 Function reference 
> **🚨 I2C error codes:**
> When a function returns an I2C error code, here is the reference:
> ```cpp
> DATA_TOO_LONG_FOR_TRANSMIT_BUFFER = 1,
> ADDRESS_TRANSMIT_NACK = 2,
> DATA_TRANSMIT_NACK = 3,
> OTHER_ERROR = 4,
> TIMEOUT = 5
> ```


## 📖 Functions
###  🔧 Setup
#### `wakeSensor(address);`
- **Parameters**:
  - ```uint8_t address``` – The address of the sensor. (`0x68`or `0x69`)
- **Returns**: I2C error code or 0 (success).
---
###  📉 Read raw values
#### `readGyroData(address, gX, gY, gZ);`
- **Parameters**:
  - `uint8_t address` – The address of the sensor.
  - `float gX, gY, gZ` – Variables passed by reference to store gyroscope values for X, Y, and Z axes.
- **Returns**: I2C error code  or 0 (success).

#### `readAccelData(address, aX, aY, aZ);`
- **Parameters**:
  - `uint8_t address` – The address of the sensor.
  - `float aX, aY, aZ` – Variables passed by reference to store acceleration values for X, Y, and Z axes.
- **Returns**: I2C error code  or 0 (success).

#### `readTempData(address, temp);`
- **Parameters**:
  - `uint8_t address` – The address of the sensor.
  - `float temp` – Variable passed by reference to store temperature value for chip temperature
- **Returns**: I2C error code or 0 (success).
---
###  🧮 Process raw values
#### `rawGyroToDPS(rawGX, rawGY, rawGZ,  dpsGX, dpsGY, dpsGZ);`
- **Parameters**:
  - `float rawGX, rawGY, rawGZ` – Variables passed that already store raw gyroscope values for X, Y, and Z axes.
  - `float dpsGX, dpsGY, dpsGZ` – Variables passed by reference to store processed gyroscope values in dps (degrees per second) for X, Y, and Z axes.
- **Returns**: 0 (success)

#### `rawAccelToGForce(rawAX, rawAY, rawAZ,  gForceAX, gForceAY, gForceAZ);`
- **Parameters**:
  - `float rawAX, rawAY, rawAZ` – Variables passed that already store raw accelerometer values for X, Y, and Z axes.
  - `float gForceAX, gForceAY, gForceAZ` – Variables passed by reference to store processed accelerometer values in g force for X, Y, and Z axes.
- **Returns**: 0 (success)

#### `dpsToAngles(dpsGX, dpsGY, dpsGZ, pitch, roll, yaw);`
- **Parameters**:
  - `float dpsGX, dpsGY, dpsGZ` – Variables passed that already store dps gyroscope for X, Y, and Z axes.
  - `float absGX, absGY, absGZ` – Variables passed by reference to store processed dps values in actual angles for X, Y, and Z axes.
- **Returns**: 0 (success)

#### `calculateGyroOffset(address, gyroOffsetX, gyroOffsetY, gyroOffsetZ);`
- **Parameters**:
  - `uint8_t address` – The address of the sensor.
  - `double gyroOffsetX, gyroOffsetY, gyroOffsetZ` – Variables passed by reference to store gyroscope offset for X, Y and Z axes.
- **Returns**: 0 (success)

#### `calculateAnglesFromAccel(gForceAX, gForceAY, gForceAZ, pitch, roll);`
- **Parameters**:
  - `float gForceAX, gForceAY, gForceAZ` – Variables passed that already store accelerometer g force for X, Y and Z axes.
  - `float roll, pitch` – Variables passed by reference to store accelerometer roll and pitch values.
- **Returns**: 0 (success)


## ⚖️ License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
