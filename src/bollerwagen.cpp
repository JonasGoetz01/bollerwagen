#include <Arduino.h>
#include <Wire.h>
#include "pitches.h"
#include "variables.h"
#include "buzzer.h"
#include "motor.h"
#include "display.h"
#include "currentSensor.h"
#include "rotary.h"
#include "EEPROM.h"
#include "switch.h"
#include "tempSensor.h"


Buzzer buzzer;
Motor motor;
Display oled;
TempSensor tempSensor;

void setup() {
  Serial.begin(9600);

  Serial.println("Welcome to Bollerwagen!");

  buzzer.initialize();
  buzzer.startSound();

  oled.initialize();
  oled.testText();

  motor.initialize();
  motor.enable();
  motor.accelerate();
  motor.slowDown();
  motor.disable();

  tempSensor.initialize();

  
}

void loop() {
  Serial.print(tempSensor.getTemperature());
  Serial.println(" C");
  delay(2000);
}
