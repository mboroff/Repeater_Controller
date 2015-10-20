/***********************************
 *  general functions 
***********************************/

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
   Serial.println("Get config");
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
  Serial.println("Get radio temp");
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
Serial.print("sendReadcmd "); Serial.println(cmd);
Serial.print("currentDevice = "); Serial.println(currentDevice);  
#endif
  for (int i = 0; i <32 ; i++) {
       UV3buff[i] = '\0';       //clear the buff
       }
  flushBuffers();
  if (currentDevice == 0) {
      Serial3.write('\r');
      Serial3.flush();
      Serial3.print(cmd);
      delay200();
#ifdef DEBUG      
Serial.print("sendReadcmd "); Serial.println(cmd);
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


