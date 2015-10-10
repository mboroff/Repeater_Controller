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
 delay(200);
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


