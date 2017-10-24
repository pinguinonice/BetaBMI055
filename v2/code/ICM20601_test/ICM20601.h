/*// ============================================
// InvenSense ICM 201601 -  I2C Class header
// Based on InvenSense ICM-20601 Datasheet - DS-000191, Revision: 1.0
// http://www.invensense.com/wp-content/uploads/2015/12/DS-000191-ICM-20601-v1.0.pdf
// ============================================
// Changelog:
//    [2017-01-17] - initial release   - [BS]
//    [2017-02-16] - code cleanup      - [BS]
// ============================================
// I2Cdev device library code is placed under the MIT license
// Copyright (c) 2012 Jeff Rowberg
// ============================================
*/

#ifndef _ICM20601_H_
#define _ICM20601_H_

#include "I2Cdev.h"
//#include <avr/pgmspace.h>

// Acc & Gyro Register ICM20601
    
#define ICM20601_ADDRESS_AD0_LOW        0x68    // address pin low  (GND)
#define ICM20601_ADDRESS_AD0_HIGH       0x69    // address pin high (VCC)
#define ICM20601_DEFAULT_ADDRESS        ICM20601_ADDRESS_AD0_LOW

#define ICM20601_RA_SELF_TEST_X_GYRO    0x00    // xg_st_data[7:0]
#define ICM20601_RA_SELF_TEST_Y_GYRO    0x01    // yg_st_data[7:0]
#define ICM20601_RA_SELF_TEST_Z_GYRO    0x02    // zg_st_data[7:0]

#define ICM20601_RA_SELF_TEST_X_ACC     0x0D    // xa_st_data[7:0]
#define ICM20601_RA_SELF_TEST_Y_ACC     0x0E    // ya_st_data[7:0]
#define ICM20601_RA_SELF_TEST_Z_ACC     0x0F    // za_st_data[7:0]

#define ICM20601_RA_XG_OFFSET_H         0x13    // XG_OFFS_USR [15:8]
#define ICM20601_RA_XG_OFFSET_L         0x14    // XG_OFFS_USR [7:0]
#define ICM20601_RA_YG_OFFSET_H         0x15    // YG_OFFS_USR [15:8]
#define ICM20601_RA_YG_OFFSET_L         0x16    // YG_OFFS_USR [7:0]
#define ICM20601_RA_ZG_OFFSET_H         0x17    // ZG_OFFS_USR [15:8]
#define ICM20601_RA_ZG_OFFSET_L         0x18    // ZG_OFFS_USR [7:0]

#define ICM20601_RA_SMPLRT_DIV          0x19    // SMPLRT_DIV [7:0]
#define ICM20601_RA_CONFIG              0x1A
#define ICM20601_RA_GYRO_CONFIG         0x1B
#define ICM20601_RA_ACC_CONFIG          0x1C
#define ICM20601_RA_ACC_CONFIG2         0x1D
#define ICM20601_RA_LP_MODE_CFG         0x1E    
#define ICM20601_RA_ACC_WOM_THR         0x1F    // holds the threshold for the wake on motion interrupt for acc 

#define ICM20601_RA_FIFO_EN             0x23

#define ICM20601_RA_FSYNC_INT           0x36    
#define ICM20601_RA_INT_PIN_CFG         0x37
#define ICM20601_RA_INT_ENABLE          0x38
#define ICM20601_RA_INT_STATUS          0x3A

#define ICM20601_RA_ACC_XOUT_H          0x3B
#define ICM20601_RA_ACC_XOUT_L          0x3C
#define ICM20601_RA_ACC_YOUT_H          0x3D
#define ICM20601_RA_ACC_YOUT_L          0x3E
#define ICM20601_RA_ACC_ZOUT_H          0x3F
#define ICM20601_RA_ACC_ZOUT_L          0x40

#define ICM20601_RA_TEMP_OUT_H          0x41
#define ICM20601_RA_TEMP_OUT_L          0x42

#define ICM20601_RA_GYRO_XOUT_H         0x43
#define ICM20601_RA_GYRO_XOUT_L         0x44
#define ICM20601_RA_GYRO_YOUT_H         0x45
#define ICM20601_RA_GYRO_YOUT_L         0x46
#define ICM20601_RA_GYRO_ZOUT_H         0x47
#define ICM20601_RA_GYRO_ZOUT_L         0x48

#define ICM20601_RA_SIGNAL_PATH_RESET   0x68
#define ICM20601_RA_ACC_INTEL_CTRL      0x69
#define ICM20601_RA_USER_CTRL           0x6A
#define ICM20601_RA_PWR_MGMT_1          0x6B
#define ICM20601_RA_PWR_MGMT_2          0x6C

#define ICM20601_RA_FIFO_COUNT_H        0x72
#define ICM20601_RA_FIFO_COUNT_L        0x73
#define ICM20601_RA_FIFO_R_W            0x74
#define ICM20601_RA_WHO_AM_I            0x75

#define ICM20601_RA_XA_OFFSET_H         0x77
#define ICM20601_RA_XA_OFFSET_L         0x78
#define ICM20601_RA_YA_OFFSET_H         0x7A
#define ICM20601_RA_YA_OFFSET_L         0x7B
#define ICM20601_RA_ZA_OFFSET_H         0x7D
#define ICM20601_RA_ZA_OFFSET_L         0x7E


// Config Register
#define ICM20601_CFG_FIFO_MODE_BIT          6   // 1: when fifo full, no additional writes to fifo. 
                                                // 0: when fifo full, additional data replaces oldest data.
#define ICM20601_CFG_EXT_SYNC_SET_BIT       5
#define ICM20601_CFG_EXT_SYNC_SET_LENGTH    3
#define ICM20601_CFG_DLPF_CFG_BIT           2
#define ICM20601_CFG_DLPF_CFG_LENGTH        3

#define ICM20601_EXT_SYNC_DISABLED          0x0
#define ICM20601_EXT_SYNC_TEMP_OUT_L        0x1
#define ICM20601_EXT_SYNC_GYRO_XOUT_L       0x2
#define ICM20601_EXT_SYNC_GYRO_YOUT_L       0x3
#define ICM20601_EXT_SYNC_GYRO_ZOUT_L       0x4
#define ICM20601_EXT_SYNC_ACC_XOUT_L        0x5
#define ICM20601_EXT_SYNC_ACC_YOUT_L        0x6
#define ICM20601_EXT_SYNC_ACC_ZOUT_L        0x7

//For the DLPF to be used, FCHOICE_B[1:0] is B00
#define ICM20601_CFG_DLPF_BW_250            0    // See table on page 36 in docu ICM20601
#define ICM20601_CFG_DLPF_BW_176            1
#define ICM20601_CFG_DLPF_BW_92             2
#define ICM20601_CFG_DLPF_BW_41             3
#define ICM20601_CFG_DLPF_BW_20             4
#define ICM20601_CFG_DLPF_BW_10             5
#define ICM20601_CFG_DLPF_BW_5              6
#define ICM20601_CFG_DLPF_BW_3281           7

// Gyro Config Register
#define ICM20601_GCONFIG_XG_ST_BIT          7   // name changed
#define ICM20601_GCONFIG_YG_ST_BIT          6   // Y Gyro self-test 
#define ICM20601_GCONFIG_ZG_ST_BIT          5   // Z Gyro self-test
#define ICM20601_GCONFIG_GYRO_FS_SEL_BIT    4
#define ICM20601_GCONFIG_GYRO_FS_SEL_LENGTH 2
#define ICM20601_GCONFIG_FCHOICE_B_BIT      1
#define ICM20601_GCONFIG_FCHOISE_B_LENGTH   2

#define ICM20601_GYRO_FS_500                0
#define ICM20601_GYRO_FS_1000               1
#define ICM20601_GYRO_FS_2000               2
#define ICM20601_GYRO_FS_4000               3
    
#define ICM20601_GCONFIG_FCHOISE_B_DLPF_EN      B00     // FCHOISE_B, DLPF enabled
#define ICM20601_GCONFIG_FCHOISE_B_DLPF_3281    B10     // FCHOISE_B, DLPF disabled = 3281 Hz
#define ICM20601_GCONFIG_FCHOISE_B_DLPF_8173    B01     // FCHOISE_B, DLPF disabled = 8173 Hz

// Acc Config Register
#define ICM20601_ACONFIG_XA_ST_BIT          7
#define ICM20601_ACONFIG_YA_ST_BIT          6
#define ICM20601_ACONFIG_ZA_ST_BIT          5
#define ICM20601_ACONFIG_ACC_FS_SEL_BIT     4
#define ICM20601_ACONFIG_ACC_FS_SEL_LENGTH  2

#define ICM20601_ACC_FS_4                   0
#define ICM20601_ACC_FS_8                   1
#define ICM20601_ACC_FS_16                  2
#define ICM20601_ACC_FS_32                  3

// Acc Config 2 Register

#define ICM20601_ACONFIG2_ACC_DEC2_CFG_BIT          5
#define ICM20601_ACONFIG2_ACC_DEC2_CFG_LENGTH       2

#define ICM20601_ACONFIG2_ACC_FCHOISE_B_BIT         3
#define ICM20601_ACONFIG2_ACC_FCHOISE_B_LENGTH      1

#define ICM20601_ACONFIG2_ACC_DLPF_CFG_BIT          2
#define ICM20601_ACONFIG2_ACC_DLPF_CFG_LENGTH       3

#define ICM20601_ACONFIG2_ACC_FCHOISE_B_DLPF_1046   1  // FCHOISE_B, DLPF disabled = 1046 Hz    
#define ICM20601_ACONFIG2_ACC_FCHOISE_B_DLPF_EN     0  // FCHOISE_B, DLPF enabled

// Averaging filer settings for Low Power Acc mode:
#define ICM20601_ACONFIG2_ACC_DEC2_CFG_4            0   // averaging by 4 samples 
#define ICM20601_ACONFIG2_ACC_DEC2_CFG_8            1   // averaging by 8 samples
#define ICM20601_ACONFIG2_ACC_DEC2_CFG_16           2   // averaging by 16 samples
#define ICM20601_ACONFIG2_ACC_DEC2_CFG_32           3   // averaging by 32 samples

#define ICM20601_ACONFIG2_ACC_DLPF_CFG_219          0   // error in docu ?? 218 Hz 
#define ICM20601_ACONFIG2_ACC_DLPF_CFG_218          1   // 218 Hz
#define ICM20601_ACONFIG2_ACC_DLPF_CFG_99           2
#define ICM20601_ACONFIG2_ACC_DLPF_CFG_45           3
#define ICM20601_ACONFIG2_ACC_DLPF_CFG_21           4
#define ICM20601_ACONFIG2_ACC_DLPF_CFG_10           5
#define ICM20601_ACONFIG2_ACC_DLPF_CFG_5            6
#define ICM20601_ACONFIG2_ACC_DLPF_CFG_420          7

// Low Power Mode Config  Register

#define ICM20601_LP_MODE_CFG_GYR_CYCLE_BIT          7   // when set to 1: low-power gyr mode is enabled, default: 0

#define ICM20601_LP_MODE_CFG_G_AVGCFG_BIT           6
#define ICM20601_LP_MODE_CFG_G_AVGCFG_LENGTH        3

#define ICM20601_LP_MODE_CFG_LPOSC_CLKSEL_BIT       2   // error in ICM20601 docu ??
#define ICM20601_LP_MODE_CFG_LPOSC_CLKSEL_LENGTH    3
#define ICM20601_LP_MODE_CFG_LPOSC_CLKSEL_0_24      0
#define ICM20601_LP_MODE_CFG_LPOSC_CLKSEL_0_49      1
#define ICM20601_LP_MODE_CFG_LPOSC_CLKSEL_0_98      2
#define ICM20601_LP_MODE_CFG_LPOSC_CLKSEL_1_95      3
#define ICM20601_LP_MODE_CFG_LPOSC_CLKSEL_3_91      4
#define ICM20601_LP_MODE_CFG_LPOSC_CLKSEL_7_81      5
#define ICM20601_LP_MODE_CFG_LPOSC_CLKSEL_15_63     6
#define ICM20601_LP_MODE_CFG_LPOSC_CLKSEL_31_25     7
//#define ICM20601_LP_MODE_CFG_LPOSC_CLKSEL_62_50     8
//#define ICM20601_LP_MODE_CFG_LPOSC_CLKSEL_125       9
//#define ICM20601_LP_MODE_CFG_LPOSC_CLKSEL_250       10
//#define ICM20601_LP_MODE_CFG_LPOSC_CLKSEL_500       11

// To operate in gyr low-power mode or 6-axis low-power mode, GYRO_CYCLE should be set to 1
// Gyr filter configuration is determined by G_AVGCFG[2:0] that sets the averaging filter configuration. 
// It is not dependent on DLPF_CFG[2:0].
// see table on page 38 of ICM20601 docu.

#define ICM20601_LP_MODE_CFG_G_AVGCFG_1             0
#define ICM20601_LP_MODE_CFG_G_AVGCFG_2             1
#define ICM20601_LP_MODE_CFG_G_AVGCFG_4             2
#define ICM20601_LP_MODE_CFG_G_AVGCFG_8             3
#define ICM20601_LP_MODE_CFG_G_AVGCFG_16            4
#define ICM20601_LP_MODE_CFG_G_AVGCFG_32            5
#define ICM20601_LP_MODE_CFG_G_AVGCFG_64            6
#define ICM20601_LP_MODE_CFG_G_AVGCFG_128           7

// FIFO enable Register        
#define ICM20601_FIFO_EN_TEMP_FIFO_EN_BIT           7
#define ICM20601_FIFO_EN_XG_FIFO_EN_BIT             6
#define ICM20601_FIFO_EN_YG_FIFO_EN_BIT             5
#define ICM20601_FIFO_EN_ZG_FIFO_EN_BIT             4
#define ICM20601_FIFO_EN_ACC_FIFO_EN_BIT            3

// FYSNC interrupt status Register
#define ICM20601_FSYNC_INT_BIT                      7   // this bit automatically sets to 1 whan a FSYNC interrupt has been generated. clears to 0 after read 
#define ICM20601_FSYNC_INT_LENGTH                   1

// Int Pin Config Register
#define ICM20601_INT_PIN_CFG_INT_LEVEL_BIT          7   // 1: logic level for INT/DRDY pin is active low        
#define ICM20601_INT_PIN_CFG_INT_OPEN_BIT           6   // 1: INT/DRDY pin is configured as open drain; 0: push-pull
#define ICM20601_INT_PIN_CFG_LATCH_INT_EN_BIT       5   // 1: INT/DRDY pin level is held until interrupt status s cleared
#define ICM20601_INT_PIN_CFG_INT_RD_CLEAR_BIT       4   // 1: interrupt status is cleared if any read operation is performed.
                                                        // 0: interrupt status is cleared only by reading INT_STATUS register
#define ICM20601_INT_PIN_CFG_FSYNC_INT_LEVEL_BIT    3   // 1: the logic level for the FSYNC pin as an interrupt is active low.
                                                        // 0: the logic level for the FSYNC pin as an interrupt is active high.
#define ICM20601_INT_PIN_CFG_FSYNC_INT_MODE_EN_BIT  2   // 1: FSYNC pin will trigger an interrupt when it transitions to the level specified by FSYNC_INT_LEVEL. 
                                                        // 0: FSYNC pin is disabled from causing an interrupt.

// Interupt enable Register
#define ICM20601_INT_ENABLE_WOM_INT_EN_BIT          7
#define ICM20601_INT_ENABLE_WOM_INT_EN_LENGTH       3
#define ICM20601_INT_ENABLE_FIFO_OFLOW_EN_BIT       4   // 1: enables a FIFO buffer overflow to generate an interrupt.
#define ICM20601_INT_ENABLE_FIFO_OFLOW_EN_LENGTH    1
#define ICM20601_INT_ENABLE_GDRIVE_INT_EN_BIT       2   // Gyroscope Drive System Ready interrupt enable
#define ICM20601_INT_ENABLE_GDRIVE_INT_EN_LENGTH    1
#define ICM20601_INT_ENABLE_DATA_RDY_INT_EN_BIT     0   // Data ready interrupt enable
#define ICM20601_INT_ENABLE_DATA_RDY_INT_EN_LENGTH  1

#define ICM20601_INT_ENABLE_WOM_INT_EN_ENABLE       B111    // Enable WoM interrupt on accelerometer.
#define ICM20601_INT_ENABLE_WOM_INT_EN_DISABLE      B000    // Disable WoM interrupt on accelerometer.

// Interupt Status Register
#define ICM20601_INT_STATUS_WOM_INT_BIT             7       // Accelerometer WoM interrupt status. Cleared on Read.
                                                            // 111 – WoM interrupt on accelerometer
#define ICM20601_INT_STATUS_WOM_INT_LENGTH          3
#define ICM20601_INT_STATUS_FIFO_OFLOW_INT_BIT      4       // 1: FIFO buffer overflow has been generated. clears to 0 after the register has been read. 
#define ICM20601_INT_STATUS_GDRIVE_INT_BIT          2       // Gyroscope Drive System Ready interrupt
#define ICM20601_INT_STATUS_DATA_RDY_INT_BIT        0       // Data Ready interrupt is generated

// data registers

// Signal Path Reset Register
#define ICM20601_SIGNAL_PATH_RESET_ACC_RST_BIT      1       // reset acc digital signal path.  NOTE: Sensor registers are not cleared. Use SIG_COND_RST to clear sensor registers
#define ICM20601_SIGNAL_PATH_RESET_TEMP_RST_BIT     0       // reset temp digital signal path. NOTE: Sensor registers are not cleared. Use SIG_COND_RST to clear sensor registers. 

// Acc intelligence Control Register
#define ICM20601_ACC_INTEL_CTRL
#define ICM20601_ACC_INTEL_CTRL_ACC_INTEL_EN_BIT    7       // enables wake on motion detection logical 
#define ICM20601_ACC_INTEL_CTRL_ACC_INTEL_MODE_BIT  6       // 1: compare the current sample with the previous sample, 0: do not use

// User Control Register
#define ICM20601_USER_CTRL_FIFO_EN_BIT              6       // 1: Enable FIFO operation mode.
                                                            // 0: Disable FIFO access from serial interface. To disable FIFO writes by DMA, use FIFO_EN register.
#define ICM20601_USER_CTRL_FIFO_EN_LENGTH           1
#define ICM20601_USER_CTRL_I2C_IF_DIS_BIT           4       // 1: Disable I2C Slave module and put the serial interface in SPI mode only.
#define ICM20601_USER_CTRL_I2C_IF_DIS_LENGTH        1
#define ICM20601_USER_CTRL_FIFO_RST_BIT             2       // 1: Reset FIFO module. Reset is asynchronous. This bit auto clears after one clock cycle of the internal 20 MHz clock.
#define ICM20601_USER_CTRL_FIFO_RST_LENGTH          1
#define ICM20601_USER_CTRL_SIG_COND_RST_BIT         0       // 1: Reset all gyr digital signal path, acc digital signal path, and temp digital signal path. This bit also clears all the sensor registers.
#define ICM20601_USER_CTRL_SIG_COND_RST_LENGTH      1

// Power Management Register 1
#define ICM20601_PWR_MGMT_1_DEVICE_RESET_BIT        7       // 1: reset the internal registers and restores the default settings. clears to 0 once the reset is done.
#define ICM20601_PWR_MGMT_1_SLEEP_BIT               6       // 1: the chip is set to sleep mode. NOTE: The default value is 1, the chip comes up in Sleep mode
#define ICM20601_PWR_MGMT_1_ACC_CYCLE_BIT           5       // 1: and SLEEP and STANDBY are not set to 1, the chip will cycle between sleep and taking a single acc sample at a rate determined by SMPLRT_DIV
                                                            // NOTE: When all acc axes are disabled via PWR_MGMT_2 register bits and cycle is enabled, the chip will wake up at the rate determined by the respective registers above, but will not take any samples
#define ICM20601_PWR_MGMT_1_GYRO_STANDBY_BIT        4       // 1: the gyr drive and pll circuitry are enabled, but the sense paths are disabled. This is a low power mode that allows quick enabling of the gyr
#define ICM20601_PWR_MGMT_1_TEMP_DIS_BIT            3       // 1: disables the temperature sensor
#define ICM20601_PWR_MGMT_1_CLKSEL_BIT              2
#define ICM20601_PWR_MGMT_1_CLKSEL_LENGTH           3           

// NOTE: The default value of CLKSEL[2:0] is 000. It is required that CLKSEL[2:0] be set to 001 to achieve full gyroscope performance.
#define ICM20601_PWR_MGMT_1_CLKSEL_INTERNAL_20M_1   0
#define ICM20601_PWR_MGMT_1_CLKSEL_PLL_AUTO1        1
#define ICM20601_PWR_MGMT_1_CLKSEL_PLL_AUTO2        2
#define ICM20601_PWR_MGMT_1_CLKSEL_PLL_AUTO3        3
#define ICM20601_PWR_MGMT_1_CLKSEL_PLL_AUTO4        4
#define ICM20601_PWR_MGMT_1_CLKSEL_PLL_AUTO5        5
#define ICM20601_PWR_MGMT_1_CLKSEL_INTERNAL_20M_2   6
#define ICM20601_PWR_MGMT_1_CLKSEL_KEEP_RESET       7       // Stops the clock and keeps timing generator in reset

// Power Management Register 2
#define ICM20601_PWR_MGMT_2_FIFO_LP_EN_BIT          7       // 1: enable FIFO in low-power accelerometer mode. Default setting is 0.
#define ICM20601_PWR_MGMT_2_STBY_XA_BIT             5       // 1: disable, 0: on
#define ICM20601_PWR_MGMT_2_STBY_YA_BIT             4       // 1: disable, 0: on
#define ICM20601_PWR_MGMT_2_STBY_ZA_BIT             3       // 1: disable, 0: on
#define ICM20601_PWR_MGMT_2_STBY_XG_BIT             2       // 1: disable, 0: on
#define ICM20601_PWR_MGMT_2_STBY_YG_BIT             1       // 1: disable, 0: on
#define ICM20601_PWR_MGMT_2_STBY_ZG_BIT             0       // 1: disable, 0: on

// Who am I Register
#define ICM20601_WHO_AM_I_BIT                       7
#define ICM20601_WHO_AM_I_LENGTH                    8
#define ICM20601_WHO_AM_I_VALUE                     0xAC    // ICM20601

class ICM20601 {
    public:
        ICM20601();
        ICM20601(uint8_t address);

        void initialize();
        bool testConnection();

        uint8_t getDeviceID();

        void getAcceleration(int16_t* ax, int16_t* ay, int16_t* az);
        void getRotation(int16_t* gx, int16_t* gy, int16_t* gz);
        int16_t getTemperature();
        void getTemperature(int16_t* temp);

        void setRate(uint8_t smprt_div);
        uint8_t getSampleRateDivider();

        void setGyrDLPF_CFG(uint8_t dlpf);
        uint8_t getGyrDLPF_CFG();

        void setGyrFchoise_b(uint8_t fchoise_b);
        uint8_t getGyrFChoise_b ();

        void setFullScaleGyroRange(uint8_t gyr_fs);
        uint8_t getFullScaleGyroRange();

        void setFullScaleAccelRange(uint8_t acc_fs);
        uint8_t getFullScaleAccelRange();

        void setAccFchoise_b(uint8_t fchoise_b);
        uint8_t getAccFChoise_b ();

        void setAccDLPF_CFG(uint8_t dlpf);
        uint8_t getAccDLPF_CFG();

        void setSleepMode(bool sleepmode);
        bool getSleepMode();

        uint8_t getIntStatus();

        void setFIFOOperationMode(bool operationmode);
        bool getFIFOOperationMode();
        void FIFOReset();

        void setFIFOModeWhenFullNoWrite(bool FIFOmode);
        bool getFIFOModeWhenFullNoWrite();

        void setFIFOOverflowGenIntEnable(bool interruptenable);
        bool getFIFOOverflowGenIntEnable();

        void setFIFOEnableSensors(uint8_t sensorsenable);
        uint8_t getFIFOEnableSensors();

        int16_t getFIFOCount();

        uint8_t getFIFOData();
        void setFIFOData(uint8_t FIFOdata);
        
    
    private:
        uint8_t devAddr;
        uint8_t buffer[14];
};

#endif /* _ICM20601_H_ */
