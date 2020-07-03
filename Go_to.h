void go_on_position () {
  unsigned int motor_position = read_int_EEPROM(POSITION_ADDRESS);
  unsigned int go_on_position = input(motor_position);  
  do_steps(go_on_position - motor_position);
}
