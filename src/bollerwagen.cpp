#include <Arduino.h>
#include <Wire.h>
#include "variables.h"
#include "./buzzer/buzzer.h"
#include "./motor/motor.h"
#include "./display/display.h"
#include "./currentSensor/currentSensor.h"
#include "./rotary/rotary.h"
#include "./EEPROM/EEPROM.h"
#include "./switch/switch.h"
#include "./tempSensor/tempSensor.h"
#include "./tasks/tasks.h"


Buzzer buzzer;
Motor motor;
Display oled;
TempSensor tempSensor;

Variables variables;


void setup() {
  Serial.begin(9600);

  Serial.println("Welcome to Bollerwagen!");

  buzzer.initialize();
  buzzer.startSound();

  oled.initialize();
  oled.testText();

  motor.initialize();
  motor.enable();
  //motor.accelerate();
  //motor.slowDown();
  motor.disable();

  tempSensor.initialize();

  //Tasks definieren
  //                      function     description    ram   parameters         prio exception core
  xTaskCreatePinnedToCore(&sensorTask, "SENSOR_TASK", 2048, (void*)&variables, 1,   NULL,     0);
}

void loop() {
  Serial.print(tempSensor.getTemperature());
  Serial.println(" C");
  vTaskDelay(SENSORCHECKINTERVAL / 2 / portTICK_PERIOD_MS);
}
