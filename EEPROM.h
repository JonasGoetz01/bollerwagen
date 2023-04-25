#ifndef EEPROM_H
#define EEPROM_H

class EEPROM {
public:
  void initialize();
  void saveValue();
  String getValue();
};

#endif