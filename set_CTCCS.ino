/*********************************
 *      CTCCS Routines
*********************************/

/*****************
 * Set CTCCS
******************/

void setCTCCS()
{
#ifdef DEBUG
  Serial.println(functionLabels[menuSelect-1]);
#endif
  lcd.clear();                               // cear the diaplay
  lcd.setCursor(0, 0);
  lcd.print(functionLabels[menuSelect-1]);          // print the function title
  printCTCCS();                              // print the current CTCCS setting
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
                  sendCTCCS();
                  lcd.clear();
                  menuSwitch = 1;
                  break;
                  }
          else if (key == txtA) {              // increment CTCCS value
                   CTCCSctr++;
                   if (CTCCSctr > NUMBEROFTONES) { // table max
                       CTCCSctr = 1;
                      }
                   printCTCCS();   
                }
          else if (key == txtB) {              // decrement CTCCS value
                   CTCCSctr--;
                   if (CTCCSctr < 1) {
                       CTCCSctr = NUMBEROFTONES; // table min
                       }
                   printCTCCS();    
                }
      }
  }
  
}

/*******************************************
 * Print CTCCS entry pointed to by CTCCSctr
********************************************/

void printCTCCS()
{
   lcd.setCursor(0,2);                       // position the cursor
   lcd.print(F("CTCCS = "));
   lcd.print(CTCSStable[CTCCSctr - 1]);       // print the table entry
   lcd.setCursor(0, 3);
   lcd.print(txtAorB);
}
/*************************************
 *      get the current CTCCS 
 *      scroll through the taable of 
 *      values
*************************************/

void getCTCCS()
{
#ifdef DEBUG
 Serial.println(F("get CTCCS"));
#endif  

  sendReadcmd("TF?\r");
  get_UV3buff();
  memcpy(radioCTCCS, UV3buff, 5);
  radioCTCCSf = atof(radioCTCCS)/ 100;                     // convert read CTCCS
  for (int i = 0; i < 50; i++) {                          // look for match to set value of CTCCSctr
      float tempCTCCS = atof(CTCSStable[i]) * 10;
      tempCTCCS = tempCTCCS/10;
      if (tempCTCCS == radioCTCCSf) {                     // matched break out
          CTCCSctr = i + 1;
          break;
          }
      }
}

/***********************************
 *   Save the CTCCS
***********************************/
void sendCTCCS()
{
#ifdef DEBUG
  Serial.println(F("send CTCCS"));
#endif  
   radioCTCCSf = atof(CTCSStable[CTCCSctr - 1]) * 100;
   radioCTCCSi = radioCTCCSf;
   sprintf(radioCTCCS, "%05i",radioCTCCSi);
   sendStorecmd("TF", radioCTCCS);

   lcd.setCursor(0, 3);
   lcd.print(F("CTCCS Freq Saved"));
   delay2k();
}


