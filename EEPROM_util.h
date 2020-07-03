#include <EEPROM.h>

void write_int_EEPROM (int address, unsigned int value) {
  int cell = address << 2;
  byte b0 = (byte)value;
  EEPROM.write(cell, b0);
  byte b1 = (byte)(value >> 8);
  EEPROM.write(cell + 1, b1);
}

unsigned int read_int_EEPROM (int address) {
  int cell = address << 2;
  byte b0 = EEPROM.read(cell);
  byte b1 = EEPROM.read(cell + 1);
  unsigned int value = b0 | ((int)b1 << 8);
  return value;
}
