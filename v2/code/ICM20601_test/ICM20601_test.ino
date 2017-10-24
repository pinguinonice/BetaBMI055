// I2C device class (I2Cdev) demonstration Arduino sketch for ICM20601 and MAX17048

// Version, date, description

// ver 0.1
// 2017/05/05 [BS]
// get IMU data, get lipo data, send via wifi, no reconnect 




// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include "Wire.h"

// ADAFRUITS ESP8266 WiFi lib is required
#include <ESP8266WiFi.h>

#include "I2Cdev.h"
#include "ICM20601.h"
#include "MAX17048.h"

// ICM20601 class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
ICM20601 imu;

// MAX17048 default I2C address is 0x36
MAX17048 lipo;


int8_t temp_max17048;
//uint16_t vbat;
//uint16_t perc;
double vbat;
double perc;

unsigned long time_millis;

int16_t ax, ay, az, gx, gy, gz, temp;

//                        t  t  t  t  ax    ay    az    gx    gy    gz    mx    my    mz
//                     0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22
uint8_t packet[23] = {'$',0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13,10};   


// beta-Platine spezifisch:
#define LED_R   0       // red
#define LED_G   13      // green
#define LED_B   2       // blue onboard ESP8266-12F
#define ON_PIN  14      // GPIO14 muss high, sonst Notaus    

bool blinkState = false;
int counter;


//  WIFI 
#define WIFI_OUTPUT
#ifdef WIFI_OUTPUT
   const char* ssid = "UPCBAF3DEE";
   const char* password= "rVzdYc3ybhma";
   const char* hostIP="192.168.188.36";
   const int httpPort = 6666;
   WiFiClient client; 
#endif // WIFI_OUTPUT


void setup() {
    Wire.begin(5,4);
    Serial.begin(115200);

    // initialize device
    Serial.println("Initializing I2C devices...");
    imu.initialize();
    imu.setSleepMode(0);

    lipo.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(imu.testConnection() ? "ICM20601 connection successful" : "ICM20601 connection failed");
    Serial.println(lipo.testConnection() ? "MAX17048 connection successful" : "MAX17048 connection failed");

    imu.setRate(0);
    imu.setGyrDLPF_CFG(ICM20601_CFG_DLPF_BW_250);
    imu.setGyrFchoise_b(ICM20601_GCONFIG_FCHOISE_B_DLPF_EN);
    imu.setFullScaleGyroRange(ICM20601_GYRO_FS_4000);
    imu.setFullScaleAccelRange(ICM20601_ACC_FS_32);
    imu.setAccFchoise_b(ICM20601_ACONFIG2_ACC_FCHOISE_B_DLPF_EN);
    imu.setAccDLPF_CFG(ICM20601_ACONFIG2_ACC_DLPF_CFG_219);


    #ifdef WIFI_OUTPUT
    // Verbindungsaufbau
        WiFi.begin(ssid, password);
        Serial.println();
        Serial.println();
        Serial.print("Connecting to ");
        Serial.println(ssid);
    
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
    
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());

        // TODO START: Keine TCP Verbindung, Block faellt weg
        // Use WiFiClient class to create TCP connections
        if (!client.connect(hostIP, httpPort)) {
            Serial.println("connection failed");
            return;
        }   
        client.print("Verbindung Hergestellt\n");
        // TODO ENDE
    #endif //WIFI_OUTPUT


    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);
    pinMode(ON_PIN, OUTPUT);
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, HIGH);
    digitalWrite(ON_PIN, HIGH);
}

void loop() {
    imu.getAcceleration(&ax, &ay, &az);
    imu.getRotation(&gx, &gy, &gz);
    imu.getTemperature(&temp);

    vbat = lipo.getVCELL() * MAX17048_VCELL_SCALE;
    perc = lipo.getSOC()   * MAX17048_SOC_SCALE;

    time_millis = millis();
    
    // sendAscii(time_millis);
    #ifdef WIFI_OUTPUT
        sendWifi(time_millis);
    #endif // WIFI_OUTPUT
    //sendBinary(time_millis);
    toggleLED();
    notaus();
}

void notaus() {
    if (perc < 30) {
        digitalWrite(ON_PIN, LOW);
    }
}

void sendWifi(unsigned long t) {

   client.setNoDelay(true);
   if (!client.connected() ) {
    Serial.println("connection failed");
    setup();
   } 

    client.print(t);
    client.print("\t");
    client.print(ax);
    client.print("\t");
    client.print(ay);
    client.print("\t");
    client.print(az);
    client.print("\t");
    client.print(gx);
    client.print("\t");
    client.print(gy);
    client.print("\t");
    client.print(gz);
    client.print("\t");
    client.print(temp);
    client.print("\t");
    client.print(perc);
    client.print("\t");
    client.println(vbat);
   
}

void sendAscii(unsigned long t) {
    
    Serial.print(t);
    Serial.print("\t");
    Serial.print(ax);
    Serial.print("\t");
    Serial.print(ay);
    Serial.print("\t");
    Serial.print(az);
    Serial.print("\t");
    Serial.print(gx);
    Serial.print("\t");
    Serial.print(gy);
    Serial.print("\t");
    Serial.print(gz);
    Serial.print("\t");
    Serial.print(temp);
    Serial.print("\t");
    Serial.print(perc);
    Serial.print("\t");
    Serial.println(vbat);
}

void sendBinary(unsigned long t) {

    memcpy(&packet[1],&t,4);
    memcpy(&packet[5],&ax,2);
    memcpy(&packet[7],&ay,2);
    memcpy(&packet[9],&az,2);
    memcpy(&packet[11],&gx,2);
    memcpy(&packet[13],&gy,2);
    memcpy(&packet[15],&gz,2);
    memcpy(&packet[17],&temp,2);
    memcpy(&packet[19],&perc,2);
    memcpy(&packet[21],&vbat,2);
    Serial.write(packet,23);
}

void toggleLED() {
    // toogle LED to indicate activity
    counter++;
    if (counter == 100){
        blinkState = !blinkState;
        digitalWrite(LED_R, blinkState);
        counter = 1;
    }
}


