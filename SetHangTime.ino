/******************************
 * SetHangTime
*****************************/

void SetHangTime()

{

#ifdef DEBUG
  Serial.println(functionLabels[menuSelect-1]);
#endif
  lcd.clear();                               // clear the diaplay
  lcd.setCursor(0, 0);
  lcd.print(functionLabels[menuSelect-1]);           // print the function title
  getHangtimer();                          // get the hang time
  printHangtimer();                        // print the current hang time
  lcd.setCursor(0, 3);
  lcd.print(txtAorB);

  menuSwitch = 0;                            // esure the loop runs

  while (menuSwitch == 0){             // loop until the * or # are pressed

      key = keypad.getKey();               // see if a key has been pressed
      if (key) {
          if (buzzerEnabled == true){        // check if buzzer should buzz
              beep();                    
              }
          if (key == txtHashTag) {               // cancel key
              lcd.clear();
              menuSwitch = 1;                      // kill the loop
              break;
              }
          else if (key == txtStar) {            // confirmation key
                  sendHangtimer();               // send the new hang time
                  lcd.clear();
                  menuSwitch = 1;                // kill the loop
                  break;
                  }
          else if (key == txtA ) {              // increment hang timer value
                   hangTimer = hangTimer + 1000;
                   if (hangTimer > 5000) {
                       hangTimer = 0;
                      }
                   printHangtimer();              // print the hang timer value   
                }
          else if (key == txtB) {              // decrement hang timer value
                   hangTimer = hangTimer - 1000;
                   if (hangTimer < 0) {
                       hangTimer = 5000;
                       }
                   printHangtimer();              // print the hang timer value       
                }
      }
  }
  
}

/*******************************************
 * Print Hang timer
********************************************/

void printHangtimer()
{
#ifdef DEBUG
Serial.print(F("hangTimer = ")); Serial.println(hangTimer);  
#endif
   lcd.setCursor(0,2);                       // position the cursor
   lcd.print(F("Hang Timer = "));
   if (hangTimer < 1000) {           // handle hang time less than 1000
    lcd.print(txtZero);
   }
   if (hangTimer < 100) {
      lcd.print(txtZero);
   }
   if (hangTimer < 10) {
       lcd.print(txtZero);
   }
   lcd.print(hangTimer);
   lcd.print(F(" MS"));
}
/*************************************
 *      get the current Hang timer 
*************************************/

void getHangtimer()
{
#ifdef DEBUG
 Serial.println(F("get Hang timer"));
#endif  
  sendReadcmd("HT?\r");
  get_UV3buff();
  for (int i = 0; i < 4; i++) {             // move hang time from common buffer
        tempHangtimer[i] = UV3buff[i + 1];
        tempHangtimer[i + 1] = txtNull;
  }
  hangTimer = atoi(tempHangtimer);
 }

/***********************************
 *   Save the Hang timer
***********************************/
void sendHangtimer()
{
#ifdef DEBUG
  Serial.println(F("send Hang Timer"));
#endif  
   sprintf(tempHangtimer, "%04.4i", hangTimer);      // format hang timer before sending to uv3
   tempHangtimer[5] = txtNull;
   sendStorecmd("HT", tempHangtimer);
   lcd.setCursor(0, 3);
   lcd.print(F("Hang Timer Saved   "));
   delay2k();
}


