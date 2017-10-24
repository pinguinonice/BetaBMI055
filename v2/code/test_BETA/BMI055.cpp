// BMI055 I2C Class source
// 2013/11/05 by Bernhardt Schaefer, boen82@gmail.com
// Datasheet: http://www.bosch-sensortec.com/en/homepage/products_3/6_axis_sensors_2/inertial_measurement_unit_1/bmi055_1/bmi055
// http://ae-bst.resource.bosch.com/media/products/dokumente/bmi055/BST-BMI055-DS000-06.pdf
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
//     2013/11/05 - initial release

/* ======================= ====================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2011 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/

#include "BMI055.h"

/*
 Default Constructor
 */
BMI055::BMI055() {
  devAddrAcc  = BMI055_ACC_ADDRESS;
  devAddrGyr  = BMI055_GYR_ADDRESS;
}

/*
Specific Address Constructor
 */
BMI055::BMI055(uint8_t addressAcc, uint8_t addressGyro) {
  devAddrAcc  = addressAcc;
  devAddrGyr  = addressGyro;
}

/*
Initialize with max Range for Acc and Gyro
 */
void BMI055::initialize() {
  setRangeAcc(BMI055_ACC_RANGE_16G);
  setRangeGyr(BMI055_GYR_RANGE_2000);
  // setBandwidth();
}

/*
 Verify the I2C connection.
 Make sure the device is connected and responds as expected.
 True if connection is valid, false otherwise.
 This registers are used to verify the identity of the device
 BMI055_ACC_BGW_CHIPID		= 0xFA
 BMI055_GYR_CHIP_ID		= 0x0F
 */
bool BMI055::testConnection() {
  return ((getDeviceIDAcc() == 0xFA) && (getDeviceIDGyr() == 0x0F));
}

uint8_t BMI055::getDeviceIDAcc() {
  I2Cdev::readByte(devAddrAcc, BMI055_ACC_BGW_CHIPID, buffer);
  return buffer[0];
}

uint8_t BMI055::getDeviceIDGyr() {
  I2Cdev::readByte(devAddrGyr, BMI055_GYR_CHIP_ID, buffer);
  return buffer[0];
}

/*
Set Acc Full Range
 0011 = +-2g
 0101 = +-4g
 1000 = +-8g
 1100 = +-16g
 */
void BMI055::setRangeAcc(uint8_t range) {
  I2Cdev::writeBits(devAddrAcc, BMI055_ACC_PMU_RANGE, BMI055_ACC_RANGE_BIT, BMI055_ACC_RANGE_LENGTH, range);
}

/*
Set Gyr Full Range
 000 = +-2000°/s
 001 = +-1000°/s
 010 = +- 500°/s
 011 = +- 250°/s
 100 = +- 125°/s
 */
void BMI055::setRangeGyr(uint8_t range) {
  I2Cdev::writeBits(devAddrGyr, BMI055_GYR_RANGE, BMI055_GYR_RANGE_BIT, BMI055_GYR_RANGE_LENGTH, range);
}

void BMI055::setBandwidthAcc(uint8_t bandwidth) {
  I2Cdev::writeBits(devAddrAcc, BMI055_ACC_PMU_BW, BMI055_ACC_BW_BIT, BMI055_ACC_BW_LENGTH, bandwidth);
}

void BMI055::setBandwidthGyr(uint8_t bandwidth) {
  I2Cdev::writeBits(devAddrGyr, BMI055_GYR_BW, BMI055_GYR_BW_BIT, BMI055_GYR_BW_LENGTH, bandwidth);
}

uint8_t BMI055::getBandwidthAcc() {
  I2Cdev::readBits(devAddrAcc, BMI055_ACC_PMU_BW, BMI055_ACC_BW_BIT, BMI055_ACC_BW_LENGTH, buffer);
  return buffer[0];
}

uint8_t BMI055::getBandwidthGyr() {
  I2Cdev::readBits(devAddrGyr, BMI055_GYR_BW, BMI055_GYR_BW_BIT, BMI055_GYR_BW_LENGTH, buffer);
  return buffer[0];
}

uint8_t BMI055::getRangeAcc() {
  I2Cdev::readBits(devAddrAcc, BMI055_ACC_PMU_RANGE, BMI055_ACC_RANGE_BIT, BMI055_ACC_RANGE_LENGTH, buffer);
  return buffer[0];
}

uint8_t BMI055::getRangeGyr() {
  I2Cdev::readBits(devAddrGyr, BMI055_GYR_RANGE, BMI055_GYR_RANGE_BIT, BMI055_GYR_RANGE_LENGTH, buffer);
  return buffer[0];
}

void BMI055::getAcceleration(uint8_t* axLB, uint8_t* axHB, uint8_t* ayLB, uint8_t* ayHB, uint8_t* azLB, uint8_t* azHB) {
  I2Cdev::readBytes(devAddrAcc, BMI055_ACC_ACCD_X_LSB, 6, buffer);
  *axLB=(uint8_t)buffer[0];
  *axHB=(uint8_t)buffer[1];

  *ayLB=(uint8_t)buffer[2];
  *ayHB=(uint8_t)buffer[3];

  *azLB=(uint8_t)buffer[4];
  *azHB=(uint8_t)buffer[5];

}

// // TODO: mask out unused bits? signed integer behaves strange when bitshifted: [1111 1111 1111 0001] >>4 = [1111 1111 1111 1111]
//
// int16_t BMI055::getAccelerationX() {
//   I2Cdev::readBytes(devAddrAcc, BMI055_ACC_ACCD_X_LSB, 2, buffer);
//   return ((((int16_t)buffer[1]) << 8) | (int16_t)buffer[0]  >> 4);
// }
//
// int16_t BMI055::getAccelerationY() {
//   I2Cdev::readBytes(devAddrAcc, BMI055_ACC_ACCD_Y_LSB, 2, buffer);
//   return ((((int16_t)buffer[1]) << 8) | (int16_t)buffer[0]  >> 4);
// }
//
// int16_t BMI055::getAccelerationZ() {
//   I2Cdev::readBytes(devAddrAcc, BMI055_ACC_ACCD_Z_LSB, 2, buffer);
//   return ((((int16_t)buffer[1]) << 8) | (int16_t)buffer[0]  >> 4);
// }

void BMI055::getTurnRate(uint8_t* gxLB,uint8_t* gxHB, uint8_t* gyLB,uint8_t* gyHB, uint8_t* gzLB,uint8_t* gzHB) {
  I2Cdev::readBytes(devAddrGyr, BMI055_GYR_RATE_X_LSB, 6, buffer);
  *gxLB=(uint8_t)buffer[0];
  *gxHB=(uint8_t)buffer[1];

  *gyLB=(uint8_t)buffer[2];
  *gyHB=(int8_t)buffer[3];

  *gzLB=(uint8_t)buffer[4];
  *gzHB=(uint8_t)buffer[5];
}

// int16_t BMI055::getTurnRateX() {
//   I2Cdev::readBytes(devAddrGyr, BMI055_GYR_RATE_X_LSB, 2, buffer);
//   return ((((int16_t)buffer[1]) << 8) | buffer[0]);
// }
//
// int16_t BMI055::getTurnRateY() {
//   I2Cdev::readBytes(devAddrGyr, BMI055_GYR_RATE_Y_LSB, 2, buffer);
//   return ((((int16_t)buffer[1]) << 8) | buffer[0]);
// }
//
// int16_t BMI055::getTurnRateZ() {
//   I2Cdev::readBytes(devAddrGyr, BMI055_GYR_RATE_Z_LSB, 2, buffer);
//   return ((((int16_t)buffer[1]) << 8) | buffer[0]);
// }
