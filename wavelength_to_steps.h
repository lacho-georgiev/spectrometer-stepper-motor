#include "steps_to_wavelength.h"

#ifndef SPECTRO_STEPPER_MOTOR_WAVELENGTH_TO_STEPS_H
#define SPECTRO_STEPPER_MOTOR_WAVELENGTH_TO_STEPS_H

#define LAMBDA_MIN 20000 // in 0.1 Angstrom
#define LAMBDA_MAX 200000 // in 0.1 Angstrom
/// y = 0.00001*x.^2 + 0.05*x - 5000
long calc_wavelength (double s, long lambda_min, long lambda_max) {
    long lambda = (lambda_max + lambda_min) / 2;
    if (lambda == lambda_min || lambda == lambda_max) {
        return lambda;
    }
    double s_guess = calc_steps_double(lambda);
    if (s_guess < s) {
        return calc_wavelength(s, lambda, lambda_max);
    } else if (s_guess > s) {
        return calc_wavelength(s, lambda_min, lambda);
    } else if (s_guess == s) {
        return lambda;
    }
}

long calc_wavelength (double s) {
    return calc_wavelength(s, LAMBDA_MIN, LAMBDA_MAX);
}

#endif //SPECTRO_STEPPER_MOTOR_WAVELENGTH_TO_STEPS_H
