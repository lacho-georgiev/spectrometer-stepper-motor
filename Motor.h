#ifndef SPECTRO_STEPPER_MOTOR_MOTOR_H
#define SPECTRO_STEPPER_MOTOR_MOTOR_H

// Define number of steps per revolution:
int steps_per_revolution; // number of steps for full motor revolution

const int PIN_SW = 2; // input pin from internal switch to stop motor when reach its bounds 

const int PIN_EN = 3; // output pin to motor driver to safe power

int manual_speed;

// callback function used to control stepper object
// steps_left is >= 0, steps_to_go can be positive or negative
bool pause(int steps_left, int steps_to_go, bool direction) {
    Button butt;
    butt = read_LCD_buttons();
//    sending_steps_interval != 0 &&
    if ((steps_to_go - steps_left) % 10 == 0) {
        char buffer[MAX_DISP_WIDTH + 1];
        if (scan_units == ANGSTROM) {
            wavelength = calc_wavelength(motor_position);
            long steps_to_go_wl = calc_wavelength(steps_to_go);
            long steps_left_wl = calc_wavelength(steps_left);
            long cur_pos;
            if (!direction) {
                cur_pos = wavelength + steps_to_go_wl + steps_left_wl;
            } else {
                cur_pos = wavelength + steps_to_go_wl - steps_left_wl;
            }
            long right_val = wavelength + steps_to_go_wl;
            format_char_array_for_int(buffer, right_val, cur_pos, right_val < 0);
//            format_char_array_for_int(buffer, wavelength + calc_wavelength(steps_to_go),
//            wavelength + done_steps_for_now);
        } else {
            long cur_pos;
            if (!direction) {
                cur_pos = motor_position + steps_to_go + steps_left;
            } else {
                cur_pos = motor_position + steps_to_go - steps_left;
            }
            long right_val = motor_position + steps_to_go;
            format_char_array_for_int(buffer, right_val, cur_pos, right_val < 0);
        }
        lcd.setCursor(0, 1);
        lcd.print(buffer);
    }
    return (butt == SELECT || digitalRead(PIN_SW) == LOW);
}

Stepper myStepper = Stepper(steps_per_revolution, 10, 11, 12, 13, &pause);

void do_steps(long steps) { // steps can be <0 because of the direction
    // enable motor driver
    digitalWrite(PIN_EN, HIGH);

    //needs some time the motor driver to become enabled
    delay(100);
    long done_steps;
    if (steps >= 0) {
        done_steps = (steps - myStepper.step(steps)); // steps returns steps_left
    } else {
        done_steps = (steps + myStepper.step(steps)); // steps returns steps_left
    }

    motor_position += done_steps;
    digitalWrite(PIN_EN, LOW);
    delay(100);

//  Serial.print("motor_pos: ");
//  Serial.println(motor_position);

    EEPROM.put(POSITION_ADDRESS, motor_position);
}

#endif // SPECTRO_STEPPER_MOTOR_MOTOR_H