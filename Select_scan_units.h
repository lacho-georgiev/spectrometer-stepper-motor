#include "Scan_units.h"
#include "Buttons.h"
#include "LCD.h"

#ifndef SPECTRO_STEPPER_MOTOR_SELECT_SCAN_UNITS_H
#define SPECTRO_STEPPER_MOTOR_SELECT_SCAN_UNITS_H

void print_scan_units_selection(ScanUnits scan_units) {
    if (scan_units == ANGSTROM) {
        Serial.println("scan units: ANGSTROM");
        char buf[16];
        buf[0] = (byte)SYMBOL_ANGSTROM;
        for (int i = 1; i <= MAX_DISP_WIDTH; i++) {
            buf[i] = 32; // 32 is ascci code of space
        }
        lcd.setCursor(0, 1);
        lcd.print(buf);
    } else {
        Serial.println("scan units: ELSE");
        char buf[16];
        buf[0] = '#';
        buf[1] = 'M';
        for (int i = 2; i <= MAX_DISP_WIDTH; i++) {
            buf[i] = 32; // 32 is ascci code of space
        }
        lcd.setCursor(0, 1);
        lcd.print(buf);
    }
}

ScanUnits select_scan_units(ScanUnits scan_units) {
    print_scan_units_selection(scan_units);
    while (true) {
        Button butt = read_LCD_buttons();
        if (butt == UP || butt == DOWN) {
            scan_units = (scan_units == ANGSTROM) ? STEPS : ANGSTROM;
            print_scan_units_selection(scan_units);
        } else if (butt == SELECT) {
            return scan_units;
        }
    }
}

#endif //SPECTRO_STEPPER_MOTOR_SELECT_SCAN_UNITS_H
