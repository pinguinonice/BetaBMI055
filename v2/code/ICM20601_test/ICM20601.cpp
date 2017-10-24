/*// ============================================
// InvenSense ICM 201601 -  I2C Class source
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

#include "ICM20601.h"

/*
 * Default Constructor
 */
ICM20601::ICM20601() {
  devAddr  = ICM20601_DEFAULT_ADDRESS;
}

/*
 * Specific Address Constructor
 */
ICM20601::ICM20601(uint8_t address) {
  devAddr  = address;
}

/*
 * Initialize with I2C Master I/F module, pins ES_DA and ES_SCL are isolated from pins SDA and SCL
 */
void ICM20601::initialize() {
 
}

/*
 * Test Connection, check WHO_AM_I value
 */
bool ICM20601::testConnection() {
    return getDeviceID() == ICM20601_WHO_AM_I_VALUE;
}

/*
 * Get Device ID / Who am I
 */
uint8_t ICM20601::getDeviceID(){
    I2Cdev::readByte(devAddr,ICM20601_RA_WHO_AM_I, buffer);
    return buffer[0];
}

/*
 * Get Acc Data
 */
void ICM20601::getAcceleration(int16_t* ax, int16_t* ay, int16_t* az) {
    I2Cdev::readBytes(devAddr, ICM20601_RA_ACC_XOUT_H, 6, buffer);
    *ax = (((int16_t)buffer[0]) << 8) | buffer[1];
    *ay = (((int16_t)buffer[2]) << 8) | buffer[3];
    *az = (((int16_t)buffer[4]) << 8) | buffer[5];
}

/*
 * Get Gyro Data
 */
void ICM20601::getRotation(int16_t *gx, int16_t *gy, int16_t *gz) {
    I2Cdev::readBytes(devAddr, ICM20601_RA_GYRO_XOUT_H, 6, buffer);
    *gx = (((int16_t)buffer[0]) << 8) | buffer[1];
    *gy = (((int16_t)buffer[2]) << 8) | buffer[3];
    *gz = (((int16_t)buffer[4]) << 8) | buffer[5];
}

/*
 * Get Temperature
 */
int16_t ICM20601::getTemperature() {
    I2Cdev::readBytes(devAddr, ICM20601_RA_TEMP_OUT_H, 2, buffer);
    return (((int16_t)buffer[0]) << 8) | buffer[1];
}

void ICM20601::getTemperature(int16_t *temp) {
    I2Cdev::readBytes(devAddr, ICM20601_RA_TEMP_OUT_H, 2, buffer);
    *temp = (((int16_t)buffer[0]) << 8) | buffer[1];
}


/*
 * Set Sample Rate Divider
 */
void ICM20601::setRate(uint8_t smplrt_div) {
    I2Cdev::writeByte(devAddr, ICM20601_RA_SMPLRT_DIV, smplrt_div);
}

/*
 * Get Sample Rate Divider
 */
uint8_t ICM20601::getSampleRateDivider() {
    I2Cdev::readByte(devAddr, ICM20601_RA_SMPLRT_DIV, buffer);
    return buffer[0];
}

/*
 * Set Gyro DLPF Config
 */
void ICM20601::setGyrDLPF_CFG(uint8_t dlpf) {
    I2Cdev::writeBits(devAddr, ICM20601_RA_CONFIG, ICM20601_CFG_DLPF_CFG_BIT, ICM20601_CFG_DLPF_CFG_LENGTH, dlpf);
}

/*
 * Get Gyro DLPF Config
 */
uint8_t ICM20601::getGyrDLPF_CFG() {
    I2Cdev::readBits(devAddr, ICM20601_RA_CONFIG, ICM20601_CFG_DLPF_CFG_BIT, ICM20601_CFG_DLPF_CFG_LENGTH, buffer);
    return buffer[0];
}

/*
 * Set Gyro FCHOISE_B
 */
void ICM20601::setGyrFchoise_b(uint8_t fchoise_b) {
    I2Cdev::writeBits(devAddr, ICM20601_RA_GYRO_CONFIG, ICM20601_GCONFIG_FCHOICE_B_BIT, ICM20601_GCONFIG_FCHOISE_B_LENGTH, fchoise_b);
}

/*
 * Get Gyro FCHOISE_B
 */
uint8_t ICM20601::getGyrFChoise_b() {
    I2Cdev::readBits(devAddr, ICM20601_RA_GYRO_CONFIG, ICM20601_GCONFIG_FCHOICE_B_BIT, ICM20601_GCONFIG_FCHOISE_B_LENGTH, buffer);
    return buffer[0];
}

/*
 * Set Gyro Full Scale Range
 */
void ICM20601::setFullScaleGyroRange(uint8_t gyr_fs) {
    I2Cdev::writeBits(devAddr, ICM20601_RA_GYRO_CONFIG, ICM20601_GCONFIG_GYRO_FS_SEL_BIT, ICM20601_GCONFIG_GYRO_FS_SEL_LENGTH, gyr_fs);
}

/*
 * Get Gyro Full Scale Range
 */
uint8_t ICM20601::getFullScaleGyroRange() {
    I2Cdev::readBits(devAddr, ICM20601_RA_GYRO_CONFIG, ICM20601_GCONFIG_GYRO_FS_SEL_BIT, ICM20601_GCONFIG_GYRO_FS_SEL_LENGTH, buffer);
    return buffer[0];
}

/*
 * Set Acc Full Scale Range
 */
void ICM20601::setFullScaleAccelRange(uint8_t acc_fs) {
    I2Cdev::writeBits(devAddr, ICM20601_RA_ACC_CONFIG, ICM20601_ACONFIG_ACC_FS_SEL_BIT, ICM20601_ACONFIG_ACC_FS_SEL_LENGTH, acc_fs);
}

/*
 * Get Gyro Full Scale Range
 */
uint8_t ICM20601::getFullScaleAccelRange() {
    I2Cdev::readBits(devAddr, ICM20601_RA_ACC_CONFIG, ICM20601_ACONFIG_ACC_FS_SEL_BIT, ICM20601_ACONFIG_ACC_FS_SEL_LENGTH, buffer);
    return buffer[0];
}

/*
 * Set Acc FCHOISE_B 
 */
void ICM20601::setAccFchoise_b(uint8_t fchoise_b) {
    I2Cdev::writeBit(devAddr, ICM20601_RA_ACC_CONFIG2, ICM20601_ACONFIG2_ACC_FCHOISE_B_BIT, fchoise_b);
}

/*
 * Get Acc FCHOISE_B 
 */
uint8_t ICM20601::getAccFChoise_b() {
    I2Cdev::readBit(devAddr, ICM20601_RA_ACC_CONFIG2, ICM20601_ACONFIG2_ACC_FCHOISE_B_BIT, buffer);
    return buffer[0];
}

/*
 * Set Acc DLPF Config 
 */
void ICM20601::setAccDLPF_CFG(uint8_t dlpf) {
    I2Cdev::writeBits(devAddr, ICM20601_RA_ACC_CONFIG2, ICM20601_ACONFIG2_ACC_DLPF_CFG_BIT, ICM20601_ACONFIG2_ACC_DLPF_CFG_LENGTH, dlpf);
}

/*
 * Get Acc DLPF Config 
 */
uint8_t ICM20601::getAccDLPF_CFG() {
    I2Cdev::readBits(devAddr, ICM20601_RA_ACC_CONFIG2, ICM20601_ACONFIG2_ACC_DLPF_CFG_BIT, ICM20601_ACONFIG2_ACC_DLPF_CFG_LENGTH, buffer);
    return buffer[0];
}

 /* 
 * Set Sleep Mode
 */
 void ICM20601::setSleepMode(bool sleepmode) {
    I2Cdev::writeBit(devAddr, ICM20601_RA_PWR_MGMT_1, ICM20601_PWR_MGMT_1_SLEEP_BIT, sleepmode);
 }

/* 
 * Get Sleep Mode
 */
bool ICM20601::getSleepMode() {
    I2Cdev::readBit(devAddr, ICM20601_RA_PWR_MGMT_1, ICM20601_PWR_MGMT_1_SLEEP_BIT, buffer);
    return buffer[0];
}

/*
 * Get Interrupt Status
 *
 * Interupt Status Register
 *
 * Values clear after read.
 *
   #define ICM20601_INT_STATUS_WOM_INT_BIT             7       // Accelerometer WoM interrupt status. Cleared on Read.
                                                               // 111 – WoM interrupt on accelerometer
   #define ICM20601_INT_STATUS_WOM_INT_LENGTH          3
   #define ICM20601_INT_STATUS_FIFO_OFLOW_INT_BIT      4       // 1: FIFO buffer overflow has been generated. clears to 0 after the register has been read.
   #define ICM20601_INT_STATUS_GDRIVE_INT_BIT          2       // Gyroscope Drive System Ready interrupt
   #define ICM20601_INT_STATUS_DATA_RDY_INT_BIT        0       // Data Ready interrupt is generated
 */
uint8_t ICM20601::getIntStatus() {
    I2Cdev::readByte(devAddr, ICM20601_RA_INT_STATUS, buffer);
    return buffer[0];
}

/*
 * Set FIFO Operation Mode
 * Enable / Disable FIFO access from serial interface
 */
void ICM20601::setFIFOOperationMode(bool operationmode) {
    I2Cdev::writeBit(devAddr, ICM20601_RA_USER_CTRL, ICM20601_USER_CTRL_FIFO_EN_BIT, operationmode);
}

/*
 * Get FIFO Operation Mode
 * Enable / Disable FIFO access from serial interface
 */
bool ICM20601::getFIFOOperationMode() {
    I2Cdev::readBit(devAddr, ICM20601_RA_USER_CTRL, ICM20601_USER_CTRL_FIFO_EN_BIT,buffer);
    return buffer[0];
}

/*
 * Reset FIFO
 */
void ICM20601::FIFOReset() {
    I2Cdev::writeBit(devAddr, ICM20601_RA_USER_CTRL, ICM20601_USER_CTRL_FIFO_RST_BIT, 1);
}

/*
 * Set FIFO Mode: 1: when FIFO is full, additional writes will not be written to FIFO
 *                0: when FIFO is full, additional writes will be written to the FIFO, replacing the oldest data
 */
void ICM20601::setFIFOModeWhenFullNoWrite(bool FIFOmode) {
    I2Cdev::writeBit(devAddr, ICM20601_RA_CONFIG, ICM20601_CFG_FIFO_MODE_BIT, FIFOmode);
}

/*
 * Get FIFO Mode: 1: when FIFO is full, additional writes will not be written to FIFO
 *                0: when FIFO is full, additional writes will be written to the FIFO, replacing the oldest data
 */
bool ICM20601::getFIFOModeWhenFullNoWrite() {
    I2Cdev::readBit(devAddr, ICM20601_RA_CONFIG, ICM20601_CFG_FIFO_MODE_BIT, buffer);
    return buffer[0];
}

/*
 * Set FIFO Overflow Interrupt Enable
 */
void ICM20601::setFIFOOverflowGenIntEnable(bool interruptenable) {
    I2Cdev::writeBit(devAddr, ICM20601_RA_INT_ENABLE, ICM20601_INT_ENABLE_FIFO_OFLOW_EN_BIT, interruptenable);
}

/*
 * Get FIFO Overflow Interrupt Enable
 */
bool ICM20601::getFIFOOverflowGenIntEnable() {
    I2Cdev::readBit(devAddr, ICM20601_RA_INT_ENABLE, ICM20601_INT_ENABLE_FIFO_OFLOW_EN_BIT, buffer);
    return buffer[0];
}

/*
 * Enable FIFO for the sensors
 *
 * // FIFO enable Register
   #define ICM20601_FIFO_EN_TEMP_FIFO_EN_BIT           7
   #define ICM20601_FIFO_EN_XG_FIFO_EN_BIT             6
   #define ICM20601_FIFO_EN_YG_FIFO_EN_BIT             5
   #define ICM20601_FIFO_EN_ZG_FIFO_EN_BIT             4
   #define ICM20601_FIFO_EN_ACC_FIFO_EN_BIT            3
 *
 */
void ICM20601::setFIFOEnableSensors(uint8_t sensorsenable) {
    I2Cdev::writeByte(devAddr, ICM20601_RA_FIFO_EN, sensorsenable);
}

/*
 * Get Enabled FIFO for the sensors
 */
uint8_t ICM20601::getFIFOEnableSensors() {
    I2Cdev::readByte(devAddr, ICM20601_RA_FIFO_EN, buffer);
    return buffer[0];
}

/*
 *  Get FIFO Count
 */
int16_t ICM20601::getFIFOCount() {
    I2Cdev::readBytes(devAddr, ICM20601_RA_FIFO_COUNT_H, 2, buffer);
    return (((int16_t) (buffer[0] & B00001111)) << 8) | buffer[1];
}

/*
 * Get FIFO Data
 */
uint8_t ICM20601::getFIFOData() {
    I2Cdev::readByte(devAddr, ICM20601_RA_FIFO_R_W, buffer);
    return buffer[0];
}

/*
 * Set FIFO Data
 */
void ICM20601::setFIFOData(uint8_t FIFOdata) {
    I2Cdev::writeByte(devAddr, ICM20601_RA_FIFO_R_W, FIFOdata);
}
