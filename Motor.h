// Define number of steps per revolution:
int STEPS_PER_REVOLUTION = read_int_EEPROM(STEPS_PER_REV_ADDRESS); // number of steps for full motor revolution

const int PIN_SW = 2; // input pin from internal switch to stop motor when reach its bounds 

const int PIN_EN = 3; // output pin to motor driver to safe power

int manual_speed = 240;

int auto_speed = 240;

int sign(int value) {
 return int((value>0)-(value<0));
}

// callback function used to control stepper object
bool pause () {
  Button butt;
  butt = read_LCD_buttons();
  return (butt == SELECT || digitalRead(PIN_SW) == LOW);
}

Stepper myStepper = Stepper(STEPS_PER_REVOLUTION, 10, 11, 12, 13, &pause);

void do_steps (int steps) { // steps can be <0 because of the direction
  // enable motor driver
  digitalWrite(PIN_EN, HIGH); 
  
  //needs some time the motor driver to become enabled
  delay(100); 
  int done_steps = (steps - myStepper.step(steps)); // steps returns left_steps
  
  Serial.print("done_steps: ");
  Serial.println(done_steps);
  
  motor_position += sign(steps)*done_steps;
  digitalWrite(PIN_EN, LOW);
  delay(100);
  Serial.print("motor_pos: ");
  Serial.println(motor_position);
  Serial.print("steps per revol: ");
  Serial.println(read_int_EEPROM(STEPS_PER_REV_ADDRESS));
  
  write_int_EEPROM(POSITION_ADDRESS, motor_position);
}