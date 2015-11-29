/**************************** 
 *  Beep Function
****************************/

void toggleBeep()
{
#ifdef DEBUG
  Serial.println)functionLabels[menuSelect-1]);
#endif    
  lcd.clear();                   // draw the screen option
  lcd.setCursor(0, 0);
  lcd.print(functionLabels[menuSelect-1]);   // print the function title
  lcd.setCursor(0, 3);
  lcd.print(txtPressAtoToggle);
  lcd.setCursor(0, 2);
  lcd.print(F("Beep = "));
  if (buzzerEnabled == true) {
      lcd.print(txtOn);
      } else {
        lcd.print(txtOff);
      }
  
  menuSwitch = 0;                    // make sure loop continues until save or cancel
    while(menuSwitch == 0) {
      lcd.setCursor(7, 2);
      key = keypad.getKey();               // see if a key has been pressed
      if (key) {
          if (buzzerEnabled == true){        // check if buzzer should buzz
              beep();                    
              }
          if (key == txtHashTag) {               // cancel key
              lcd.clear();
              menuSwitch = 1;
              break;
              }
          else if (key == txtStar) {            // confirmation key
                  EEPROM.write(buzzerAddr, buzzerEnabled);     // save the status in EEPROM
                  lcd.setCursor(0, 3);
                  if (buzzerEnabled == true) {
                      lcd.print(F("Beep ON saved      "));
                      } else {
                              lcd.print(F("Beep OFF saved    "));
                              }
                  menuSwitch = 1;
                  delay2k();
                  break;
                  }
          else if (key == txtA) {              // toggle key
                   if (buzzerEnabled == true){
                       buzzerEnabled = false;                    
                       }
                       else {
                            buzzerEnabled = true;
                            beep();                    
                            }

                   lcd.setCursor(7, 2);
                   if (buzzerEnabled == true) {
                       lcd.print(txtOn);
                   } else {
                           lcd.print(txtOff);
                           }
              }     //end off A
        }      // end of key
       }      // end of while
}
