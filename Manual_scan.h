#include "Scan_units.h"
#include "steps_to_wavelength.h"
#include "Motor.h"

long calc_delta_steps(long delta) {
    long delta_steps;
//    Serial.print("SCAN_UNITS:");
//    Serial.println(scan_units);
    if (scan_units == ANGSTROM) {
        Serial.println("ANGSTROOOOM");
    }
//        long go_to_steps = calc_steps(wavelength + delta);
//        delta_steps = go_to_steps - motor_position;
//    } else {
        delta_steps = delta;
//    }
    return delta_steps;
}

void manual_scan() {
    unsigned int delta = 10;
    int motor_dir = 1;
    while (true) {
        Button butt = read_LCD_buttons();
        if (butt == LEFT) {
            Serial.println("LEFT");
            motor_dir = -1;
            long delta_steps = calc_delta_steps(delta);
            do_steps(delta_steps * motor_dir);
            lcd.setCursor(0, 1);
            lcd.print("                ");
        } else if (butt == RIGHT) {
            Serial.println("RIGHT");
            motor_dir = 1;
            long delta_steps = calc_delta_steps(delta);
            do_steps(delta_steps * motor_dir);
            lcd.setCursor(0, 1);
            lcd.print("                ");
        } else if (butt == UP) {
            Serial.println("UP");
            if (delta == 0)
                delta == 10;
            else if (delta < 10000)
                delta *= 10;
            lcd.setCursor(0, 1);
            lcd.print("                ");
        } else if (butt == DOWN) {
            Serial.println("DOWN");
            if (delta != 1)
                delta /= 10;
            lcd.setCursor(0, 1);
            lcd.print("                ");
        } else if (butt == SELECT) {
            return;
        }
        lcd.setCursor(0, 1);
        lcd.print(delta);
        lcd.setCursor(7, 1);
        lcd.print(motor_position);
    }
}
