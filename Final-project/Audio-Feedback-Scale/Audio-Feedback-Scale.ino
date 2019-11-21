///////////// SETUP AUDIO ///////////////////
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//SoftwareSerial mySoftwareSerial(3, 1); // RX, TX for NodeMCU upload impossible
SoftwareSerial mySoftwareSerial(13, 15); // RX, TX for NodeMCU so upload is still possible
//SoftwareSerial mySoftwareSerial(16, 17); // RX, TX for ESP32 Thing

DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

///////////// SETUP FSR ///////////////////
#include "SensorFSR.h"

//const int fsrPin = A7; // FSR is connected to analog 7 on Arduino Nano
const int fsrPin = A0; // FSR is connected to analog A0 on NodeMCU
bool DEBUG = true;

SensorFSR sensorFSR(fsrPin, DEBUG); // Create object sensorFSR

///////////// SETUP GRAPHICS ///////////////////
#include <Wire.h>
#include <SPI.h>
#include "SH1106.h"
#include "SH1106Ui.h"
#include "emojis.h"

// Pin definitions for I2C
#define OLED_SDA    D2  // pin 14
#define OLED_SDC    D4  // pin 12
#define OLED_ADDR   0x3C

SH1106   display(OLED_ADDR, OLED_SDA, OLED_SDC);
SH1106Ui ui     ( &display );

///////////// SETUP ///////////////////
void setup() {
  Serial.begin(115200);
  // Setup AUDIO
  //DFplayerSetup();

  // Setup GRAPHICS
  setupUI();

}

///////////// LOOP ///////////////////
void loop() {
  // AUDIO loop
  //DFplayerTest();

  // FSR loop
  sensorFSR.readValue();
  sensorFSR.convertToMass();
  sensorFSR.converToReality();

  // GRAPHICS loop
  timeBudget();

}
