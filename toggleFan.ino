/**************************** 
 *  Fan Function
****************************/

void toggleFan()
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
  lcd.print(F("Fan = "));
#ifdef DEBUG  
Serial.print(F("Start fanEnabled = ")); Serial.println(fanEnabled);
#endif
  if (fanEnabled == relayOn) {
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
Serial.print(F("Saved fanEnabled = ")); Serial.println(fanEnabled);
#endif
                  EEPROM.write(fanAddr, fanEnabled);
                  lcd.print(F("FAN state saved  "));
                  menuSwitch = 1;
                  delay2k();
                  break;
                  }
          else if (key == txtA) {              // toggle the setting
                   lcd.setCursor(6, 2);
                   if (fanEnabled == relayOn){
                       fanEnabled = relayOff;
                       digitalWrite(FANPIN, HIGH);                    //turn the relay off
                       lcd.print(txtOff);
                       }
                       else {
                            fanEnabled = relayOn;
                            digitalWrite(FANPIN, LOW);            // turn the relay on        
                            lcd.print(txtOn);
                            }
              }     //end off A
        }      // end of key
       }      // end of while
}
