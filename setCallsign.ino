/**********************
 * Set Call Sign
**********************/

void SetCallsign()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set Call Sign");
  lcd.setCursor(0, 1);
  lcd.print("Use keypad like a   ");
  lcd.setCursor(0, 2);
  lcd.print("phone.    2 = ABC2  ");
  lcd.setCursor(0, 3);
  lcd.print("3 = DEF3  4 = GHI4  ");
  delay2k();
  
  lcd.setCursor(0, 1);
  lcd.print("phone.    2 = ABC2  ");
  lcd.setCursor(0, 2);
  lcd.print("3 = DEF3  4 = GHI4  ");
  lcd.setCursor(0, 3);
  lcd.print("5 = JKL5  6 = MNO6  ");
  delay500();
  lcd.setCursor(0, 1);
  lcd.print("3 = DEF3  4 = GHI4  ");
  lcd.setCursor(0, 2);
  lcd.print("5 = JKL5  6 = MNO6  ");
  lcd.setCursor(0, 3);
  lcd.print("7 = PQRS7 8 = TUV8  ");
  delay500();
  lcd.setCursor(0, 1);
  lcd.print("5 = JKL5  6 = MNO6  ");
  lcd.setCursor(0, 2);
  lcd.print("7 = PQRS7 8 = TUV8  ");
  lcd.setCursor(0, 3);  
  lcd.print("9 = WXYZ9 A = Next  ");
  delay500();
  lcd.setCursor(0, 1);
  lcd.print("7 = PQRS7 8 = TUV8  ");
  lcd.setCursor(0, 2);  
  lcd.print("9 = WXYZ9 A = Next  ");
  lcd.setCursor(0, 3);  
  lcd.print("B = Bksp  C = clear ");
  delay500();
  lcd.setCursor(0, 1);
  lcd.print("9 = WXYZ9 A = Next  ");
  lcd.setCursor(0, 2);
  lcd.print("B = Bksp  C = clear ");
  lcd.setCursor(0, 3);  
  lcd.print("                    ");
  delay500();
  lcd.setCursor(0, 1);
  lcd.print("B = Bksp  C = clear ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  delay500();
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  for (int i = 0; i < 21; i++){
       callSignbuffer[i] = '\0';
       }
  lcd.print(callSignbuffer);
  lcd.setCursor(0, 3);
  lcd.print("Enter call sign");
  bufferIndex = 0;
  keyIndex = 0;
  menuSwitch = 0;
    while(menuSwitch == 0) {
      key = keypad.getKey();               // see if a key has been pressed
      if (key) {
          if (prevKey != key) {
              prevKey = key;
              keyIndex = 0;
              }
          if (buzzerEnabled == true){
              beep();                    
              }
          if (key == '#') {               // cancel key
              lcd.clear();
              menuSwitch = 1;
              break;
              }
          else if (key == '*') {            // confirmation key
                  menuSwitch = 1;
                  sendStorecmd("CL", callSignbuffer);
                  lcd.setCursor(0, 3);  
                  lcd.print("Call sign saved     ");
                  delay2k();
                  getCallsign();
                  lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.setCursor(0, 1);
                  lcd.print("Call sign now is");
                  lcd.setCursor(0, 2);
                  lcd.print(radioCallsign);         
                  menuSwitch = 1;
                  delay2k();
             break;
                  }
          else if (key == 'A' ) {              
                   if (keyEntered == true) {
                       keyEntered = false;
                       bufferIndex++;
                       keyIndex = 0;
                       if (bufferIndex > 19) {
                           bufferIndex = 19;
                           }
                       } 
                    }
          else if (key == 'B') {
                   callSignbuffer[bufferIndex] = ' ' ;
                   bufferIndex--;
                   if (bufferIndex < 0){
                       bufferIndex = 0;
                       }
                   callSignbuffer[bufferIndex] = ' ' ;
                   lcd.setCursor(0, 2); 
                   lcd.print(callSignbuffer);   
                   }
          else if (key == 'C') {
                   bufferIndex = 0;
                   keyIndex = 0;
                   callSignbuffer[0] ='\0';
                   callSignbuffer[1] = '\0';
                   lcd.setCursor(0, 2);
                   lcd.print("                    ");
                   lcd.setCursor(0, 2);
                   }
          else if (key == 'D') {
                   }
          else {
                currentKey[0] = key;
                currentKey[1] = '\0';
                keySwitch = atoi(currentKey);
                callSignbuffer[bufferIndex + 1] = '\0';
                lcd.setCursor(0, 2);
                keyEntered = true;
                switch (keySwitch)    {    
                    case 0:
                       callSignbuffer[bufferIndex] = '0' ;
                       lcd.print(callSignbuffer);
                       break;
                                   
                    case 1:
                       callSignbuffer[bufferIndex] = '1' ;
                       lcd.print(callSignbuffer);
                       break;            
 
                     case 2:
                       callSignbuffer[bufferIndex] = keyTable2[keyIndex][0] ;
                       lcd.print(callSignbuffer);
                       keyIndex++;
                       if (keyIndex == 4) {
                           keyIndex = 0;
                       }
                      break;

                    case 3: 
                       callSignbuffer[bufferIndex] = keyTable3[keyIndex][0] ;
                       lcd.print(callSignbuffer);
                       keyIndex++;
                       if (keyIndex == 4) {
                           keyIndex = 0;
                       }
                      break;

                    case 4:
                       callSignbuffer[bufferIndex] = keyTable4[keyIndex][0] ;
                       lcd.print(callSignbuffer);
                       keyIndex++;
                       if (keyIndex == 4) {
                           keyIndex = 0;
                       }
                      break;
           
                    case 5:            
                       callSignbuffer[bufferIndex] = keyTable5[keyIndex][0] ;
                       lcd.print(callSignbuffer);
                       keyIndex++;
                       if (keyIndex == 4) {
                           keyIndex = 0;
                       }
                      break;
    
                    case 6:
                       callSignbuffer[bufferIndex] = keyTable6[keyIndex][0] ;
                       lcd.print(callSignbuffer);
                       keyIndex++;
                       if (keyIndex == 4) {
                           keyIndex = 0;
                       }
                      break;

                    case 7:
                       callSignbuffer[bufferIndex] = keyTable7[keyIndex][0] ;
                       lcd.print(callSignbuffer);
                       keyIndex++;
                       if (keyIndex == 5) {
                           keyIndex = 0;
                       }
                      break;
            
                    case 8:
                       callSignbuffer[bufferIndex] = keyTable8[keyIndex][0] ;
                       lcd.print(callSignbuffer);
                       keyIndex++;
                       if (keyIndex == 4) {
                           keyIndex = 0;
                       }
                      break;

                    case 9:
                       callSignbuffer[bufferIndex] = keyTable9[keyIndex][0] ;
                       lcd.print(callSignbuffer);
                       keyIndex++;
                       if (keyIndex == 5) {
                           keyIndex = 0;
                       }
                      break;

                   default:
                     break;   
  
                     }
                  lcd.setCursor(0, 2);
                  lcd.print(callSignbuffer);
                
                          
                }
      }
    }
}
/*************************************
 *      get the current squelch level
*************************************/

void getCallsign()
{
#ifdef DEBUG  
  Serial.println("Get call sign");
#endif

 sendReadcmd("CL?\r");
 get_UV3buff();
 for (int i = 0; i < 15; i++) {
      if (UV3buff[4 + i] == '\r' || UV3buff[4 + i] == '\0' ) {
          break;
          }
      radioCallsign[i]= UV3buff[4 + i];
      }
}

