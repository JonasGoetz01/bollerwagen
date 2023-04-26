#include <Arduino.h>
#include "tasks.h"
#include "../variables.h"

void sensorTask(void *parameter) {
  Variables *vars = (Variables*)parameter;
  while (1)
  {
    //@TODO
    //Sensoren checken
  Serial.println("CORE 0");
    vTaskDelay(SENSORCHECKINTERVAL / portTICK_PERIOD_MS);
  }
}