#include <Arduino.h>
#include "variables.h"
#include "tempSensor.h"

void TempSensor::initialize(){
  pinMode(TEMP, INPUT);
}

uint16_t TempSensor::getTemperature() {
  // Temp auslesen
  return analogRead(TEMP);
}