/**************************
 * toggleDTFM
**************************/

void toggleDTFM()
{

#ifdef DEBUG
  Serial.println(functionLabels[menuSelect-1]);
#endif
  lcd.clear();                               // clear the diaplay
  lcd.setCursor(0, 0);
  lcd.print(functionLabels[menuSelect-1]);           // print the function title
  getdtfmState();
  printDTFMstate();  
  lcd.setCursor(0, 3);
  lcd.print(txtPressAtoToggle);

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
                  senddtfmState();               // send the dtfm state
                  lcd.clear();
                  menuSwitch = 1;                // kill the loop
                  break;
                  }
          else if (key == txtA ) {              // toggle dtfm state
                    if (dtfmState[1] == 'F') {
                       dtfmSwitch[0] = txtOne[0];
                       dtfmSwitch[1] = txtNull;
                       for (int i = 0; i < 3; i++) {
                 
                            dtfmState[i] = txtOn[i];
                       }
                   } else {
                       dtfmSwitch[0] = txtZero[0];
                       dtfmSwitch[1] = txtNull;
                       for (int i = 0; i < 3; i++) {
                       dtfmState[i] = txtOff[i];
                       }
                   }
                   dtfmSwitch[1] = txtNull;
                   printDTFMstate();
          }
      }
  }
}

/****************************
 * printDTFMstate
****************************/
void printDTFMstate()
{
  lcd.setCursor(0, 2);
  lcd.print(F("DTFM = "));
  lcd.print(dtfmState);
 
}
/*********************
 *    get dtfm status
*********************/

void getdtfmState()
{
  sendReadcmd("DR?\r");
  get_UV3buff();
  for (int i = 0; i < 3; i++) {             // move hang time from common buffer
        dtfmState[i] = UV3buff[i + 4];
        dtfmState[i + 1] = txtNull;
  }
}


/**********************
 * send dtfm switch
*************************/
/***********************************
 *   setdtfmState
***********************************/
void senddtfmState()
{
#ifdef DEBUG
  Serial.println(F("senddtfmState"));
#endif  
   sendStorecmd("DR", dtfmSwitch);

   lcd.setCursor(0, 3);
   lcd.print(F("DTFM state saved "));
   delay2k();
}

