/***************************************
 * Set freq function  No backspace key - 
 * if user makes an error they can hit #
****************************************/
void setFreq()
{
#ifdef DEBUG
Serial.println("Entring frequency menu");
#endif  
  lcd.clear();                          // draw the option screen
  for(int i = 0; i < 6; i++){
      inputFld[i] = '/0';
  }
  lcd.setCursor(0, 0);
  if (freqSwitch == 1) {                // am I processing recev freq
      strcpy(oldFreq, recvFreq);
      lcd.print("Set Rx Freq");
      lcd.setCursor(0, 2);
      lcd.print("Rx: ---.---");
  } else  {               // am I processing xmit freq
           strcpy(oldFreq, xmitFreq);
           lcd.print("Set Tx Freq");
           lcd.setCursor(0, 2);
           lcd.print("Tx: ---.---");
          }
  lcd.setCursor(4, 2);      
  menuSwitch = 0;                    // ensure while loop runs
  inputCtr = 0;  
  while(menuSwitch == 0) {               // processing loop
    key = keypad.getKey();               // see if a key has been pressed
    if (key) {
        if (buzzerEnabled == true){
            beep();                    
            }

        if (key == '*') {             // confirmation key not allowed
            lcd.setCursor(0, 3);
            lcd.print("All digits required");
            delay(2000);
            lcd.setCursor(0, 3);
            lcd.print("                   ");
            } 
            else if (key == '#') {                // cancel key
                     if (freqSwitch == 1) {
                         strcpy(recvFreq, oldFreq);
                         } else {
                                strcpy(xmitFreq, oldFreq);
                                      }
                      lcd.clear();
                      menuSwitch = 1;
                      break;
                      }
            else {
                  if (inputCtr < 3) {
                      lcd.setCursor(inputCtr + 4, 2);
                      } else {
                             lcd.setCursor(inputCtr + 5, 2);
                             }
                 if (key != 'A' && key != 'B' && key != 'C' && key != 'D') {           
                     lcd.print(key);
                     inputFld[inputCtr] = key;      // copy input character into input field
                     inputCtr++;
                     if (inputCtr == 3) {          // skip over decimal point
                         lcd.print(".");
                         }
                     if(inputCtr == 6) {            // at end of input field? 
                         currentFrequency = atol(inputFld);
                         returnCode = DoRangeCheck();             // make sure it is in band
                         if (returnCode == FREQOUTOFBAND) {         // check if frequency is out of band
                             lcd.setCursor(0, 3);
                             lcd.print("Freq out of band");
                             strcpy(recvFreq,oldFreq);
                             delay(2000);
                             menuSwitch = 1;
                             break;
                             }
                              else {                               // it is in band
                                    if (buzzerEnabled == true){
                                        beep();                    
                                        }
                                    delay(200);
                                    if (buzzerEnabled == true){
                                        beep();                    
                                        }

                                    lcd.setCursor(4, 2);
                                    showFreq();
                                    if (freqSwitch == 1) {                 // if processing recv
                                        memcpy (recvFreq,inputFld, 6);
                                        memcpy (UV3buff, inputFld, 6);
                                        lcd.setCursor(4,2);
                                        currentFrequency = atol(recvFreq);
                                        if (currentDevice == 0) {    // check device
                                            UV3A.write('\r');
                                            UV3A.print("FR");
                                            UV3A.write(UV3buff);
                                            UV3A.write("000");              // freq is stored in kHz
                                            UV3A.write('\r');
                                            delay(200);
                                            UV3A.flush();
                                            UV3A.print("ST");
                                            UV3A.write(memoryChannel);
                                            UV3A.write('\r');
                                            } else {                     // device 2
                                                    UV3B.write('\r');
                                                    UV3B.print("FR");
                                                    UV3B.write(UV3buff);
                                                    UV3B.write("000");         // freq is stored in kHz
                                                    UV3B.write('\r');
                                                    delay(200);
                                                    UV3B.flush();
                                                    UV3B.print("ST");
                                                    UV3B.write(memoryChannel);
                                                    UV3B.write('\r');

                                            }
                                        } else {          // if processing xmit
                                                memcpy (xmitFreq, inputFld, 6);     
                                                memcpy (UV3buff, inputFld, 6);     
                                                lcd.setCursor(4, 2);
                                                currentFrequency = atol(xmitFreq);
               
                                                if (currentDevice == 0) {    // check device
                                                    UV3A.write('\r');
                                                    UV3A.print("FT");
                                                    UV3A.write(UV3buff);
                                                    UV3A.write("000");
                                                    UV3A.write('\r');
                                                    delay(200);
                                                    UV3A.flush();
                                                    UV3A.print("ST");
                                                    UV3A.write(memoryChannel);
                                                    UV3A.write('\r');
                                                    } else  {    // 2nd device
                                                             UV3B.write('\r');
                                                             UV3B.print("FT");
                                                             UV3B.write(UV3buff);
                                                             UV3B.write("000");
                                                             UV3B.write('\r');
                                                             delay(200);
                                                             UV3B.flush();
                                                             UV3B.print("ST");
                                                             UV3B.write(memoryChannel);
                                                             UV3B.write('\r');
                                                             }                                      }
                                               delay(200);
                                               lcd.setCursor(0, 3);
                                               lcd.print("Freq saved");
                                               delay(2000);
                                               menuSwitch = 1;
                                               break;
                                  }                                    // end of in band

                        }                 // end of counter = 6
                   }            // end of input key
              } // end  of not * or #
    }   // end of input key
  }   // end of while
}

/******************************
 * get frequency
 ****************************/
void getFreq()
{
#ifdef DEBUG  
  Serial.println("get frequency");
#endif  
  sendReadcmd("F?\r");
  get_UV3buff();
         
  for (int i = 0; i < 3; i++) {
       recvFreq[i] = UV3buff[6 + i];
       xmitFreq[i] = UV3buff[20 +i];
       }
  for (int i = 0; i < 3; i++) {
       recvFreq[i + 3] = UV3buff[9 + i];
       xmitFreq[i+ 3] = UV3buff[23 +i];
       }
}

/****************************************
 * Print frequency 
****************************************/

void printFreq()
{
#ifdef DEBUG
  Serial.println("ptrintFreq");
#endif

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("RX: ");
  currentFrequency = atol(recvFreq);
#ifdef DEBUG
  Serial.print("currentFrequency = "); Serial.println(currentFrequency);
#endif
  showFreq();
  lcd.setCursor(0, 0);
  lcd.print("RS-UV3 Controller ");
  if (currentDevice == 0) {    // check device
      lcd.print("A");
      }
  if (currentDevice == 1) {    // check device
      lcd.print("B");
      }
  lcd.setCursor(0,2);
  lcd.print("TX: ");
  currentFrequency = atol(xmitFreq);
#ifdef DEBUG
  Serial.print("currentFrequency = "); Serial.println(currentFrequency);
  Serial.print("RX: ");
  Serial.println(recvFreq);
  Serial.print("TX: ");
  Serial.println(xmitFreq);
#endif
  showFreq();
  lcd.setCursor(16, 1);
  lcd.print(radioTemp);
}
/******************************************************
  format current frequency 
******************************************************/
void showFreq() 
{
#ifdef DEBUG
Serial.println("showFreq");
#endif  
  int offset = 0;
  hundredthousands = ((currentFrequency / 100000) % 10);
  temp[0 + offset] = (char) (hundredthousands + 48);
  tenthousands = ((currentFrequency / 10000) % 10);
  temp[1 + offset] = (char) (tenthousands + 48);
  thousands = ((currentFrequency / 1000) % 10);
  temp[2 + offset] = (char) (thousands + 48);
  temp[3 + offset] = '.';
  hundreds = ((currentFrequency / 100) % 10);
  temp[4 + offset] = (char) (hundreds + 48);
  tens = ((currentFrequency / 10) % 10);
  temp[5 + offset] = (char) (tens + 48);
  ones = ((currentFrequency / 1) % 10);
  temp[6 + offset] = (char) (ones + 48);
  temp[7 + offset] = ' ';
  temp[8 + offset] = '\0';

  lcd.print(temp);
  lcd.print("   ");
#ifdef DEBUG
  Serial.print("temp ="); Serial.println(temp);
#endif
}



/**********************************************
 *    check current frequency is in band
**********************************************/

int DoRangeCheck()
{
#ifdef DEBUG  
  Serial.print("current freq = "); Serial.println(currentFrequency);
#endif  
  if (currentFrequency >= TWOMLOWERFREQUENCYLIMIT && currentFrequency <= TWOMUPPERFREQUENCYLIMIT) {
      return FREQINBAND;
      } 
  else if (currentFrequency >= TWOTWENTYLOWERFREQUENCYLIMIT && currentFrequency <= TWOTWENTYUPPERFREQUENCYLIMIT) {
           return FREQINBAND;
           } 
  else if (currentFrequency >= FOURFORTYLOWERFREQUENCYLIMIT && currentFrequency <= FOURFORTYUPPERFREQUENCYLIMIT) {
           return FREQINBAND;
           } 
  return FREQOUTOFBAND;
}

