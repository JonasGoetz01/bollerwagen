#import <Arduino.h>
#import "variables.h"
#import "motor.h"

void Motor::initialize(){
  //Motor
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
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
    analogWrite(RPWM, i);
    delay(25);
  }
}

void Motor::slowDown() {
  for (int i = 255; i > 30; i--){
    analogWrite(RPWM, i);
    delay(25);
  }
  analogWrite(RPWM, 0);
}
