#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <stdio.h>

#include "Wire.h"
#include "I2Cdev.h"
#include "MAX17048.h"
#include "BMI055.h"
// BMI055 default I2C address is 0x18 and 0x68
BMI055 imu;
// MAX17048 default I2C address is 0x36
MAX17048 lipo;

WiFiUDP Udp;

#define LED_R   0       // red
#define LED_G   13      // green
#define LED_B   2       // blue onboard ESP8266-12F
#define ON_PIN  14      // GPIO14 muss high, sonst Notaus    

#define SSID  "iPippo"
#define PW    "hallowelt"
#define TARGET_IP "172.20.10.4"
#define TARGET_PORT 7000
#define MESSAGE_SIZE 255

uint8_t data[32000];
uint16_t counter = 0;

bool error = false;
uint32_t errorT;

union ByteSplit2 {
  int16_t in;
  struct S {
    byte b1, b2;
  } out;
};
union ByteSplit4 {
  uint32_t in;
  struct S {
    byte b1, b2, b3, b4;
  } out;
};

void setup() {
  Wire.begin(5, 4);
  Serial.begin(115200);
  Serial.println("booting...");
  Serial.print("Connecting to "SSID);
  WiFi.begin(SSID, PW);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  imu.initialize();
  
  if (!imu.testConnection()) {
    Serial.println("IMU test failed");
    delay(100);
    ESP.restart();
  }

  // Config Bandwidth and Range has to be adjusted to your expected measurments
  imu.setRangeAcc(BMI055_ACC_RANGE_16G);
  imu.setRangeGyr(BMI055_GYR_RANGE_2000);

  imu.setBandwidthAcc(BMI055_ACC_BW_500);
  imu.setBandwidthGyr(BMI055_GYR_BW_523);

  lipo.initialize();

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
  ByteSplit4 t;
  t.in = (uint32_t)millis();
  //  t.in = 12313;
  data[counter++] = t.out.b1;
  data[counter++] = t.out.b2;
  data[counter++] = t.out.b3;
  data[counter++] = t.out.b4;

  imu.getAcceleration(&data[counter++], &data[counter++], &data[counter++], &data[counter++], &data[counter++], &data[counter++]);

  
  imu.getTurnRate(&data[counter++], &data[counter++], &data[counter++], &data[counter++], &data[counter++], &data[counter++]);

  if (counter >= 160) {//160 equals 10x ( 2byte*6sensors + 4byte time )
    sendBuffer();
    counter = 0;
  }
}

bool sendBuffer() {
  int8_t perc = (int)(lipo.getSOC()   * MAX17048_SOC_SCALE);
  uint8_t vbatt = (int)(lipo.getVCELL() * MAX17048_VCELL_SCALE * 10);
  bool okay = true;

  ByteSplit4 s;
  s.in = WiFi.RSSI();
  data[counter++] = s.out.b1;
  data[counter++] = s.out.b2;
  data[counter++] = s.out.b3;
  data[counter++] = s.out.b4;
  data[counter++] = perc;

  for ( uint8_t iTry = 0; iTry < 10; iTry++) {
    okay = sendUDP(data, counter, TARGET_PORT);
    if (okay == true)
      break;
    delay(1);
  }
  if (okay == false) {
    delay(0);
    byte msg[32] = "finnaly failed to send message\n";
    sendUDP(msg, 32, 7001);
    Serial.println("finnaly failed to send message\n");
    digitalWrite(LED_R, LOW);
    error = true;
    errorT = (uint32_t)millis();
    delay(0);
  }
  else if (error == true && ((uint32_t)millis() - errorT) >= 1000) {
    byte msg[50] = "finnaly failed to send message\n";
    sendUDP(msg, 32, 7001);
    error = false;
    digitalWrite(LED_R, HIGH);
  }
  counter = 0;
}

bool sendUDP(byte* test, uint8_t msgSize, uint16_t port) {
  if ( Udp.beginPacket(TARGET_IP, port) != 1 ) {
    return false;
  }
  Udp.write(test, msgSize);
  if ( Udp.endPacket() != 1) {
    return false;
  }
  return true;
}

