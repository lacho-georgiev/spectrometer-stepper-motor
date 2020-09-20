#include "steps_to_wavelength.h"

#ifndef SPECTRO_STEPPER_MOTOR_WAVELENGTH_TO_STEPS_H
#define SPECTRO_STEPPER_MOTOR_WAVELENGTH_TO_STEPS_H

#define LAMBDA_MIN 0 // in Angstrom
#define LAMBDA_MAX 20000 // in Angstrom

long calc_wavelength (long s, long lambda_min, long lambda_max) {
    long lambda = (lambda_max + lambda_min) / 2;
    if (lambda == lambda_min || lambda == lambda_max) {
        return lambda;
    }
    long s_guess = calc_steps(lambda);
    if (s_guess < s) {
        return calc_wavelength(s, lambda, lambda_max);
    } else if (s_guess > s) {
        return calc_wavelength(s, lambda_min, lambda);
    } else if (s_guess == s) {
        return lambda;
    }
}

long calc_wavelength (long s) {
    return calc_wavelength(s, LAMBDA_MIN, LAMBDA_MAX);
}

#endif //SPECTRO_STEPPER_MOTOR_WAVELENGTH_TO_STEPS_H
