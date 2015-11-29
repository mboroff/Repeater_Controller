/*****************************
 *    SetIDtime
*****************************/

void SetIDtime()
{
  #ifdef DEBUG
  Serial.println(functionLabels[menuSelect-1]);
#endif
  lcd.clear();                               // clear the diaplay
  lcd.setCursor(0, 0);
  lcd.print(functionLabels[menuSelect-1]);            // print the function title
  getIDtimer();
  printIDtimer();
  lcd.setCursor(0, 3);
  lcd.print(txtAorBorC);       // "Press A or B or C"

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
                  sendIDtimer();
                  lcd.clear();
                  menuSwitch = 1;
                  break;
                  }
          else if (key == txtA ) {              // increment ID time value
                   idTimer++;
                   if (idTimer > 500) {
                       idTimer = 0;
                      }
                   printIDtimer();   
                }
          else if (key == txtB) {              // decrement ID time value
                   idTimer--;
                   if (idTimer < 0) {
                       idTimer = 500;
                       }
                   printIDtimer();    
                }
          else if (key == txtC ) {              // decrement CTCCS value
                   idTimer = idTimer + 50;
                   if (idTimer < 0) {
                       idTimer = 500;
                       }
                   if (idTimer > 500) {
                       idTimer = 0;
                       }
                       
                   printIDtimer();    
                }

      }
  }
  
}

/*******************************************
 * Print ID timer
********************************************/

void printIDtimer()
{
#ifdef DEBUG
Serial.print(F("idTimer = ")); Serial.println(idTimer);  
#endif
   lcd.setCursor(0,2);                       // position the cursor
   lcd.print(F("ID Timer = "));
   if (idTimer < 10) {
       lcd.print("0");
   }
   lcd.print(idTimer);
   lcd.print(F(" Secs "));
}
/*************************************
 *      get the current ID timer 
*************************************/

void getIDtimer()
{
#ifdef DEBUG
 Serial.println(F("get ID timer"));
#endif  
  sendReadcmd("IT?\r");
  get_UV3buff();
  for (int i = 0; i < 3; i++) {
        tempIDtimer[i] = UV3buff[i + 6];      // move the id timer from common buffer
        tempIDtimer[i + 1] = txtNull;
  }
  idTimer = atoi(tempIDtimer);
 }

/***********************************
 *   Save the ID timer
***********************************/
void sendIDtimer()
{
#ifdef DEBUG
  Serial.println("send ID Timer");
#endif  
   sprintf(tempIDtimer, "%03.3i", idTimer);     // format the id time before sending to uv3
   tempIDtimer[4] = txtNull;
   sendStorecmd("IT", tempIDtimer);

   lcd.setCursor(0, 3);
   lcd.print(F("ID Timer Saved     "));
   delay2k();
}


