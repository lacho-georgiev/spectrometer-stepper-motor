#include "Scan_units.h"
#include "steps_to_wavelength.h"
#include "Motor.h"
#include "Print_utils.h"

long calc_delta_steps(long delta) {
    long delta_steps;
    if (scan_units == ANGSTROM) {
        wavelength = calc_wavelength(motor_position);
        long go_to_steps = calc_steps(wavelength + delta);
        delta_steps = go_to_steps - motor_position;
        Serial.print("MC: goto: ");
        Serial.println(go_to_steps);
        Serial.print("MC: bf_RESULT: ");
        Serial.println(calc_wavelength(go_to_steps));
        Serial.print("MC: RESULT: ");
        Serial.println(calc_wavelength(delta_steps + motor_position));
        Serial.print("MC: wavelength: ");
        Serial.println(wavelength);
        Serial.print("MC: wavelength + delta: ");
        Serial.println(wavelength + delta);

    } else {
        delta_steps = delta;
    }
    return delta_steps;
}

void manual_scan() {
    unsigned int delta = 10;
    int motor_dir = 1;
    print_scan_units(scan_units);
    while (true) {
        Button butt = read_LCD_buttons();
        if (butt == LEFT) {
            motor_dir = -1;
            long delta_steps = calc_delta_steps(delta);
            do_steps(delta_steps * motor_dir);
            lcd.setCursor(0, 1);
            lcd.print("                ");
        } else if (butt == RIGHT) {
            motor_dir = 1;
            long delta_steps = calc_delta_steps(delta);
            do_steps(delta_steps * motor_dir);
            lcd.setCursor(0, 1);
            lcd.print("                ");
        } else if (butt == UP) {
            if (delta == 0)
                delta == 10;
            else if (delta < 10000)
                delta *= 10;
            lcd.setCursor(0, 1);
            lcd.print("                ");
        } else if (butt == DOWN) {
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
        if (scan_units == ANGSTROM) {
            wavelength = calc_wavelength(motor_position);
            lcd.print(wavelength);
        } else {
            lcd.print(motor_position);
        }
    }
}
