enum Button {
  RIGHT,
  UP,
  DOWN,
  LEFT,
  SELECT,
  NONE
};

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 5;

Button lastButtonState = NONE;

Button read_LCD_buttons()
{

  if ((millis() - lastDebounceTime) < debounceDelay) {
    return NONE;
  }
  
  int reading = analogRead(0);
////  Serial.println(reading);
  Button buttonState = NONE;
  if (reading < 50) {
    buttonState = RIGHT;
  } else if (reading < 150) {// 250
    buttonState = UP;
  } else if (reading < 350) {// 450
    buttonState = DOWN;
  } else if (reading < 500) { //650
    buttonState = LEFT;
  } else if (reading < 650) {//850
    buttonState = SELECT;
  }
  if (buttonState != lastButtonState) {
    lastDebounceTime = millis();
    lastButtonState = buttonState;
    return buttonState;
  }

 return NONE;
}
