#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Stepper.h>
#include "Menu.h"
#include "EEPROM_vars.h"
#include "EEPROM.h"
#include "Buttons.h"
#include "Symbols.h"
#include "LCD.h"
#include "Decimal.h"

Decimal a0, a1, a2;

#include "steps_to_wavelength.h"
#include "wavelength_to_steps.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#include "Input.h"

long motor_position;
long wavelength;

#include "Motor.h"

#include "Scan_units.h"

ScanUnits scan_units;

#include "Manual_scan.h"

#include "Go_to.h"
#include "Select_scan_units.h"

int addr = 0;

enum ProgramState {
    MENU_NAVIGATION_STATE,
    EXECUTE_FUNCTION_STATE
};

ProgramState program_state = MENU_NAVIGATION_STATE;

int child_indx;
TreeNode *parent_n;

void setup() {
    init_addresses();
    EEPROM.get(POSITION_ADDRESS, motor_position);
    EEPROM.get(STEPS_PER_REV_ADDRESS, steps_per_revolution);
    EEPROM.get(SPEED_ADDRESS, manual_speed);
//    a2.value = 1;
//    a2.scale = 1000;
    EEPROM.get(A0_ADDRESS, a0);
    EEPROM.get(A1_ADDRESS, a1);
    EEPROM.get(A2_ADDRESS, a2);
    EEPROM.get(SCAN_UNITS_ADDRESS, scan_units);
    if (scan_units == ANGSTROM) {
        wavelength = calc_wavelength(motor_position);
    }
    TreeNode *ptree = &root;
    Serial.begin(115200);
    myStepper.setSpeed(manual_speed);
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    inject_parents(ptree);
    child_indx = 0;
    parent_n = ptree;
    lcd.clear();
    lcd.createChar(SYMBOL_DOWN_ARROW, down_arrow);
    lcd.createChar(SYMBOL_UP_ARROW, up_arrow);
    lcd.createChar(SYMBOL_RUN_ARROW, run_arrow);
    lcd.createChar(SYMBOL_ANGSTROM, angtrom);

    pinMode(PIN_EN, OUTPUT);

    pinMode(PIN_SW, INPUT);

    myStepper = Stepper(steps_per_revolution, 10, 11, 12, 13, &pause);
    myStepper.setSpeed(manual_speed);

}

void loop() {
    Button butt = read_LCD_buttons();

    String menu = parent_n->children[child_indx]->text;
    if (program_state == MENU_NAVIGATION_STATE) {
        if (butt == UP) {
            if (child_indx > 0) child_indx--;
            lcd.clear();
        } else if (butt == DOWN) {
            if (child_indx < parent_n->children_size - 1) child_indx++;
            lcd.clear();
        } else if (butt == SELECT) {
            if (parent_n->parent != NULL) {
                parent_n = parent_n->parent;
                child_indx = 0;
            }
            lcd.clear();
        } else if (butt == RIGHT) {
            if (menu == "Manual scan" || menu == "speed" || menu == "Go to" || menu == "steps per rev" ||
                menu == "Enter a0" || menu == "Enter a1" || menu == "Enter a2" || menu == "Enter a3" ||
                menu == "set motor pos" || menu == "scan units") {
                lcd.setCursor(0, 0);
                program_state = EXECUTE_FUNCTION_STATE;
            }
            if (parent_n->children[child_indx]->children != NULL) {
                parent_n = parent_n->children[child_indx];
                child_indx = 0;
            }
            lcd.clear();
        }
    } else if (program_state == EXECUTE_FUNCTION_STATE) {
        lcd.setCursor(menu.length() + 1, 0);
        if (menu == "Manual scan") {
            manual_scan();
            lcd.clear();
            lcd.noCursor();
            program_state = MENU_NAVIGATION_STATE;
        } else if (menu == "Go to") {
            go_on_position();
            lcd.clear();
            lcd.noCursor();
            program_state = MENU_NAVIGATION_STATE;
        } else if (menu == "speed") {
            manual_speed = input_int(EEPROM.read(SPEED_ADDRESS));
            myStepper.setSpeed(manual_speed);
            EEPROM.put(SPEED_ADDRESS, manual_speed);
            lcd.clear();
            lcd.noCursor();
            program_state = MENU_NAVIGATION_STATE;
        } else if (menu == "steps per rev") {
            steps_per_revolution = input_int(EEPROM.read(STEPS_PER_REV_ADDRESS));
            EEPROM.put(STEPS_PER_REV_ADDRESS, steps_per_revolution);
            myStepper = Stepper(steps_per_revolution, 10, 11, 12, 13, &pause);
            myStepper.setSpeed(manual_speed);
            lcd.clear();
            lcd.noCursor();
            program_state = MENU_NAVIGATION_STATE;
        } else if (menu == "set motor pos") {
            print_scan_units(STEPS);
            motor_position = input_long(motor_position);
            EEPROM.put(POSITION_ADDRESS, motor_position);
            lcd.clear();
            lcd.noCursor();
            program_state = MENU_NAVIGATION_STATE;
        } else if (menu == "Enter a0") {
            a0 = input_decimal(a0);
            EEPROM.put(A0_ADDRESS, a0);
            lcd.clear();
            lcd.noCursor();
            program_state = MENU_NAVIGATION_STATE;
        } else if (menu == "Enter a1") {
            a1 = input_decimal(a1);
            EEPROM.put(A1_ADDRESS, a1);
            lcd.clear();
            lcd.noCursor();
            program_state = MENU_NAVIGATION_STATE;
        } else if (menu == "Enter a2") {
            a2 = input_decimal(a2);
            EEPROM.put(A2_ADDRESS, a2);
            lcd.clear();
            lcd.noCursor();
            program_state = MENU_NAVIGATION_STATE;
        } else if (menu == "scan units") {
            ScanUnits new_scan_units = select_scan_units(scan_units);
            if (new_scan_units == ANGSTROM) {
                wavelength = calc_wavelength(motor_position);
            }
            scan_units = new_scan_units;
            EEPROM.put(SCAN_UNITS_ADDRESS, scan_units);
            lcd.clear();
            lcd.noCursor();
            program_state = MENU_NAVIGATION_STATE;
        }
        menu = parent_n->parent->text;
        child_indx = 0;
    }

    menu = parent_n->children[child_indx]->text;
    lcd.setCursor(0, 0);

    lcd.print(menu);
}
