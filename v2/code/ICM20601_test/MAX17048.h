// MAX 17048 Lib
//
// HEADER
//
// based on http://datasheets.maximintegrated.com/en/ds/MAX17048-MAX17049.pdf
//
// BS
//
// Changelog:
//     [2015-05-28] - initial release
//     [2017-05-05] - code clean up

#ifndef _MAX17048_H_
#define _MAX17048_H_

#include "I2Cdev.h"

// ----------------------------------------------------------------------------
#define MAX17048_DEFAULT_ADDRESS    0x36    // B0110110

// ----------------------------------------------------------------------------
// List all registers
// ----------------------------------------------------------------------------
#define MAX17048_RA_VCELL           0x02
#define MAX17048_RA_SOC             0x04
#define MAX17048_RA_MODE            0x06
#define MAX17048_RA_VERSION         0x08
#define MAX17048_RA_HIBRT           0x0A
#define MAX17048_RA_CONFIG          0x0C
#define MAX17048_RA_VALRT           0x14
#define MAX17048_RA_CRATE           0x16
#define MAX17048_RA_VRESET_ID       0x18
#define MAX17048_RA_STATUS          0x1A
#define MAX17048_RA_CMD             0xFE

// TABLE 0x40 to 0x7F: Configures battery parameters

// ----------------------------------------------------------------------------
// List register structures
// ----------------------------------------------------------------------------
#define MAX17048_MODE_QUICKSTART_BIT    14
#define MAX17048_MODE_ENABLE_BIT        13
#define MAX17048_MODE_HIBSTAT_BIT       12

#define MAX17048_CONFIG_SLEEP_BIT       7
#define MAX17048_CONFIG_ALSC_BIT        6
#define MAX17048_CONFIG_ALRT            5
#define MAX17048_CONFIG_ATHD_BIT        4 
#define MAX17048_CONFIG_ATHD_LENGTH     5
#define MAX17048_CONFIG_RCOMP_BIT       15
#define MAX17048_CONFIG_RCOMP_LENGTH    8

#define MAX17048_VALRT_MIN_BIT          15
#define MAX17048_VALRT_MIN_LENGTH       8
#define MAX17048_VALRT_MAX_BIT          7  
#define MAX17048_VALRT_MAX_LENGTH       8

#define MAX17048_VRESET_BIT             15
#define MAX17048_VRESET_LENGTH          7
#define MAX17048_VRESET_DIS_BIT	        8
#define MAX17048_ID_BIT                 7  
#define MAX17048_ID_LENGTH              8

#define MAX17048_STATUS_ENVR_BIT        14
#define MAX17048_STATUS_SC_BIT          13  
#define MAX17048_STATUS_HD_BIT          12
#define MAX17048_STATUS_VR_BIT          11
#define MAX17048_STATUS_VL_BIT          10
#define MAX17048_STATUS_VH_BIT          9
#define MAX17048_STATUS_RI_BIT          8

// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
#define MAX17048_VCELL_SCALE           78.125/1000000
#define MAX17048_SOC_SCALE             1/256


class MAX17048 {
    public:
        MAX17048();
        MAX17048(uint8_t address);

        void initialize();
        bool testConnection();

        
        uint16_t getVCELL();    
        uint16_t getSOC();        
        uint16_t getDeviceID();
        uint16_t getMode();
        void setMode(uint16_t mode);
        uint16_t getConfig();
        void setConfig(uint16_t config);
        

    private:
        uint8_t  devAddr;
        uint16_t buffer[2];
};

#endif /* _MAX17048_H_ */
