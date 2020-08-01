#ifndef SPECTRO_STEPPER_MOTOR_MOTOR_H
#define SPECTRO_STEPPER_MOTOR_MOTOR_H
// Define number of steps per revolution:
int steps_per_revolution; // number of steps for full motor revolution

const int PIN_SW = 2; // input pin from internal switch to stop motor when reach its bounds 

const int PIN_EN = 3; // output pin to motor driver to safe power

int manual_speed;

// callback function used to control stepper object
bool pause () {
  Button butt;
  butt = read_LCD_buttons();
  return (butt == SELECT || digitalRead(PIN_SW) == LOW);
}

Stepper myStepper = Stepper(steps_per_revolution, 10, 11, 12, 13, &pause);

void do_steps (long steps) { // steps can be <0 because of the direction
  // enable motor driver
  digitalWrite(PIN_EN, HIGH); 
  
  //needs some time the motor driver to become enabled
  delay(100); 
  long done_steps = (steps - myStepper.step(steps)); // steps returns left_steps
  
  motor_position += done_steps;
  digitalWrite(PIN_EN, LOW);
  delay(100);

//  Serial.print("motor_pos: ");
//  Serial.println(motor_position);

  EEPROM.put(POSITION_ADDRESS, motor_position);
}

#endif // SPECTRO_STEPPER_MOTOR_MOTOR_H