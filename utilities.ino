/***********************************
 *  general functions 
***********************************/

/******************************
 * get_UV3buff
 */
byte get_UV3buff(){
#ifdef DEBUG
Serial.println("get_VU3buff");
#endif
  for (int i= 0; i < 32; i++) {       // clear UV3buff
       UV3buff[i] = txtNull;
  }
  byte k = 0;
  long T = millis() + 100;
  char c = 0;
 if (currentDevice == 0) {  
  while ((millis() < T) && (c != '\r')){   // while data in the serial bufffer
    if(Serial3.available()){
      c = Serial3.read();                  // read a character
      UV3buff[k++] = c;
      if (c == '\r') UV3buff[--k] = 0;
    }
  }
 } else {
  while ((millis() < T) && (c != '\r')){   // while data in the serial buffer
    if(Serial2.available()){            
      c = Serial2.read();                 // read a character
#ifdef DEBUGC      
Serial.println(c);
#endif
      UV3buff[k++] = c;
      if (c == '\r') UV3buff[--k] = 0;
    }
  }
 }
#ifdef DEBUG 
Serial.print(F("UV3buff = ")); Serial.println(UV3buff);
#endif
  if (c == 13){
    return 1;
  }
  return 0;
}

/*************************
 * BEEP
 */

void beep()
{
     tone(BUZZER, 700, 100);
}



/*******************************************
 *      get config info from current device
********************************************/

void getConfiginfo()
{
#ifdef DEBUG
   Serial.println(F("Get config"));
#endif  
  getSquelchlevel();
  getCTCCS();
  getTonemode();
  getradioTemp();
  getVolume();
}

void getradioTemp()
{
#ifdef DEBUG
  Serial.println(F("Get radio temp"));
#endif  
 if (currentDevice == 0) {
     Serial3.write('\r');
     Serial3.print("TP\r");
 } else {
     Serial2.write('\r');
     Serial2.print("TP\r");
 }
 delay200();
  get_UV3buff();
  for (int i = 0; i < 3; i++) {
       radioTemp[i] = UV3buff[6 + i];
       }  
}

/********************************
 * Flush buffers
*********************************/

void flushBuffers()
{
  Serial3.flush();
  Serial2.flush();
}

/***************************
 *   Send a query to RS-UV3
 */
void sendReadcmd(char* cmd)
{
#ifdef DEBUG
Serial.print(F("sendReadcmd ")); Serial.println(cmd);
Serial.print(F("currentDevice = ")); Serial.println(currentDevice);  
#endif
  for (int i = 0; i <32 ; i++) {
       UV3buff[i] = txtNull;       //clear the buff
       }
  flushBuffers();
  if (currentDevice == 0) {
      Serial3.write('\r');
      Serial3.flush();
      Serial3.print(cmd);
      delay200();
#ifdef DEBUG      
Serial.print(F("sendReadcmd ")); Serial.println(cmd);
#endif
      } else {
              Serial2.write('\r');
              Serial2.flush();
              Serial2.print(cmd);
              delay200();
              }
}

/************************
 *  Send a data store to RS-UV3
 */

 void sendStorecmd(char* cmd, char* data)
{
#ifdef DEBUG  
  Serial.print(F("cmd = ")); Serial.println(cmd);
  Serial.print(F("data = ")); Serial.println(data);
#endif 
 flushBuffers();
 if (currentDevice == 0) {
     Serial3.write('\r');
     Serial3.flush();
     Serial3.print(cmd);
     Serial3.write(data);
     Serial3.write('\r');
     delay200();
     Serial3.print("ST0");
     Serial3.write('\r');
     delay200();
     } else { 
             Serial2.write('\r');
             Serial2.flush();
             Serial2.print(cmd);
             Serial2.write(data);
             Serial2.write('\r');
             delay200();
             Serial2.print("ST0");
             Serial2.write('\r');
             delay200();
             }
}


/************************
 *  Send a cmd to RS-UV3 with data
 */

 void sendDatacmd(char* cmd, char* data)
{
  Serial.println(F("sendDatacmd"));
  Serial.print(F("cmd = ")); Serial.println(cmd);
  Serial.print(F("data = ")); Serial.println(data);
  
 flushBuffers();
 if (currentDevice == 0) {
     Serial3.write('\r');
     Serial3.flush();
     Serial3.print(cmd);
     Serial3.print(data);
     Serial3.write('\r');
     delay200();
     } else { 
             Serial2.write('\r');
             Serial2.flush();
             Serial2.print(cmd);
             Serial2.print(data);
             Serial2.write('\r');
             delay200();
             }
}
/*********************
 * delay1K
*********************/
void delay1k()
{
  delay(1000);
}

/************************
 * delay2k
************************/

void delay2k()
{
  delay(2000);
}

/************************
 * delay200();
************************/

void delay200()
{
  delay(200);
}
/************************
 * delay500();
************************/

void delay500()
{
  delay(500);
}

/************************
 * delay4K();
************************/

void delay4k()
{
  delay(4000);
}

/*************************
 * Reset Arduino EEPROM
*************************/
void eraseEEPROM()
{
#ifdef DEBUG
Serial.println(functionLabels[17]);
#endif  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(functionLabels[17]);
  lcd.setCursor(0, 3);
  lcd.print(F("Press * to Reset"));
  menuSwitch = 0;
  while (menuSwitch == 0){

      key = keypad.getKey();               // see if a key has been pressed
      if (key) {
          if (buzzerEnabled == true){
              beep();                    
              }
          if (key == txtHashTag) {               // cancel key
              lcd.clear();
              menuSwitch = 1;
              break;
              }
          else if (key == txtStar) {            // confirmation key
                lcd.setCursor(0, 2);
                lcd.print(F("Erasing "));  
                repeaterEnabled = relayOn; 
                fanEnabled = relayOn;        
                for (int i = 0; i < nextAvalableaddress; i++) {
                     EEPROM.write(i, 0xFF);
                    }
                EEPROM.write(fanAddr, fanEnabled);              // set default value
                EEPROM.write(repeaterAddr, repeaterEnabled);    // set default value
                EEPROM.write(utcoffsetAddr, utcOffset);
                EEPROM.write(localoffsetAddr, localOffset);                  
                EEPROM.write(buzzerAddr, buzzerEnabled);     // save the status in EEPROM
                delay(2000);    
                lcd.print(F("completed."));           
                delay(2000);
                lcd.clear();
                menuSwitch = 1;
                break;
                  }
      }
  }
    
}

