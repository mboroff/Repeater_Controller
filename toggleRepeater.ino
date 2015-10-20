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
  if (repeaterEnabled == relayOn) {
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
Serial.print("Saved repaeterEnabled = "); Serial.println(repeaterEnabled);
#endif
                  EEPROM.write(repeaterAddr, repeaterEnabled);
                  lcd.print("Repeater state saved");
                  menuSwitch = 1;
                  delay2k();
                  break;
                  }
          else if (key == 'A' ) {              // increment squelch value
                   lcd.setCursor(11, 2);
                   if (repeaterEnabled == relayOn){
                       repeaterEnabled = relayOff;
                       digitalWrite(REPEATERPIN, HIGH);        // turns the relay off            
                       lcd.print("OFF");
                       }
                       else {
                            repeaterEnabled = relayOn;
                            digitalWrite(REPEATERPIN, LOW);      //turns the relay on              
                            lcd.print("ON ");
                            }
#ifdef DEBUG                            
Serial.print("Toggled repeaterEnabled = "); Serial.println(repeaterEnabled);                       
#endif
              }     //end off A
        }      // end of key
       }      // end of while
}
