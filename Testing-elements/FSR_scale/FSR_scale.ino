/* FSR testing sketch.

  Connect one end of FSR to power, the other end to Analog 0.
  Then connect one end of a 10K resistor from Analog 0 to ground

  For more information see www.ladyada.net/learn/sensors/fsr.html */

#include "SensorFSR.h"

int fsrPin = A7; // FSR is connected to analog 0
bool DEBUG = true;

// Create object sensorFSR
SensorFSR sensorFSR(fsrPin, DEBUG);

void setup(void) {
  Serial.begin(115200);   // We'll send debugging information via the Serial monitor


}

void loop(void) {

  sensorFSR.readValue();
  sensorFSR.convertToMass();
  sensorFSR.converToReality();

  Serial.println("--------------------");
  delay(1000);
}
