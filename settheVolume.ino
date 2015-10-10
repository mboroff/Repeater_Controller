/*********************************
 *      Volume Routines
*********************************/

/*****************
 * Set Volume
******************/

void settheVolume()
{
#ifdef DEBUG
  Serial.println("Enter Volume menu");
#endif
  lcd.clear();                               // cear the diaplay
  lcd.setCursor(0, 0);
  lcd.print("Set Volume");

  printVolume();                              // print the current CTCCS setting
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
                  sendVolume();
                  lcd.clear();
                  menuSwitch = 1;
                  break;
                  }
          else if (key == 'A' ) {              // increment CTCCS value
                   volumeCtr = atoi(UV3volume);
#ifdef DEBUG
Serial.print("volume ctr = "); Serial.println(volumeCtr);
#endif
                   volumeCtr++;
                   if (volumeCtr > 39) {
                       volumeCtr = 1;
                       }
                   volumeStr = String(volumeCtr);
                   volumeStr.toCharArray(UV3volume, 3);
#ifdef DEBUG
Serial.print("volume str = "); Serial.println(volumeStr);
Serial.print("UV3volume = "); Serial.println(UV3volume);
#endif
                   printVolume();   
                }
          else if (key == 'B' ) {              // decrement CTCCS value
                   volumeCtr = atoi(UV3volume);
                   volumeCtr--;
                   if (volumeCtr < 1) {
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
   lcd.print("Volume = ");
#ifdef DEBUG
Serial.print("UV3volume = "); Serial.println(UV3volume);
#endif

   lcd.print(UV3volume);       // print the volume variable
   lcd.print(" ");
   lcd.setCursor(0, 3);
   lcd.print("Press A or B");
}
/*************************************
 *      get the current Volume 
*************************************/

void getVolume()
{
#ifdef DEBUG
 Serial.println("get volume");
#endif  
  sendReadcmd("VU?\r");
  get_UV3buff();
  // get the value
  for (int i= 0; i <2; i++) {
       UV3volume[i] = UV3buff[i + 4];
      }
#ifdef DEBUG  
  Serial.print("volume = "); Serial.println(UV3volume);
#endif  
}

/***********************************
 *   Save the Volume
***********************************/
void sendVolume()
{
#ifdef DEBUG
  Serial.println("send Volume");
#endif  

   sendStorecmd("VU", UV3volume);

   lcd.setCursor(0, 3);
   lcd.print("Volume Saved");
   delay(2000);

}

