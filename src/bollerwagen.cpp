#include <Arduino.h>
#include <Wire.h>
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "driver/ledc.h"

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

const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

Variables variables;


void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);

  Serial.println("Welcome to Bollerwagen!");

  buzzer.initialize();
  //buzzer.startSound();

  oled.initialize();
  //oled.testText();
  
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(RPWM, ledChannel);

  motor.initialize();
  motor.enable();

  tempSensor.initialize();

  //Tasks definieren
  //                      function     description    ram   parameters         prio exception core
  xTaskCreatePinnedToCore(&sensorTask, "SENSOR_TASK", 2048, (void*)&variables, 1,   NULL,     1);
  xTaskCreatePinnedToCore(&triggerChange, "TRIGGER_CHANGE", 2048, (void*)&variables, 1,   NULL,     1);
  //xTaskCreatePinnedToCore(&serialTask, "SERIAL_TASK", 2048, (void*)&variables, 1,   NULL,     1);
  xTaskCreatePinnedToCore(&motorSpeed, "MOTOR_SPEED", 2048, (void*)&variables, 1,   NULL,     0);

  pinMode(TRIGGERPIN, INPUT_PULLUP);
}

void loop() {
  delay(100 / portTICK_PERIOD_MS);
}
