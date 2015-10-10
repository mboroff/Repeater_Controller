/**********************
 * Set Call Sign
**********************/

void SetCallsign()
{
  lcd.clear();                   // draw the screen option
  lcd.setCursor(0, 0);
  lcd.print("Set Call Sign");
  getCallsign();
  lcd.setCursor(0, 2);
  lcd.print("Call sign = ");
  lcd.print(radioCallsign);
  lcd.setCursor(0, 3);
  lcd.print("Press * to change");
   
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
                   sendStorecmd("CL", myCallsign);
                   lcd.setCursor(0, 3);
                   lcd.print("Call sign saved    ");
                   delay2k(); 
                   getCallsign();
                   lcd.clear();                   // draw the screen option
                   lcd.setCursor(0, 0);
                   lcd.print("Set Call Sign");
                   lcd.setCursor(0, 1);
                   lcd.print("Call sign now is");
                   lcd.setCursor(0, 2);
                   lcd.print(radioCallsign);         
                   menuSwitch = 1;
                   delay2k();
                   break;
                   }
        }
    }
}

/*************************************
 *      get the current squelch level
*************************************/

void getCallsign()
{
#ifdef DEBUG  
  Serial.println("Get call sign");
#endif

 sendReadcmd("CL?\r");
 get_UV3buff();
 for (int i = 0; i < 15; i++) {
      if (UV3buff[4 + i] == '\r' || UV3buff[4 + i] == '\0' ) {
          break;
          }
      radioCallsign[i]= UV3buff[4 + i];
      }
}

