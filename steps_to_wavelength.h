#include "Decimal.h"

#ifndef SPECTRO_STEPPER_MOTOR_STEPS_TO_WAVELENGTH_H
#define SPECTRO_STEPPER_MOTOR_STEPS_TO_WAVELENGTH_H
// its expected that a0, a1, a2 are initialized global variables

long calc_steps (int lambda) {
    float d1 = (float)lambda * (float)lambda * a2.to_float();
    float d2 = (float)lambda * a1.to_float();
    float d3 = a0.to_float();
//    Serial.print("d1: ");
//    Serial.println(d1);
//    Serial.print("d2: ");
//    Serial.println(d2);
//    Serial.print("d3: ");
//    Serial.println(d3);
    return d1 + d2 + d3;
}


#endif //SPECTRO_STEPPER_MOTOR_STEPS_TO_WAVELENGTH_H
