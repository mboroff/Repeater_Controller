/**************************** 
 *  Fan Function
****************************/

void toggleFan()
{
#ifdef DEBUG
  Serial.println("Enter toggle fan");
#endif  
  lcd.clear();                   // draw the screen option
  lcd.setCursor(0, 0);
  lcd.print("Fan ON/OFF ");
  lcd.setCursor(0, 3);
  lcd.print("Press A to toggle");
  lcd.setCursor(0, 2);
  lcd.print("Fan = ");
  if (fanEnabled == true) {
      lcd.print("ON  ");
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
                  EEPROM.write(fanAddr, fanEnabled);
                  lcd.setCursor(0, 3);
                  if (fanEnabled == true) {
                      lcd.print("Fan ON saved      ");
                      } else {
                              lcd.print("Fan OFF saved    ");
                              }
                  menuSwitch = 1;
                  delay(2000);
                  break;
                  }
          else if (key == 'A' ) {              // increment squelch value
                   if (fanEnabled == true){
                       fanEnabled = false;                    
                       }
                       else {
                            fanEnabled = true;
                            }
                   lcd.setCursor(6, 2);
                   if (fanEnabled == true) {
                       digitalWrite(FANPIN, LOW);
                       lcd.print("ON ");
                   } else {
                           digitalWrite(FANPIN, HIGH);
                           lcd.print("OFF");
                           }
              }     //end off A
        }      // end of key
       }      // end of while
}
