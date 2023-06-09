#include <Arduino.h>
#include "../variables.h"
#include "motor.h"
#include "../currentSensor/currentSensor.h"

CurrentSensor currentSensor;
Variables varsMotor;

void Motor::initialize(){
  //Motor
  // pinMode(RPWM, OUTPUT);
  // pinMode(LPWM, OUTPUT);
  pinMode(LEN, OUTPUT);
  pinMode(REN, OUTPUT);
}

void Motor::enable(){
  digitalWrite(REN, HIGH);
  digitalWrite(LEN, HIGH);
}

void Motor::disable(){
  digitalWrite(REN, LOW);
  digitalWrite(LEN, LOW);
  analogWrite(RPWM, 0);
}

void Motor::accelerate() {
  //Motor beschleunigen und abbremsen
  for (int i = 30; i < 255; i++){
    analogWrite(LPWM, i);
    //currentSensor.initialize();
    delay(50);
  }
}

void Motor::slowDown() {
  for (int i = 255; i > 30; i--){
    analogWrite(LPWM, i);
    //currentSensor.initialize();
    //delay(50);
  }
  analogWrite(RPWM, 0);
}

void Motor::run(bool dir, uint8_t speed){

  if(dir) {
    ledcWrite(0, speed);
    //dacWrite(LPWM, vars->currentMotorSpeed);
    //analogWrite(RPWM, 0);
  } else {
    //analogWrite(LPWM, 0);
    ledcWrite(0, 0);
    //dacWrite(RPWM, vars->currentMotorSpeed);
  }
}
