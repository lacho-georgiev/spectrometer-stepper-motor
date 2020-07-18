#include <EEPROM.h>

//void write_int_EEPROM (int address, int value) {
//  int cell = address << 2;
//  byte b0 = (byte)value;
//  EEPROM.write(cell, b0);
//  byte b1 = (byte)(value >> 8);
//  EEPROM.write(cell + 1, b1);
//}
//
//int read_int_EEPROM (int address) {
//  int cell = address << 2;
//  byte b0 = EEPROM.read(cell);
//  byte b1 = EEPROM.read(cell + 1);
//  unsigned int value = b0 | ((int)b1 << 8);
//  return value;
//}
//
//void write_long_EEPROM (int address_high, int address_low, long value) {
//  int high_val = int(value>>16);
//  int low_val = int(value);
//  Serial.print("write: high_val ");
//  Serial.println(high_val);
//  Serial.print("write: low_val ");
//  Serial.println(low_val);
//  write_int_EEPROM(address_high, high_val);
//  write_int_EEPROM(address_low, low_val);
//}
//
//long read_long_EEPROM (int address_high, int address_low) {
//  long high_val = 0;
//  int low_val = 0;
//  Serial.print("read: high_val ");
//  Serial.println(high_val);
//  Serial.print("read: low_val ");
//  Serial.println(low_val);
//  return (((long)read_int_EEPROM(address_high)) << 16 + read_int_EEPROM(address_low));
//}
