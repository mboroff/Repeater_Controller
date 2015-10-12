/******************************************
 * Set the time - scroll through the values 
 * and let user accept the next entry
******************************************/

void settheTime()
{
#ifdef DEBUG
 Serial.println("enter set the time menu");
#endif 
  lcd.clear();                               // cear the diaplay
  lcd.setCursor(0, 0);
  lcd.print("Set Clock");                   // print the title
  lcd.setCursor(0, 3);
  lcd.print("Press A or B");               // print the prompt
  myHr = 1;                                // initialize the time defaults
  myMin = 1;
  mySec = 1;
  myMonth = 1;
  myDay = 1;
  myYr = 2015;
  menuSwitch = 0;                            // ensure the loop runs
  timeFldswitch = 0;                         // initialize counters used in loop
  timeCtr = 1;
  printTimefld();
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
                } else if (key == '*') {            // confirmation key
                           timeFldswitch++;               // bump the switch used to know which field is being updated
                           if (timeFldswitch == 1) {            // is it hour that was confirmed
                               myHr = timeCtr;                   // save the ctr in hour
                               timeCtr = 1;                      // reset the counter for the next field
                               lcd.setCursor(1, 1);              // print hour
                               if (myHr < 10) {
                                   lcd.print("0");
                                   }
                               lcd.print(myHr);    
                               lcd.print(":");                     // print the colon
                               } else if (timeFldswitch == 2) {      // is it minute that was confirmed
                                          myMin = timeCtr;           // save the ctr in minute
                                          timeCtr = 1;              // rest the ctr for the next field
                                          lcd.setCursor(4, 1);      // print minute
                                          if (myMin < 10) {
                                              lcd.print("0");
                                              }
                                          lcd.print(myMin);
                                          lcd.print(":");
                               } else if (timeFldswitch == 3) {      // is second being confirmed
                                          mySec = timeCtr;           // save the ctr in second/
                                          timeCtr = 1;               // reset the ctr for the next field
                                          lcd.setCursor(7, 1);       // print second
                                          if (mySec < 10) {
                                              lcd.print("0");
                                              }
                                          lcd.print(mySec);
                                          lcd.print("   ");
                               } else if (timeFldswitch == 4) {      // is month being confirmed
                                          myMonth = timeCtr;           // save the ctr in month
                                          timeCtr = 1;               // reset the ctr for the next field
                                          lcd.setCursor(10, 1);       // print month
                                          if (myMonth < 10) {
                                              lcd.print("0");
                                              }
                                          lcd.print(myMonth);
                                          lcd.print("/");
                               } else if (timeFldswitch == 5) {      // is day being confirmed
                                          myDay = timeCtr;           // save the ctr in day
                                          timeCtr = 2015;               // reset the ctr for the next field
                                          lcd.setCursor(13, 1);       // print day
                                          if (myDay < 10) {
                                              lcd.print("0");
                                              }
                                          lcd.print(myDay);
                                          lcd.print("/   ");
                               } else if (timeFldswitch == 6) {      // is day being confirmed
                                          myYr = timeCtr;           // save the ctr in year
                                          lcd.setCursor(16, 1);       // print year
                                          lcd.print(myYr,DEC);
                                          lcd.setCursor(0, 4);
                                          lcd.print("Time updated       ");
                                          delay2k();
                                          time_t t = processSyncMessage();
                                          myYr = myYr - 2000;
                          // This sets the system time (NOT the Teensy RTC Clock)
                          // set your seperated date/time variables out as normal and update system time FIRST
                          //setTime(hour(), minute(), second(), day(), month(), year())
                                          setTime(myHr, myMin, mySec, myDay, myMonth, myYr);

                          // now lets set the RTC in teensy before exiting.
                          // now we can use the system time to update the Teensy's RTC bits
                          // This sets the Teensy RTC Clock from Arduino Time library(system time) - epoch stylee, just like it wants :)
                                           Teensy3Clock.set(now());
                                           lcd.clear();
                                           menuSwitch = 1;
                                           break;
                                           } 
                  printTimefld();            
                  } else if (key == 'A' ) {              // increment CTCCS value
                             timeCtr++;
                             if (timeFldswitch == 0) {   // working on hour
                                 if (timeCtr > 23) {
                                     timeCtr = 0;
                                     }
                             } else if (timeFldswitch == 1 || timeFldswitch == 2) {
                                        if (timeCtr > 59) {     // working on minutes or seconds
                                            timeCtr = 1;
                                            }
                             } else if (timeFldswitch == 3) {    // working on month
                                        if (timeCtr > 12) {
                                            timeCtr = 1;
                                            }
                             } else if (timeFldswitch == 4) {    // woring on day
                                        if (timeCtr > 31) {
                                            timeCtr = 1;
                                            }
                             }
                             printTimefld();
                } else if (key == 'B' ) {              // decrement CTCCS value
                           timeCtr--;
                           if (timeFldswitch == 0) {                    // working hour
                               if (timeCtr < 0) {
                                   timeCtr = 23;
                                   } 
                               } else if (timeFldswitch == 1 || timeFldswitch == 2) {             // working on minute or seconds
                                          if (timeCtr < 0) {
                                              timeCtr = 59;
                                              }
                               } else if (timeFldswitch == 3) {                    // working on month
                                          if (timeCtr < 1) {
                                              timeCtr = 12;
                                              }
                               } else if (timeFldswitch == 4) {                  // working on day
                                          if (timeCtr < 1) {
                                              timeCtr = 31; 
                                              }
                                } else if (timeFldswitch == 5) {                 // working on year
                                          if (timeCtr < 1) {
                                              timeCtr = 12; 
                                              }
                                          }
                                printTimefld();
          }
      }
  }
}

void printTimefld()
{

  lcd.setCursor(0, 2);
  if (timeFldswitch == 0) {
      lcd.print("Hour = ");
      if (timeCtr < 10) {
          lcd.print("0");
      }
      lcd.print(timeCtr);
      lcd.print("          ");
  } else if (timeFldswitch == 1) {
             lcd.print("Minute = ");
             if (timeCtr < 10) {
                 lcd.print("0");
                 }
             lcd.print(timeCtr);
             lcd.print("          ");    
  } else if (timeFldswitch == 2) {
             lcd.print("Second = ");
             if (timeCtr < 10) {
                 lcd.print("0");
                 }
              lcd.print(timeCtr);
              lcd.print("          ");    
  } else if (timeFldswitch == 3) {
             lcd.print("Month = ");
             if (timeCtr < 10) {
                 lcd.print("0");
                 }
              lcd.print(timeCtr);
              lcd.print("          ");    
  } else if (timeFldswitch == 4) {
             lcd.print("Day = ");
             if (timeCtr < 10) {
                 lcd.print("0");
                 }
              lcd.print(timeCtr);
              lcd.print("          ");    
  } else if (timeFldswitch == 5) {
             lcd.print("Year = ");
             if (timeCtr < 10) {
                 lcd.print("0");
                 }
              lcd.print(timeCtr);
              lcd.print("          ");    
              }
}             


  


