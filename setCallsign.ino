/*********************************************************
 * Set Call Sign  use the keypad like a telephone keypad
**********************************************************/

void SetCallsign()
{
#ifdef DEBUG
Serial.println("Enter set call sign");
#endif
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set Call Sign");
  
  /********************************** scroll through the options *******/
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
  lcd.print("D = /               ");
  delay500();
  lcd.setCursor(0, 1);
  lcd.print("B = Bksp  C = clear ");
  lcd.setCursor(0, 2);
  lcd.print("D = /               ");
  lcd.setCursor(0, 3);  
  lcd.print("                    ");
  delay500();
  lcd.setCursor(0, 1);
  lcd.print("D = /               ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  delay500();
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  delay500();

  /************    set up the input screen *****************/
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
          else if (key == 'A' ) {                // accept the last key value entered and bump he buffer index
                   if (keyEntered == true) {
                       keyEntered = false;
                       bufferIndex++;
                       keyIndex = 0;
                       if (bufferIndex > 19) {
                           bufferIndex = 19;
                           }
                       } 
                    }
          else if (key == 'B') {                          // back space delete the current character and decrement the buffer index
                   callSignbuffer[bufferIndex] = ' ' ;
                   bufferIndex--;
                   if (bufferIndex < 0){
                       bufferIndex = 0;
                       }
                   callSignbuffer[bufferIndex] = ' ' ;
                   lcd.setCursor(0, 2); 
                   lcd.print(callSignbuffer);   
                   }
          else if (key == 'C') {                         // cclear the buffer and reset indexes
                   bufferIndex = 0;
                   keyIndex = 0;
                   callSignbuffer[0] ='\0';
                   callSignbuffer[1] = '\0';
                   lcd.setCursor(0, 2);
                   lcd.print("                    ");
                   lcd.setCursor(0, 2);
                   }
          else {
                if (key == 'D') {                     // D is transformed to a slash 
                    currentKey[0] = '/';
                    currentKey[1] = '\0';
                    callSignbuffer[bufferIndex] = '/';
                    callSignbuffer[bufferIndex + 1] = '\0';
                    lcd.setCursor(0, 2);
                    lcd.print(callSignbuffer);
                } else {                             // numbers 0 - 9 are handled using a table for each key
                currentKey[0] = key;
                currentKey[1] = '\0';
                keySwitch = atoi(currentKey);
                callSignbuffer[bufferIndex + 1] = '\0';
                lcd.setCursor(0, 2);
                keyEntered = true;
                switch (keySwitch)    {    
                    case 0:
                       callSignbuffer[bufferIndex] = '0' ;          // zero is only zero
                       lcd.print(callSignbuffer);
                       break;
                                   
                    case 1:
                       callSignbuffer[bufferIndex] = '1' ;       // 1 is only 1
                       lcd.print(callSignbuffer);
                       break;            
 
                     case 2:
                       callSignbuffer[bufferIndex] = keyTable2[keyIndex][0] ;   // 2 = A, B, C or 2
                       lcd.print(callSignbuffer);
                       keyIndex++;
                       if (keyIndex == 4) {
                           keyIndex = 0;
                       }
                      break;

                    case 3: 
                       callSignbuffer[bufferIndex] = keyTable3[keyIndex][0] ;   // 3 = D E F 3
                       lcd.print(callSignbuffer);
                       keyIndex++;
                       if (keyIndex == 4) {
                           keyIndex = 0;
                       }
                      break;

                    case 4:
                       callSignbuffer[bufferIndex] = keyTable4[keyIndex][0] ;  // 4 = G H I 4
                       lcd.print(callSignbuffer);
                       keyIndex++;
                       if (keyIndex == 4) {
                           keyIndex = 0;
                       }
                      break;
           
                    case 5:            
                       callSignbuffer[bufferIndex] = keyTable5[keyIndex][0] ;    // 5 = J K L 5
                       lcd.print(callSignbuffer);
                       keyIndex++;
                       if (keyIndex == 4) {
                           keyIndex = 0;
                       }
                      break;
    
                    case 6:
                       callSignbuffer[bufferIndex] = keyTable6[keyIndex][0] ;   // 6 = M N O 6
                       lcd.print(callSignbuffer);
                       keyIndex++;
                       if (keyIndex == 4) {
                           keyIndex = 0;
                       }
                      break;

                    case 7:
                       callSignbuffer[bufferIndex] = keyTable7[keyIndex][0] ;  // 7 = P Q R S 7
                       lcd.print(callSignbuffer);
                       keyIndex++;
                       if (keyIndex == 5) {
                           keyIndex = 0;
                       }
                      break;
            
                    case 8:
                       callSignbuffer[bufferIndex] = keyTable8[keyIndex][0] ;  // 8 = T U V 8
                       lcd.print(callSignbuffer);
                       keyIndex++;
                       if (keyIndex == 4) {
                           keyIndex = 0;
                       }
                      break;

                    case 9:
                       callSignbuffer[bufferIndex] = keyTable9[keyIndex][0] ;  // 9 = W X Y Z 9
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

}

/*************************************
 *      get the current call sign
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

