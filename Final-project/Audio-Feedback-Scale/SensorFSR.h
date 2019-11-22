/*
  SensorFSR.h - Class for reading FSR sensor.
  Created by Abel Matser, 21 November 2019
*/

#ifndef SensorFSR_h
#define SensorFSR_h

class SensorFSR
{
  public:
    SensorFSR(int pin, bool DEBUG);
    void readValue();
    void convertToMass();
    void converToReality();

    // Output value
    int outputMass;

  private:
    int _pin;
    bool _DEBUG;
    float _fsrMass;
    int _fsrReading;

    // Linear approximation of FSR
    //    const float _convertToMass_a = 3.14;
    //    const float _convertToMass_b = -103.5;
    const float _convertToMass_a = 3.46;
    const float _convertToMass_b = -129.55;

};

SensorFSR::SensorFSR(int pin, bool DEBUG)
{
  pinMode(pin, INPUT);
  _pin = pin;
  _DEBUG = DEBUG;
}

void SensorFSR::readValue()
{
  _fsrReading = analogRead(_pin);
  if (_DEBUG)
  {
    Serial.print("Analog reading = ");
    Serial.println(_fsrReading);
  }
}

void SensorFSR::convertToMass()
{
  _fsrMass = _convertToMass_a * _fsrReading + _convertToMass_b;
  if (_DEBUG)
  {
    Serial.print("Mass reading = ");
    Serial.println(_fsrMass);
  }
}

void SensorFSR::converToReality()
{
  if (_fsrMass < 50)
  {
    outputMass = -1;
  }
  else if ((_fsrMass > 50) && (_fsrMass < 150))
  {
    outputMass = 100;
  }
  else if ((_fsrMass > 150) && (_fsrMass < 250))
  {
    outputMass = 200;
  }
  else if ((_fsrMass > 250) && (_fsrMass < 350))
  {
    outputMass = 300;
  }
  else if ((_fsrMass > 350) && (_fsrMass < 450))
  {
    outputMass = 400;
  }
  else if ((_fsrMass > 450) && (_fsrMass < 550))
  {
    outputMass = 500;
  }
  else if ((_fsrMass > 550) && (_fsrMass < 650))
  {
    outputMass = 600;
  }
  else if ((_fsrMass > 650) && (_fsrMass < 750))
  {
    outputMass = 700;
  }
  else if ((_fsrMass > 750) && (_fsrMass < 850))
  {
    outputMass = 800;
  }

  //  if (_DEBUG)
  //  {
  Serial.print("Output mass reading = ");
  Serial.println(outputMass);
  //  }
}
#endif
