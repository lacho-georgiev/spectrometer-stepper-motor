int input (int cur) {
  int indx = 5;
  int scale = 10;
  char buffer[16];
  while (true) {
    Button butt = read_LCD_buttons();
    sprintf(buffer,"> %5d",cur);
    lcd.setCursor(0,1);
    lcd.print(buffer);
    if (butt == LEFT) {
      if (indx > 2) {
        indx--;
        scale *= 10;
        lcd.noCursor();
      }
    } else if (butt == RIGHT){
      if (indx < 6) {
        indx++;
        scale /= 10;
        lcd.noCursor();
      }
    } else if (butt == UP) {
      if (scale + cur > 0)
        cur += scale;
    } else if (butt == DOWN){
      if (cur - scale > 0)
        cur -= scale;
    } else if (butt == SELECT) {
      lcd.noCursor();
      return cur;
    }
    lcd.setCursor(indx, 1);
    lcd.cursor();
  }
}
