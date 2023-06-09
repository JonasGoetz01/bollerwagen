#include <Arduino.h>
#include "tasks.h"
#include "../variables.h"
#include "../motor/motor.h"

Motor taskMotor;

void sensorTask(void *parameter) {
  Variables *vars = (Variables*)parameter;
  while (1)
  {
    //@TODO
    //Sensoren checken
    if(vars->debug){
        Serial.println("Check sensors");
    }
    vTaskDelay(SENSORCHECKINTERVAL / portTICK_PERIOD_MS);
  }
}

void serialTask(void *parameter) {
  Variables *vars = (Variables*)parameter;
  String data = "";
  while (1)
  {
    if(Serial2.available()){
        data = Serial2.readStringUntil('\n');
    }
    //@TODO
    //Sensoren checken
    if(vars->debug){
        Serial.println("Check serial");
        Serial.println(data);
    }
  }
  vTaskDelay(1 / portTICK_PERIOD_MS);
}

void triggerChange(void *parameter) {
  Variables *vars = (Variables*)parameter;
  while (1)
  {
    if(!vars->trigger) {
        if(digitalRead(TRIGGERPIN) == HIGH){
            vars->trigger = true;
            if(vars->debug){
                Serial.println("TRIGGER DOWN");
            }
        }
    }

    if(vars->trigger) {
        if(digitalRead(TRIGGERPIN) == LOW){
            vars->trigger = false;
            if(vars->debug){
                Serial.println("TRIGGER UP");
            }
        }
    }
    vTaskDelay(TRIGGERCHANGEINTERVAL / portTICK_PERIOD_MS);
  }
}

void motorSpeed(void *parameter) {
  Variables *vars = (Variables*)parameter;
  while (1)
  {
    if(vars->trigger){
        vars->desiredMotorSpeed = map(255, 0, 255, 0, vars->limitedMotorSpeed);
        if(vars->currentMotorSpeed < vars->desiredMotorSpeed){
            if(vars->currentMotorSpeed + vars->acceleration * 100 > 255){
                vars->currentMotorSpeed = 255;
            } else {
                vars->currentMotorSpeed += vars->acceleration * 100;
            }
        }
    }
    if(!vars->trigger){
        vars->desiredMotorSpeed = map(0, 0, 255, 0, vars->limitedMotorSpeed);
        if(vars->currentMotorSpeed > vars->desiredMotorSpeed){
            if(vars->currentMotorSpeed - vars->acceleration * 100 < 0){
                vars->currentMotorSpeed = 0;
            } else {
                vars->currentMotorSpeed -= vars->acceleration * 100;
            }
        }
    }

    taskMotor.run(vars->motorDir, vars->currentMotorSpeed);

    if(vars->debug){
        Serial.print("Enabled:");
        Serial.print(vars->motorEnabled);
        Serial.print(", ");
        Serial.print("DesiredSpeed:");
        Serial.print(vars->desiredMotorSpeed);
        Serial.print(", ");
        Serial.print("CurrentSpeed:");
        Serial.print(vars->currentMotorSpeed);
        Serial.print(", ");
        Serial.print("ENR:");
        Serial.print(digitalRead(REN));
        Serial.print(", ");
        Serial.print("ENL:");
        Serial.println(digitalRead(LEN));
    }

    vTaskDelay(MOTORSPEEDINTERVAL / portTICK_PERIOD_MS);
  }
}