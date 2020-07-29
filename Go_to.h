#include "Print_utils.h"

void go_on_position() {
    print_scan_units(scan_units);
    long go_on_position;
    if (scan_units == ANGSTROM) {
        long go_on_wavelength = input_long(wavelength);
        go_on_position = calc_steps(go_on_wavelength);
    } else {
        go_on_position = input_long(motor_position);
    }
    do_steps(go_on_position - motor_position);
}
