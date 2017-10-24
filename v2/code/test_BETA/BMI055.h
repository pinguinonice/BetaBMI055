// BMI055 I2C Class header
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

#ifndef _BMI055_H_
#define _BMI055_H_

#include "I2Cdev.h"

#define BMI055_ACC_ADDRESS          	        0x18    // default I2C address acc
#define BMI055_GYR_ADDRESS         		0x68    // default I2C address gyro

#define BMI055_ACC_ADDRESS_alt      	        0x19    // alternative I2C address acc
#define BMI055_GYR_ADDRESS_alt      	        0x69    // alternative I2C address gyro

#define BMI055_ACC_BGW_CHIPID	    	        0x00 	// Fixed value B11111010 or 0xFA

#define BMI055_ACC_ACCD_X_LSB	  		0x02
#define BMI055_ACC_ACCD_X_MSB			0x03
#define BMI055_ACC_ACCD_Y_LSB	  		0x04
#define BMI055_ACC_ACCD_Y_MSB			0x05
#define BMI055_ACC_ACCD_Z_LSB	  		0x06
#define BMI055_ACC_ACCD_Z_MSB			0x07
#define BMI055_ACC_ACCD_TEMP			0x08
#define BMI055_ACC_INT_STATUS_0			0x09
#define BMI055_ACC_INT_STATUS_1			0x0A
#define BMI055_ACC_INT_STAUTS_2			0x0B
#define BMI055_ACC_INT_STATUS_3			0x0C

#define BMI055_ACC_FOFO_STATUS			0x0E
#define BMI055_ACC_PMU_RANGE			0x0F
#define BMI055_ACC_PMU_BW			0x10
#define BMI055_ACC_PMU_LPW			0x11
#define BMI055_ACC_PMU_LOW_POWER		0x12
#define BMI055_ACC_ACCD_HBW			0x13
#define BMI055_ACC_BGW_SOFTRESET		0x14

#define BMI055_ACC_INT_EN_0			0x16
#define BMI055_ACC_INT_EN_1			0x17
#define BMI055_ACC_INT_EN_2			0x18
#define BMI055_ACC_INT_MAP_0			0x19
#define BMI055_ACC_INT_MAP_1			0x1A
#define BMI055_ACC_INT_MAP_2			0x1B
#define BMI055_ACC_INT_SRC			0x1E
#define BMI055_ACC_INT_OUT_CTRL			0x20
#define BMI055_ACC_INT_RST_LATCH		0x21
#define BMI055_ACC_INT_0			0x22
#define BMI055_ACC_INT_1			0x23
#define BMI055_ACC_INT_2			0x24
#define BMI055_ACC_INT_3			0x25
#define BMI055_ACC_INT_4			0x26
#define BMI055_ACC_INT_5			0x27
#define BMI055_ACC_INT_6			0x28
#define BMI055_ACC_INT_7			0x29
#define BMI055_ACC_INT_8			0x2A
#define BMI055_ACC_INT_9			0x2B
#define BMI055_ACC_INT_A			0x2C
#define BMI055_ACC_INT_B			0x2D
#define BMI055_ACC_INT_C			0x2E
#define BMI055_ACC_INT_D			0x2F
#define BMI055_ACC_FIFO_CONFIG_0		0x30
#define BMI055_ACC_PMU_SELF_TEST		0x32
#define BMI055_ACC_TRIM_NVM_CTRL		0x33
#define BMI055_ACC_BGW_SPI3_WDT			0x34
#define BMI055_ACC_OFC_CTRL			0x36
#define BMI055_ACC_OFC_SETTING			0x37
#define BMI055_ACC_OFC_OFFSET_X			0x38
#define BMI055_ACC_OFC_OFFSET_Y			0x39
#define BMI055_ACC_OFC_OFFSET_Z			0x3A
#define BMI055_ACC_TRIM_GP0			0x3B
#define BMI055_ACC_TRIM_GP1			0x3C
#define BMI055_ACC_FIFO_CONFIG_1		0x3E
#define BMI055_ACC_FIFO_DATA			0x3F

#define BMI055_ACC_RANGE_BIT			3
#define BMI055_ACC_RANGE_LENGTH			4
#define BMI055_ACC_BW_BIT			4
#define BMI055_ACC_BW_LENGTH			5

#define BMI055_ACC_RANGE_2G			3		// B0011
#define BMI055_ACC_RANGE_4G			5		// B0101
#define BMI055_ACC_RANGE_8G			8		// B1000
#define BMI055_ACC_RANGE_16G			12		// B1100

#define BMI055_ACC_BW_BIT                       4
#define BMI055_ACC_BW_LENGTH                    5

#define BMI055_ACC_BW_7                         8               // 01000b'7.81 Hz
#define BMI055_ACC_BW_15                        9               //'01001b 15.63 Hz
#define BMI055_ACC_BW_31                        10              // 01010b 31.25 Hz
#define BMI055_ACC_BW_62                        11              //'01011b 62.5 Hz
#define BMI055_ACC_BW_125                       12              //'01100b 125 Hz
#define BMI055_ACC_BW_250                       13              //'01101b 250 Hz
#define BMI055_ACC_BW_500                       14              //'01110b 500 Hz
#define BMI055_ACC_BW_1000                      15              //'01111b'1000 Hz


#define BMI055_ACC_DATA_HIGH_BW_BIT		7
#define BMI055_ACC_DATA_HIGH_BW_LENGTH		1
#define BMI055_ACC_DATA_HIGH_BW                 1

// GYRO REGISTER

#define BMI055_GYR_CHIP_ID			0x00	// fixed value 0x0F
#define BMI055_GYR_RATE_X_LSB			0x02
#define BMI055_GYR_RATE_X_MSB			0x03
#define BMI055_GYR_RATE_Y_LSB			0x04
#define BMI055_GYR_RATE_Y_MSB			0x05
#define BMI055_GYR_RATE_Z_LSB			0x06
#define BMI055_GYR_RATE_Z_MSB			0x07

#define BMI055_GYR_INT_STATUS_0			0x09
#define BMI055_GYR_INT_STATUS_1			0x0A
#define BMI055_GYR_INT_STAUTS_2			0x0B
#define BMI055_GYR_INT_STATUS_3			0x0C

#define BMI055_GYR_FIFO_STATUS			0x0E
#define BMI055_GYR_RANGE			0x0F
#define BMI055_GYR_BW				0x10
#define BMI055_GYR_LPM1                         0x11
#define BMI055_GYR_LPM2                         0x12
#define BMI055_GYR_RATE_HBW                     0x13
#define BMI055_GYR_BGW_SOFTRESET                0x14
#define BMI055_GYR_INT_EN_0                     0x15
#define BMI055_GYR_INT_EN_1                     0x16
#define BMI055_GYR_INT_MAP_0                    0x17
#define BMI055_GYR_INT_MAP_1                    0x18
#define BMI055_GYR_INT_MAP_2                    0x19
#define BMI055_GYR_INT_DATA_SOURCE              0x1A
#define BMI055_GYR_MOT_THRES_DATA_SOURCE        0x1B
#define BMI055_GYR_MOT_INT_EN                   0x1C

#define BMI055_GYR_FIFO_WM_EN                   0x1E

#define BMI055_GYR_INT_RST_LATCH                0x21
#define BMI055_GYR_HIGH_TH_X                    0x22
#define BMI055_GYR_HIGH_DUR_X                   0x23
#define BMI055_GYR_HIGH_TH_Y                    0x24
#define BMI055_GYR_HIGH_DUR_Y                   0x25
#define BMI055_GYR_HIGH_TH_Z                    0x26
#define BMI055_GYR_HIGH_DUR_Z                   0x27

#define BMI055_GYR_SOC                          0x31
#define BMI055_GYR_A_FOC                        0x32
#define BMI055_GYR_TRIM_NVM_CTRL                0x33
#define BMI055_GYR_BGW_SPI3_WDT                 0x34

#define BMI055_GYR_OFC1                         0x36
#define BMI055_GYR_OFC2                         0x37
#define BMI055_GYR_OFC3                         0x38
#define BMI055_GYR_OFC4                         0x39
#define BMI055_GYR_TRIM_GP0                     0x3A
#define BMI055_GYR_TRIM_GP1                     0x3B
#define BMI055_GYR_BIST                         0x3C
#define BMI055_GYR_FIFO_CONFIG_0                0x3D
#define BMI055_GYR_FIFO_CONFIG_1                0x3E
#define BMI055_GYR_FIFO_DATA                    0x3F

// GYR RANGE

#define BMI055_GYR_RANGE_BIT			2
#define BMI055_GYR_RANGE_LENGTH			3

#define BMI055_GYR_RANGE_2000			0		// B000
#define BMI055_GYR_RANGE_1000			1		// B001
#define BMI055_GYR_RANGE_500			2		// B010
#define BMI055_GYR_RANGE_250			3		// B011
#define BMI055_GYR_RANGE_125			4		// B100

// GYR BW
#define BMI055_GYR_BW_BIT                       3
#define BMI055_GYR_BW_LENGTH                    4

#define BMI055_GYR_BW_32                        7               //  0111  20 100 Hz BW 32 Hz
#define BMI055_GYR_BW_64                        6               // ‘0110  10 200 Hz BW 64 Hz
#define BMI055_GYR_BW_12                        5               // ‘0101  20 100 Hz BW 12 Hz
#define BMI055_GYR_BW_23                        4               // ‘0100  10 200 Hz BW 23 Hz
#define BMI055_GYR_BW_47                        3               // ‘0011  5  400 Hz BW 47 Hz
#define BMI055_GYR_BW_116                       2               // ‘0010  2 1000 Hz BW 116 Hz
#define BMI055_GYR_BW_230                       1               // ‘0001  0 2000 Hz BW 230 Hz
#define BMI055_GYR_BW_523                       0               // ‘0000  0 2000 Hz Unfiltered (523Hz)


#define BMI055_GYR_BW_BIT                       3
#define BMI055_GYR_BW_LENGTH                    4
#define BMI055_GYR_BW_32HZ                      7               // B0111
#define BMI055_GYR_BW_64HZ                      6               // B0111
#define BMI055_GYR_BW_12HZ                      5               // B0110
#define BMI055_GYR_BW_23HZ                      4               // B0101
#define BMI055_GYR_BW_47HZ                      3               // B0011
#define BMI055_GYR_BW_116HZ                     2               // B0010
#define BMI055_GYR_BW_230HZ                     1               // B0001
#define BMI055_GYR_BW_523HZ                     0               // B0000

// TODO

// class

class BMI055 {
public:
  BMI055();
  BMI055(uint8_t addressAcc, uint8_t addressGyro);

  void initialize();
  bool testConnection();

  // CHIP_ID register
  uint8_t getDeviceIDAcc();
  uint8_t getDeviceIDGyr();

  // AXIS registers
  void getAcceleration(uint8_t* ,uint8_t* , uint8_t* ,uint8_t* , uint8_t* ,uint8_t* );
  int16_t getAccelerationX();
  int16_t getAccelerationY();
  int16_t getAccelerationZ();

  void getTurnRate(uint8_t* ,uint8_t* , uint8_t* ,uint8_t* , uint8_t* ,uint8_t* );
  int16_t getTurnRateX();
  int16_t getTurnRateY();
  int16_t getTurnRateZ();

  // Range & Bandwidth Registers
  uint8_t getRangeAcc();
  void setRangeAcc(uint8_t range);
  uint8_t getBandwidthAcc();
  void setBandwidthAcc(uint8_t bandwidth);
  uint8_t getRangeGyr();
  void setRangeGyr(uint8_t range);
  uint8_t getBandwidthGyr();
  void setBandwidthGyr(uint8_t bandwidth);

private:
  uint8_t devAddrAcc;
  uint8_t devAddrGyr;
  uint8_t buffer[6];
};

#endif /* _BMI055_H_ */
