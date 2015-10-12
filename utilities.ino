/***********************************
 *  general functions 
***********************************/

void beep()
{
     tone(BUZZER, 700, 100);
}

/*******************************
 *   get_UV3buff() 
 *******************************/

byte get_UV3buff()
{
#ifdef DEBUGGETUVBUFF
  Serial.println("Get UV3buff");
#endif  
  byte k = 0;
  unsigned long T = millis() + 100;
  char c = 0;
  
  while ((millis() < T) && (c != '\r')){
  if (currentDevice == 0) {              // which device
    if(UV3A.available()){           // Data received ?
      c = UV3A.read();
#ifdef DEBUGC
Serial.println(c);
#endif
      UV3buff[k++] = c;
      if (c == '\r'){
          UV3buff[--k] = 0;
          }
    }  
  }else {
         if(UV3B.available()){          // Data received ?
            c = UV3B.read();
#ifdef DEBUGC
Serial.println(c);
#endif
            UV3buff[k++] = c;
            if (c == '\r'){
                UV3buff[--k] = 0;
               }
            }

         }
#ifdef DEBUGGETUVBUFF  
  Serial.println(UV3buff);
#endif  
     }
  UV3A.flush();
  UV3B.flush();   
  if (c == 13){
      return 1;
      }
  return 0;
}

/*******************************************
 *      get config info from current device
********************************************/

void getConfiginfo()
{
#ifdef DEBUG
   Serial.println("Get config");
#endif  
  getFreq();
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
     UV3A.write('\r');
     UV3A.print("TP\r");
 } else {
     UV3B.write('\r');
     UV3B.print("TP\r");
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
  UV3A.flush();
  UV3B.flush();
}

/***************************
 *   Send a query to RS-UV3
 */
void sendReadcmd(char* cmd)
{
  for (int i = 0; i <32 ; i++) {
       UV3buff[i] = '\0';       //clear the buff
       }
  flushBuffers();
  if (currentDevice == 0) {
      UV3A.write('\r');
      UV3A.flush();
      UV3A.print(cmd);
      delay200();
      } else {
              UV3B.write('\r');
              UV3B.flush();
              UV3B.print(cmd);
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
     UV3A.write('\r');
     UV3A.flush();
     UV3A.print(cmd);
     UV3A.write(data);
     UV3A.write('\r');
     delay200();
     UV3A.print("ST0");
     UV3A.write('\r');
     delay200();
     } else { 
             UV3B.write('\r');
             UV3B.flush();
             UV3B.print(cmd);
             UV3B.write(data);
             UV3B.write('\r');
             delay200();
             UV3B.print("ST0");
             UV3B.write('\r');
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
     UV3A.write('\r');
     UV3A.flush();
     UV3A.print(cmd);
     UV3A.print(data);
     UV3A.write('\r');
     delay200();
     } else { 
             UV3B.write('\r');
             UV3B.flush();
             UV3B.print(cmd);
             UV3B.print(data);
             UV3B.write('\r');
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


