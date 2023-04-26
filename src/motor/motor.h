#ifndef MOTOR_H
#define MOTOR_H

class Motor {
public:
  void initialize();
  void accelerate();
  void slowDown();
  void disable();
  void enable();
  void run(bool, u_int8_t);
};

#endif