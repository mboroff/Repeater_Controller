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
#ifdef DEBUG  
Serial.print("Start fanEnabled = "); Serial.println(fanEnabled);
#endif
  if (fanEnabled == relayOn) {
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
                  lcd.setCursor(0, 3);
#ifdef DEBUG                  
Serial.print("Saved fanEnabled = "); Serial.println(fanEnabled);
#endif
                  EEPROM.write(fanAddr, fanEnabled);
                  lcd.print("FAN state saved  ");
                  menuSwitch = 1;
                  delay2k();
                  break;
                  }
          else if (key == 'A' ) {              // increment squelch value
                   lcd.setCursor(6, 2);
                   if (fanEnabled == relayOn){
                       fanEnabled = relayOff;
                       digitalWrite(FANPIN, HIGH);                    //turn the relay off
                       lcd.print("OFF");
                       }
                       else {
                            fanEnabled = relayOn;
                            digitalWrite(FANPIN, LOW);            // turn the relay on        
                            lcd.print("ON ");
                            }
              }     //end off A
        }      // end of key
       }      // end of while
}
