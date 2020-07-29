#include "Decimal.h"

#ifndef SPECTRO_STEPPER_MOTOR_STEPS_TO_WAVELENGTH_H
#define SPECTRO_STEPPER_MOTOR_STEPS_TO_WAVELENGTH_H
// its expected that a0, a1, a2 are initialized global variables

long calc_steps (int lambda) {
    return lambda*lambda * a2.to_float() + lambda * a1.to_float() + a0.to_float();
}


#endif //SPECTRO_STEPPER_MOTOR_STEPS_TO_WAVELENGTH_H
