#ifndef SPECTRO_STEPPER_MOTOR_DECIMAL_H
#define SPECTRO_STEPPER_MOTOR_DECIMAL_H

struct Decimal {
    long value;
    long scale;
    float to_float() {
        return float(this->value)/float(this->scale);
    }
    double to_double() {
        return double(this->value)/double(this->scale);
    }
};

#endif //SPECTRO_STEPPER_MOTOR_DECIMAL_
