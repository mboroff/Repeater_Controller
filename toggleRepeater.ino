/**************************** 
 *  Repeater Function
****************************/

void toggleRepeater()
{
#ifdef DEBUG
  Serial.println(functionLabels[menuSelect-1]);
#endif  
  lcd.clear();                   // draw the screen option
  lcd.setCursor(0, 0);
  lcd.print(functionLabels[menuSelect-1]);     // print the function title
  lcd.setCursor(0, 3);
  lcd.print(txtPressAtoToggle);
  lcd.setCursor(0, 2);
  lcd.print(F("Repeater = "));
  if (repeaterEnabled == relayOn) {
      lcd.print(txtOn);
      } else {
        lcd.print(txtOff);
      }
  
  menuSwitch = 0;
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
                  lcd.setCursor(0, 3);
#ifdef DEBUG                  
Serial.print(F("Saved repaeterEnabled = ")); Serial.println(repeaterEnabled);
#endif
                  EEPROM.write(repeaterAddr, repeaterEnabled);
                  lcd.print(F("Repeater state saved"));
                  menuSwitch = 1;
                  delay2k();
                  break;
                  }
          else if (key == txtA) {              // toggle the setting
                   lcd.setCursor(11, 2);
                   if (repeaterEnabled == relayOn){
                       repeaterEnabled = relayOff;
                       digitalWrite(REPEATERPIN, HIGH);        // turns the relay off            
                       lcd.print(txtOff);
                       }
                       else {
                            repeaterEnabled = relayOn;
                            digitalWrite(REPEATERPIN, LOW);      //turns the relay on              
                            lcd.print(txtOn);
                            }
#ifdef DEBUG                            
Serial.print(F("Toggled repeaterEnabled = ")); Serial.println(repeaterEnabled);                       
#endif
              }     //end off A
        }      // end of key
       }      // end of while
}
