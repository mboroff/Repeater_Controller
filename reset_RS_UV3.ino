/************************************
 * reset_RS_UV3
************************************/

void reset_RS_UV3()
{
#ifdef DEBUG
Serial.println("Enter Reset RS_UV3");
#endif
  lcd.clear();                   // draw the screen option
  lcd.setCursor(0, 0);
  lcd.print("Reset RS-UV3");
  lcd.setCursor(0, 0);
  lcd.print("WARNING Reset Board");
  lcd.setCursor(0, 2);
  lcd.print("Press * to confirm");
  lcd.setCursor(0, 3);
  lcd.print("Press # to cancel");

  beep();
  delay(500);
  beep();
  delay(500);
  beep();
  
  menuSwitch = 0;
    while(menuSwitch == 0) {
      lcd.setCursor(10, 2);
      key = keypad.getKey();               // see if a key has been pressed
      if (key) {
          if (buzzerEnabled == true){
              beep();                    
              }
          if (key == '#') {               // cancel key
              lcd.clear();
              menuSwitch = 1;
              break;
              }
          else if (key == '*') {            // confirmation key
                  sendReset();              
                  menuSwitch = 1;
                  break;
                  }
      }
    }
}


/********************************
 * Send reset
********************************/

void sendReset()
{
    sendReadcmd("FD1\r");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reset RS-UV3");
    lcd.setCursor(0, 1);
    lcd.print("Board has been Reset");
    delay(3000);
    get_repeater_info();
}

