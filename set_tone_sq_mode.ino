/*********************************
 *      Set Tone SQ Mode  0, 1 or 2
*********************************/

/*****************
 * Set Tone Mode
******************/

void setToneMode()
{
#ifdef DEBUGTM
  Serial.println("Enter set tone mode");
#endif
  lcd.clear();                               // cear the diaplay
  lcd.setCursor(0, 0);
  lcd.print("Tone Sqlch Mode");
  getTonemode();
  printTonemode();
  menuSwitch = 0;                            // esure the loop runs

  while (menuSwitch == 0){

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
                  sendTonemode();
                  lcd.clear();
                  menuSwitch = 1;
                  break;
                  }
          else {               
                if (key == '0' || key == '1' || key == '2' ) {
                   toneMode[0] = key;
                   toneMode[1] = '\0';
                   lcd.setCursor(12, 2);
                   lcd.print(key);
                } else {
                    lcd.setCursor(0, 3);
                    lcd.print("Invalid tone value");
                    delay(2000);
                    lcd.setCursor(0, 3);
                    lcd.print("                  ");
                    }
              }
          }
    }
}

/*******************************************
 * Print Tone Mode
********************************************/

void printTonemode()
{
   lcd.setCursor(0,2);                       // position the cursor
   lcd.print("Tone Mode = ");
   lcd.print(toneMode);       // print the table entry
}
/*************************************
 *      get the current Tone Mode 
*************************************/

void getTonemode()
{
#ifdef DEBUGTM
 Serial.println("Getting tone mode");
#endif  
  sendReadcmd("TF?\r");
  get_UV3buff();
  toneMode[0] =  UV3buff[4];
#ifdef DEBUGTM
Serial.print("tone mode = "); Serial.println(toneMode);
#endif
}

/***********************************
 *   Save the CTCCS
***********************************/
void sendTonemode()
{
#ifdef DEBUGTM
   Serial.println("===================================");
   Serial.println("Send tone mode");
   Serial.print("toneMode = "); Serial.println(toneMode[0]);
#endif  

   sendStorecmd("TM", toneMode);
   lcd.setCursor(0, 3);
   lcd.print("Tone Mode Saved    ");
#ifdef DEBUGTM
Serial.println("Tone mode saved");
Serial.println("===================================");
#endif   
   getTonemode();
   delay(2000);
}


