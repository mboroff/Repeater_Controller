/***********************
 * setTimeouttimer
***********************/

void setTimeouttimer()
{
#ifdef DEBUG
  Serial.println(functionLabels[menuSelect-1]);
#endif
  lcd.clear();                               // cear the diaplay
  lcd.setCursor(0, 0);
  lcd.print(functionLabels[menuSelect-1]);          // print the function title
  getTimeouttimer;
  printTimeouttimer();                              // print the current CTCCS setting
  lcd.setCursor(0, 3);
  lcd.print(txtAorBorC);
  menuSwitch = 0;                            // esure the loop runs
  prevtimeOutctr = timeOutctr;

  while (menuSwitch == 0){

      key = keypad.getKey();               // see if a key has been pressed
      if (key) {
          if (buzzerEnabled == true){        // check if buzzer should buzz
              beep();                    
              }
          if (key == txtHashTag) {               // cancel key
              timeOutctr = prevtimeOutctr;
              lcd.clear();
              menuSwitch = 1;
              break;
              }
          else if (key == txtStar) {            // confirmation key
                  sendTimeouttimer();
                  lcd.clear();
                  menuSwitch = 1;
                  break;
                  }
          else if (key == txtA) {              // increment timeOutctr value
                   timeOutctr++;
                   if (timeOutctr > 600) {
                       timeOutctr = 0;
                   }
                   printTimeouttimer();   
                }
          else if (key == txtB) {              // decrement timeOutctr value
                   timeOutctr--;
                   if (timeOutctr < 0) {
                       timeOutctr = 600;
                   }
                   printTimeouttimer();    
                }
          else if (key == txtC) {              // increment by 50 timeOutctr value
                   timeOutctr = timeOutctr + 50;
                   if (timeOutctr > 600) {
                       timeOutctr = 0;
                   }
                   printTimeouttimer();    
                }
      }
  }
  
}

/*******************************************
 * Print timeout timer
********************************************/

void printTimeouttimer()
{
   lcd.setCursor(0,2);                       // position the cursor
   lcd.print(F("Time out = "));
   if (timeOutctr < 10) {
       lcd.print(txtZeroZero);
   } else if (timeOutctr > 9 && timeOutctr < 100) {
       lcd.print(txtZero);
   }
   lcd.print(timeOutctr);       // print the table entry
   lcd.print(F(" msec"));
   lcd.setCursor(0, 3);
}
/*************************************
 *      get the current tinme out timer 
*************************************/

void getTimeouttimer()
{
#ifdef DEBUG
 Serial.println(F("get timeout timer"));
#endif  

  sendReadcmd("TO?\r");
  get_UV3buff();
for (int i = 0; i < 3; i++) {             // move hang time from common buffer
        timeOuttime[i] = UV3buff[i + 1];
        timeOuttime[i + 1] = txtNull;
  }
  timeOutctr = atoi(timeOuttime);
}

/***********************************
 *   Save the timeout timer
***********************************/
void sendTimeouttimer()
{
#ifdef DEBUG
  Serial.println(F("send timeout time"));
#endif  
   sprintf(timeOuttime, "%03i",timeOutctr);
   sendStorecmd("TO", timeOuttime);

   lcd.setCursor(0, 3);
   lcd.print(F("Timeout Saved       "));
   delay2k();
}

