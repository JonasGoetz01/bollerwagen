#include <Arduino.h>
#include "variables.h"
#include "currentSensor.h"

void CurrentSensor::initialize() {
  float sensitivity [] = {
    40.0, //050B
    60.0, //050U
    20.0, //100B
    40.0, //100U
    13.0, //150B
    16.7, //150U
    10.0, //200B
    20.0 //200U
  };

  float quientcent_Output_voltage [] = {
    0.5, //050B
    0.12, //050U
    0.5, //100B
    0.12, //100U
    0.5, //150B
    0.12, //150U
    0.5, //200B
    0.12 //200U
  };

  const float FACTOR = sensitivity[CURRENTSENSOR_MODEL] / 1000;
  const float QOV = quientcent_Output_voltage [CURRENTSENSOR_MODEL] * CURRENTSENSOR_VCC;

  float voltage;
  float cutOff = FACTOR / CURRENTSENSOR_CUTOFFLIMIT;

  float voltage_raw = (CURRENTSENSOR_VCC / 1023.0) * analogRead(CURRENTSENSOR_PIN);
  voltage = voltage_raw - QOV + 0.007;
  float current = voltage / FACTOR;

  if(abs(voltage) > cutOff) {
    Serial.print("Voltage:");
    Serial.print(voltage, 3);
    Serial.print(", ");
    Serial.print("Current:");
    Serial.println(current, 2);
  } else {
    Serial.println("No Current");
  }
}