/**************************** 
 *  Repeater Function
****************************/

void toggleRepeater()
{
#ifdef DEBUG
  Serial.println("Enter toggle repeater");
#endif  
  lcd.clear();                   // draw the screen option
  lcd.setCursor(0, 0);
  lcd.print("Repeater ON/OFF");
  lcd.setCursor(0, 3);
  lcd.print("Press A to toggle");
  lcd.setCursor(0, 2);
  lcd.print("Repeater = ");
  if (repeaterEnabled == true) {
      lcd.print("ON ");
      } else {
        lcd.print("OFF");
      }
  
  menuSwitch = 0;
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
                  EEPROM.write(repeaterAddr, repeaterEnabled);
                  lcd.setCursor(0, 3);
                  if (repeaterEnabled == true) {
                      lcd.print("Repeater ON saved  ");
                      } else {
                              lcd.print("Repeater OFF saved ");
                              }
                  menuSwitch = 1;
                  delay2k();
                  break;
                  }
          else if (key == 'A' ) {              // increment squelch value
                   if (repeaterEnabled == true){
                       repeaterEnabled = false;                    
                       }
                       else {
                            repeaterEnabled = true;
                            }
                   lcd.setCursor(11, 2);
                   if (repeaterEnabled == true) {
                       digitalWrite(REPEATERPIN, LOW);
                       lcd.print("ON ");
                   } else {
                           digitalWrite(REPEATERPIN, HIGH);
                           lcd.print("OFF");
                           }
              }     //end off A
        }      // end of key
       }      // end of while
}
