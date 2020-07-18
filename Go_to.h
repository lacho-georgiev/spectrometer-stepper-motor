void go_on_position () {
  long motor_position = EEPROM.read(POSITION_ADDRESS);
  long go_on_position = input_long(motor_position);  
  do_steps(go_on_position - motor_position);
}
