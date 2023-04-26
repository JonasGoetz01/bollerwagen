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

#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "driver/ledc.h"


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

  Serial.println("Welcome to Bollerwagen!");

  //buzzer.initialize();
  //buzzer.startSound();

  //oled.initialize();
  //oled.testText();
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(RPWM, ledChannel);
  //delay(10000);

  motor.initialize();
  motor.enable();

  tempSensor.initialize();

  //Tasks definieren
  //                      function     description    ram   parameters         prio exception core
  xTaskCreatePinnedToCore(&sensorTask, "SENSOR_TASK", 2048, (void*)&variables, 1,   NULL,     1);
  xTaskCreatePinnedToCore(&triggerChange, "TRIGGER_CHANGE", 2048, (void*)&variables, 1,   NULL,     1);
  xTaskCreatePinnedToCore(&motorSpeed, "MOTOR_SPEED", 2048, (void*)&variables, 1,   NULL,     1);

  pinMode(TRIGGERPIN, INPUT_PULLUP);
}

void loop() {
  // if(1) {
  //   ledcWrite(0, 255);
  //   //dacWrite(LPWM, vars->currentMotorSpeed);
  //   //analogWrite(RPWM, 0);
  // } else {
  //   //analogWrite(LPWM, 0);
  //   ledcWrite(0, 0);
  //   //dacWrite(RPWM, vars->currentMotorSpeed);
  // }
  delay(100 / portTICK_PERIOD_MS);
}
