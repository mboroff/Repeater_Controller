/*********************************
 *      Volume Routines
 *      scroll through the values
 *      0 - 39
*********************************/

/*****************
 * Set Volume
******************/

void settheVolume()
{
#ifdef DEBUG
  Serial.println(functionLabels[menuSelect-1]);
#endif
  lcd.clear();                               // cear the diaplay
  lcd.setCursor(0, 0);
  lcd.print(functionLabels[menuSelect-1]);    // print the function title
  getVolume();
  printVolume();                              // print the current CTCCS setting
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
                  sendVolume();
                  lcd.clear();
                  menuSwitch = 1;
                  break;
                  }
          else if (key == txtA) {              // increment volume value
                   volumeCtr = atoi(UV3volume);
#ifdef DEBUG
Serial.print("volume ctr = "); Serial.println(volumeCtr);
#endif
                   volumeCtr++;
                   if (volumeCtr > 39) {    // max value
                       volumeCtr = 1;
                       }
                   volumeStr = String(volumeCtr);
                   volumeStr.toCharArray(UV3volume, 3);
#ifdef DEBUG
Serial.print(F("volume str = ")); Serial.println(volumeStr);
Serial.print(F("UV3volume = ")); Serial.println(UV3volume);
#endif
                   printVolume();   
                }
          else if (key == txtB) {              // decrement volume value
                   volumeCtr = atoi(UV3volume);
                   volumeCtr--;
                   if (volumeCtr < 1) {        // min value
                       volumeCtr = 39;
                       }
                   volumeStr = String(volumeCtr);
                   volumeStr.toCharArray(UV3volume, 3);
                   printVolume();    
                }
      }
  }
  
}

/*******************************************
 * Print Volume
********************************************/

void printVolume()
{
   lcd.setCursor(0,2);                       // position the cursor
   lcd.print(F("Volume = "));
#ifdef DEBUG
Serial.print(F("volumeCtr = ")); Serial.println(volumeCtr);
#endif

   lcd.print(volumeCtr);       // print the volume variable
   lcd.print(txtSpaceOne);
   lcd.setCursor(0, 3);
   lcd.print(txtAorB);
}
/*************************************
 *      get the current Volume 
*************************************/

void getVolume()
{
#ifdef DEBUG
 Serial.println(F("get volume"));
#endif  
  sendReadcmd("VU?\r");
  get_UV3buff();
  // get the value
  for (int i= 0; i <2; i++) {
       UV3volume[i] = UV3buff[i + 4];
      }
  volumeCtr = atoi(UV3volume);
#ifdef DEBUG  
  Serial.print(F("volume = ")); Serial.println(UV3volume);
#endif  
}

/***********************************
 *   Save the Volume
***********************************/
void sendVolume()
{
#ifdef DEBUG
  Serial.println(F("send Volume"));
#endif  
   if (volumeCtr > 9) {
   sendStorecmd("VU", UV3volume);
   } else {
     char tempVol[3];
     tempVol[0] = txtZero[0];
     tempVol[1] = UV3volume[0];
     tempVol[2] = txtNull;
     sendStorecmd("VU", tempVol);
   }
   lcd.setCursor(0, 3);
   lcd.print(F("Volume Saved"));
   delay2k();

}


