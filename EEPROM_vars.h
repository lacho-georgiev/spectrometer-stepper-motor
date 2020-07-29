#include "Decimal.h"
#include "Scan_units.h"

int POSITION_ADDRESS;
int STEPS_PER_REV_ADDRESS;
int SPEED_ADDRESS;
int A0_ADDRESS;
int A1_ADDRESS;
int A2_ADDRESS;
int SCAN_UNITS_ADDRESS;

void init_addresses () {
  int eeAddress = 0;
  POSITION_ADDRESS = eeAddress;
  eeAddress += sizeof(long);
  STEPS_PER_REV_ADDRESS = eeAddress;
  eeAddress += sizeof(int);
  SPEED_ADDRESS = eeAddress;
  eeAddress += sizeof(int);
  A0_ADDRESS = eeAddress;
  eeAddress += sizeof(Decimal);
  A1_ADDRESS = eeAddress;
  eeAddress += sizeof(Decimal);
  A2_ADDRESS = eeAddress;
  eeAddress += sizeof(Decimal);
  SCAN_UNITS_ADDRESS = eeAddress;
  eeAddress += sizeof(ScanUnits);
}
