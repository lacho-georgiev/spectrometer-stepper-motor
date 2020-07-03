#include <LiquidCrystal.h>
#include <Stepper.h>
#include "Menu.h"
#include "EEPROM_vars.h"
#include "EEPROM_util.h"
#include "Buttons.h"
#include "Symbols.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#include "Input.h"

unsigned int motor_position = read_int_EEPROM(POSITION_ADDRESS);
#include "Motor.h"

#include "Manual_scan.h"

#include "Go_to.h"

int addr = 0;

enum ProgramState {
  MENU_NAVIGATION_STATE,
  EXECUTE_FUNCTION_STATE
};

ProgramState program_state = MENU_NAVIGATION_STATE;

int child_indx;
TreeNode* parent_n;

int a0 = read_int_EEPROM(A0_ADDRESS),
    a1 = read_int_EEPROM(A1_ADDRESS),
    a2 = read_int_EEPROM(A2_ADDRESS);
void setup() {
  TreeNode* ptree = &tree;
  Serial.begin(115200);
  myStepper.setSpeed(manual_speed);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  inject_parents(ptree);
  child_indx = 0;
  parent_n = ptree;
  lcd.clear();
  lcd.createChar(0, down_arrow);
  lcd.createChar(1, up_arrow);
  lcd.createChar(2, run_arrow);
  
  pinMode(PIN_EN, OUTPUT);
  
  pinMode(PIN_SW, INPUT);
}

void loop() {
  Button  butt = read_LCD_buttons();

  String menu = parent_n->children[child_indx]->text;
  if (program_state == MENU_NAVIGATION_STATE) {
    if (butt == UP) {
      Serial.println(butt);
      if (child_indx > 0) child_indx--;
      lcd.clear();
    } else if (butt == DOWN) {
      if (child_indx < parent_n->children_size - 1) child_indx++;
      lcd.clear();
    } else if (butt == SELECT) {
      Serial.println("select");
    } else if (butt == RIGHT) {
      Serial.println("right");
      if (menu == "manual scan" || menu == "speed" || menu == "go_to" || menu == "steps per rev" || 
      menu == "Enter a0" || menu == "Enter a1" || menu == "Enter a2" || menu == "Enter a3") {
        lcd.setCursor(0, 0);
        program_state = EXECUTE_FUNCTION_STATE;
      }
      if (parent_n->children[child_indx]->children != NULL) {
        parent_n = parent_n->children[child_indx];
        child_indx = 0;
      }
      lcd.clear();
    } else if (butt == LEFT) {
      Serial.println("left");
      if (parent_n->parent != NULL) {
        parent_n = parent_n->parent;
        child_indx = 0;
      }
      lcd.clear();
    }
  } else if (program_state == EXECUTE_FUNCTION_STATE) {
    lcd.setCursor(menu.length() + 1, 0);
    lcd.write((byte)2);
     if (menu == "manual scan") {
      manual_scan();
      lcd.clear();
      lcd.noCursor();
      program_state = MENU_NAVIGATION_STATE;
    } else if (menu == "go_to") {
      go_on_position();
      lcd.clear();
      lcd.noCursor();
      program_state = MENU_NAVIGATION_STATE;
    } else if (menu == "speed") {
      manual_speed = input(read_int_EEPROM(SPEED_ADDRESS));
      myStepper.setSpeed(manual_speed);
      write_int_EEPROM(SPEED_ADDRESS, manual_speed);
      lcd.clear();
      lcd.noCursor();
      program_state = MENU_NAVIGATION_STATE;
    } else if (menu == "steps per rev") {
      STEPS_PER_REVOLUTION = input(read_int_EEPROM(STEPS_PER_REV_ADDRESS));
      write_int_EEPROM(STEPS_PER_REV_ADDRESS, STEPS_PER_REVOLUTION);
      myStepper = Stepper(STEPS_PER_REVOLUTION, 10, 11, 12, 13, &pause);
      lcd.clear();
      lcd.noCursor();
      program_state = MENU_NAVIGATION_STATE;
    } else if (menu == "Enter a0") {
      a0 = input(read_int_EEPROM(A0_ADDRESS));
      lcd.clear();
      lcd.noCursor();
      program_state = MENU_NAVIGATION_STATE;
    } else if (menu == "Enter a1") {
      a1 = input(read_int_EEPROM(A1_ADDRESS));
      lcd.clear();
      lcd.noCursor();
      program_state = MENU_NAVIGATION_STATE;
    } else if (menu == "Enter a2") {
      a2 = input(read_int_EEPROM(A2_ADDRESS));
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
  if (program_state == MENU_NAVIGATION_STATE) {
    if (child_indx == parent_n->children_size - 1) {
      lcd.setCursor(menu.length() + 1, 0);
      lcd.write((byte)0);
    }
    if (child_indx == 0) {
      lcd.setCursor(menu.length() + 1, 0);
      lcd.write((byte)1);
    }
  }
  
}
