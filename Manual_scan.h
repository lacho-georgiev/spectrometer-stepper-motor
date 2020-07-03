void manual_scan () {
  unsigned int motor_step = 10;
  int motor_dir = 1;
  while (true) {
    Button butt = read_LCD_buttons();
    if (butt == LEFT) {
      Serial.println("LEFT");
      motor_dir = -1;
      do_steps(motor_step*motor_dir);
      lcd.setCursor(0, 1);
      lcd.print("                ");
    } else if (butt == RIGHT) {
      Serial.println("RIGHT");
      motor_dir = 1;
      do_steps(motor_step*motor_dir);
      lcd.setCursor(0, 1);
      lcd.print("                ");
    } else if (butt == UP) {
      Serial.println("UP");
      if (motor_step == 0)
        motor_step == 10;
      else if (motor_step < 10000)
        motor_step *= 10;
      lcd.setCursor(0, 1);
      lcd.print("                ");
    } else if (butt == DOWN) {
      Serial.println("DOWN");
      if (motor_step != 1) 
        motor_step /= 10;
      lcd.setCursor(0, 1);
      lcd.print("                ");
    } else if (butt == SELECT) {
      write_int_EEPROM(POSITION_ADDRESS, motor_position);
      return;
    }
    lcd.setCursor(0, 1);
    lcd.print(motor_step);
    lcd.setCursor(7, 1);
    lcd.print(read_int_EEPROM(POSITION_ADDRESS));
  }
}
