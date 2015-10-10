/**************************** 
 *  Squelch  Level Option
****************************/

void setSquelchlevel()
{
#ifdef DEBUG
Serial.println("Enter Squelch level menu");
#endif
  for(int i = 0; i < 2; i++){     // clear the input field
      inputFld[i] = '/0';
  }
  inputCtr = 0;
  lcd.clear();                   // draw the screen option
  lcd.setCursor(0, 0);
  lcd.print("Set Sqlch Level");
  getSquelchlevel();
  lcd.setCursor(0, 2);
  lcd.print("Squelch = ");
  lcd.print(squelchLevel);
  
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
                  sendSquelchlevel();              
                  delay(2000);
                  menuSwitch = 1;
                  delay(2000);
                  break;
                  }
          else if (key == 'A' ) {              // increment squelch value
                   squelchValue++;
                   if (squelchValue == 10) {
                       squelchValue = 0;
                      }
                }
          else if (key == 'B' ) {              // decrement squelch value
                   squelchValue--;
                   if (squelchValue < 0) {
                       squelchValue = 9;
                       }
                }
          else {
                squelchLevel[0] = key;
                squelchValue = atoi(squelchLevel);
          }
       lcd.print(squelchValue);
      }
    }
}

/*************************************
 *      get the current squelch level
*************************************/

void getSquelchlevel()
{
  squelchLevel[0] = '\0';
  flushBuffers();
#ifdef DEBUG  
Serial.println("Get sqlchlvl");  
#endif
  if (currentDevice == 0) {                        // check for device
      UV3A.write('\r');
      UV3A.print("SQ?\r");
      get_UV3buff();
      squelchLevel[0] = UV3buff[4];
  } else {
      UV3B.write('\r');
      UV3B.print("SQ?\r");
      get_UV3buff();
      squelchLevel[0] = UV3buff[4];
  }
  squelchValue = atoi(squelchLevel);
}

/***********************************
 *   Save the squelch level
***********************************/
void sendSquelchlevel()
{
#ifdef DEBUG  
  Serial.println("Send sql lvl");
#endif
   squelchStr = String(squelchValue);
   squelchStr.toCharArray(squelchLevel, 2);
#ifdef DEBUG
  Serial.print("Sqlch lvl = "); Serial.println(squelchLevel); 
#endif
      if (currentDevice == 0) {                   // check which device
          UV3A.write('\r');
          UV3A.print("SQ");
          UV3A.write(squelchLevel);
          UV3A.write('\r');
          delay(200);
#ifdef DEBUG
          Serial.print("Sending ST"); Serial.println(memoryChannel);
#endif
          UV3A.print("ST");
          UV3A.write(memoryChannel);
          UV3A.write('\r');
       } else {
                UV3B.write('\r');
                UV3B.print("SQ");
                UV3B.write(squelchLevel);
                UV3B.write('\r');
                UV3B.print("ST");
                UV3B.write(memoryChannel);
                UV3B.write('\r');
                }
   delay(200);             
   getSquelchlevel();
   lcd.setCursor(0, 3);   
   lcd.print("Squelch Level Saved");
   delay(2000);
}

