/**************************************
 *      Set Tone SQ Mode  0, 1, 2 or 3
**************************************/

/*****************
 * Set Tone Mode
******************/

void setToneMode()
{
#ifdef DEBUGTM
  Serial.println(functionLabels[menuSelect-1]);
#endif
  lcd.clear();                               // cear the diaplay
  lcd.setCursor(0, 0);
  lcd.print(functionLabels[menuSelect-1]);       // print the function title
  getTonemode();
  printTonemode();
  lcd.setCursor(0, 3);
  lcd.print(txtZerDashTwo);
  menuSwitch = 0;                            // esure the loop runs

  while (menuSwitch == 0){

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
                  sendTonemode();
                  lcd.clear();
                  menuSwitch = 1;
                  break;
                  }
          else if (key == txtZero[0] || key == '1' || key == '2') {  // only valid choices
                   toneMode[0] = key;
                   toneMode[1] = txtNull;
                   lcd.setCursor(12, 2);
                   lcd.print(key);
                   }  else {         
                            lcd.setCursor(12, 2);
                            lcd.print(key);
                            lcd.setCursor(0, 3);
                            lcd.print(F("Invalid tone value"));
                            delay2k();
                            lcd.setCursor(0, 3);
                            lcd.print(txtSpace20);
                            lcd.setCursor(0, 3);
                            lcd.print(txtZerDashTwo);
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
   lcd.print(F("Tone Mode = "));
   lcd.print(toneMode);       // print the table entry
}
/*************************************
 *      get the current Tone Mode 
*************************************/

void getTonemode()
{
#ifdef DEBUGTM
 Serial.println(F("Getting tone mode"));
#endif  
  sendReadcmd("TM?\r");
  get_UV3buff();
  toneMode[0] =  UV3buff[4];
#ifdef DEBUGTM
Serial.print(F("tone mode = ")); Serial.println(toneMode);
#endif
}

/***********************************
 *   Save the CTCCS
***********************************/
void sendTonemode()
{
#ifdef DEBUGTM
   Serial.println(F("==================================="));
   Serial.println(F("Send tone mode"));
   Serial.print(F("toneMode = ")); Serial.println(toneMode[0]);
#endif  

   sendStorecmd("TM", toneMode);
   lcd.setCursor(0, 3);
   lcd.print(F("Tone Mode Saved    "));
#ifdef DEBUGTM
Serial.println(F("Tone mode saved"));
Serial.println("===================================");
#endif   
   getTonemode();
   delay2k();
}


