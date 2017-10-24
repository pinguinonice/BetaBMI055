// MAX 17048 Lib
//
// CLASS
//
// based on http://datasheets.maximintegrated.com/en/ds/MAX17048-MAX17049.pdf
//
// BS
//
// Changelog:
//     [YYYY-mm-dd] - updated some broken thing
//     [2015-05-28] - initial release

#include "MAX17048.h"


MAX17048::MAX17048() {
  devAddr = MAX17048_DEFAULT_ADDRESS;
}

MAX17048::MAX17048(uint8_t address) {
  devAddr = MAX17048_DEFAULT_ADDRESS;
}

void MAX17048::initialize() {
}


bool MAX17048::testConnection() {
  I2Cdev::readWord(devAddr, MAX17048_RA_CONFIG, buffer);
  if (buffer[0] == 0x971C) {
    return true;
  }
  return false;
}

uint16_t MAX17048::getVCELL() {
  // read a single word and return it
  I2Cdev::readWord(devAddr, MAX17048_RA_VCELL, buffer);
  return buffer[0];
}

uint16_t MAX17048::getSOC() {
  // read a single word and return it
  I2Cdev::readWord(devAddr, MAX17048_RA_SOC, buffer);
  return buffer[0];
}

uint16_t MAX17048::getMode() {
  I2Cdev::readWord(devAddr, MAX17048_RA_MODE, buffer);
  return buffer[0];
}

void MAX17048::setMode(uint16_t mode) {
  I2Cdev::writeWord(devAddr, MAX17048_RA_MODE, mode);  
}

uint16_t MAX17048::getConfig() {
  I2Cdev::readWord(devAddr, MAX17048_RA_CONFIG, buffer);
  return buffer[0];
}

void MAX17048::setConfig(uint16_t config) {
  I2Cdev::writeWord(devAddr, MAX17048_RA_CONFIG, config);
}

uint16_t MAX17048::getDeviceID() {
  // read a single byte and return it
  I2Cdev::readWord(devAddr, MAX17048_RA_VRESET_ID, buffer);
  return buffer[0];
}
