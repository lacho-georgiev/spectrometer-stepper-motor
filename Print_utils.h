#include "Scan_units.h"
#include "LCD.h"

#ifndef SPECTRO_STEPPER_MOTOR_PRINT_UTILS_H
#define SPECTRO_STEPPER_MOTOR_PRINT_UTILS_H

void print_scan_units(ScanUnits scan_units) {
    if (scan_units == ANGSTROM) {
        lcd.setCursor(MAX_DISP_WIDTH, 0);
        lcd.write((byte) SYMBOL_ANGSTROM);
    } else {
        char buf[2];
        buf[0] = '#';
        buf[1] = 'M';
        lcd.setCursor(MAX_DISP_WIDTH - 1, 0);
        lcd.print(buf);
    }
}

#endif //SPECTRO_STEPPER_MOTOR_PRINT_UTILS_H
