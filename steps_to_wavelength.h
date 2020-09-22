#include "Decimal.h"

#ifndef SPECTRO_STEPPER_MOTOR_STEPS_TO_WAVELENGTH_H
#define SPECTRO_STEPPER_MOTOR_STEPS_TO_WAVELENGTH_H

double calc_steps_double (long lambda) {
    double d1 = (double)lambda * (double)lambda * a2.to_double();
    double d2 = (double)lambda * a1.to_double();
    double d3 = a0.to_double();
    return d1 + d2 + d3;
}

// its expected that a0, a1, a2 are initialized global variables
///y = -0.000000005 * x.^2 + 0.07*x + -20000
long calc_steps (long lambda) {
    return calc_steps_double(lambda);
}

#endif //SPECTRO_STEPPER_MOTOR_STEPS_TO_WAVELENGTH_H
