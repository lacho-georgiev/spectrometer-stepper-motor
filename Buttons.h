#ifndef SPECTRO_STEPPER_MOTOR_BUTTONS_H
#define SPECTRO_STEPPER_MOTOR_BUTTONS_H

#include <HardwareSerial.h>

enum State {
    IDLE_STATE,
    TRANS_DOWN_STATE,
    PRESSED_STATE,
    TRANS_UP_STATE
};

enum Button {
    RIGHT,
    UP,
    DOWN,
    LEFT,
    SELECT,
    RESET,
    NONE
};

unsigned long lastTransTime = 0;
unsigned long transDelay = 20;

State state = IDLE_STATE;

Button lastButton = NONE;

Button getButton();

Button read_LCD_buttons() {
    Button button = getButton();
    if (state == IDLE_STATE) {
        if (button != NONE) {
            lastTransTime = millis();
            state = TRANS_DOWN_STATE;
        }
        return NONE;
    } else if (state == TRANS_DOWN_STATE) {
        if (millis() - lastTransTime < transDelay) {
            return NONE;
        }
        lastButton = button;
        state = PRESSED_STATE;
        return button;
    } else if (state == PRESSED_STATE) {
        button = getButton();
        if (button != lastButton) {
            lastTransTime = millis();
            lastButton = button;
            state = TRANS_UP_STATE;
        }
        return NONE;
    } else if (state == TRANS_UP_STATE) {
        if (millis() - lastTransTime > transDelay) {
            state = IDLE_STATE;
        }
        return NONE;
    }
}

Button getButton() {
    int read = analogRead(0);
    Button button;
    if (read < 195) {
        button = RIGHT;
        Serial.println("RIGHT");
    } else if (read < 270) {
        button = DOWN;
        Serial.println("DOWN");
    } else if (read < 357) {
        button = UP;
        Serial.println("UP");
    } else if (read < 529) {
        button = LEFT;
        Serial.println("LEFT");
    } else if (read < 738) {
        button = SELECT;
        Serial.println("SELECT");
    } else if (read < 902) {
        button = RESET;
    } else {
        button = NONE;
    }
    return button;
}

//    Button button = NONE;
//    if (read - lastRead > 50 ) {
//        lastButtonState = NONE;
//        return NONE;
//    }
#endif
