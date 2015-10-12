/**************************** 
 *  Beep Function
****************************/

void toggleBeep()
{
  lcd.clear();                   // draw the screen option
  lcd.setCursor(0, 0);
  lcd.print("Beep ON/OFF");
  lcd.setCursor(0, 3);
  lcd.print("Press A to toggle");
  lcd.setCursor(0, 2);
  lcd.print("Beep = ");
  if (buzzerEnabled == true) {
      lcd.print("ON ");
      } else {
        lcd.print("OFF");
      }
  
  menuSwitch = 0;                    // make sure loop continues until save or cancel
    while(menuSwitch == 0) {
      lcd.setCursor(7, 2);
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
                  EEPROM.write(buzzerAddr, buzzerEnabled);
                  lcd.setCursor(0, 3);
                  if (buzzerEnabled == true) {
                      lcd.print("Beep ON saved      ");
                      } else {
                              lcd.print("Beep OFF saved    ");
                              }
                  menuSwitch = 1;
                  delay2k();
                  break;
                  }
          else if (key == 'A' ) {              // toggle key
                   if (buzzerEnabled == true){
                       buzzerEnabled = false;                    
                       }
                       else {
                            buzzerEnabled = true;
                            beep();                    
                            }

                   lcd.setCursor(7, 2);
                   if (buzzerEnabled == true) {
                       lcd.print("ON ");
                   } else {
                           lcd.print("OFF");
                           }
              }     //end off A
        }      // end of key
       }      // end of while
}
