/*********************************
 * displayTemphistory
*********************************/

void displayTemphistory()
{

#ifdef DEBUG
  Serial.println(functionLabels[menuSelect-1]);
#endif
  lcd.clear();                               // clear the diaplay
  lcd.setCursor(0, 0);
  lcd.print(functionLabels[menuSelect-1]);    // print the function title
  lcd.setCursor(0, 3);
  lcd.print(txtAorB);              // press a or b
  displayHour = 0;
  displayHistory();
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
          else if (key == txtStar ) {              // page forward
              lcd.clear();
              menuSwitch = 1;
              break;
          }
          else if (key == txtA ) {              // page forward
                if (displayHour > 22) {
                    displayHour = 0;
                }
                displayHistory();
                }
          else if (key == txtB) {              // page back
                displayHour = displayHour - 8;
                if (displayHour < 0) {
                    displayHour = 20;
                }
                displayHistory(); 
                }
      }
  }
  
}

/*****************************
 * displayHistory two to a line
*****************************/
void displayHistory()
{
  int tempTemperature;
  lcd.setCursor(0, 1);
  lcd.print(txtSpace20);
  lcd.setCursor(0, 1);
  for (int i = 0 ; i <2; i++) {
       if (currentDevice == 0) {
 #ifdef DEBUG       
          Serial.print(F("temperaturesaveAddr + displayHour = ")); Serial.println(temperaturesaveAddr + displayHour);
 #endif         
          tempTemperature = EEPROM.read(temperaturesaveAddr + displayHour);      // get the saved temperature from EEPROM
           } else {
                   tempTemperature = EEPROM.read(temperaturesaveAddr + 24 + displayHour);
                   }
       if (displayHour < 10) {
           lcd.print(txtZero); 
           }
        lcd.print(displayHour);
        lcd.print(txtSpaceEqualSpace);        // " = "
        if (tempTemperature < 10) {
          lcd.print(txtZero);   
          }
        lcd.print(tempTemperature);
        lcd.print(txtCspace);            // "C "
        displayHour++;
       } 
  lcd.setCursor(0, 2);
  lcd.print(txtSpace20);
  lcd.setCursor(0, 2);
  for (int i = 0 ; i <2; i++) {
       if (currentDevice == 0) {
#ifdef DEBUG 
           Serial.print(F("temperaturesaveAddr + displayHour = ")); Serial.println(temperaturesaveAddr + displayHour);       
#endif           
           tempTemperature = EEPROM.read(temperaturesaveAddr + displayHour);
           } else {
                   tempTemperature = EEPROM.read(temperaturesaveAddr + 24 + displayHour);
                   }
       if (displayHour < 10) {
           lcd.print(txtZero); 
           }
        lcd.print(displayHour);
        lcd.print(txtSpaceEqualSpace);         // " = "
        if (tempTemperature < 10) {
          lcd.print(txtZero);   
          }
        lcd.print(tempTemperature);
        lcd.print(txtCspace);           // "C "
        displayHour++;  
       } 

}

