#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

class TempSensor {
public:
  void initialize();
  uint16_t getTemperature();
};

#endif