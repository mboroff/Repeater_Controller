/******************************************
 * Set the time - scroll through the values 
 * and let user accept the next entry
 * Clock is set in 24 Hr format but displayed
 * in 12 Hr format
******************************************/

void settheTime()
{
#ifdef DEBUG
 Serial.println(functionLabels[menuSelect-1]);
#endif 
  lcd.clear();                               // cear the diaplay
  lcd.setCursor(0, 0);
  lcd.print(F("Set Clock Time Zone"));                   // print the title
  lcd.setCursor(0, 1);
  lcd.print(F("A = East B = Central"));               // print the prompt
  lcd.setCursor(0, 2);
  lcd.print(F("C = Mountain"));               // print the prompt
  lcd.setCursor(0, 3);
  lcd.print(F("D = West  "));               // print the prompt

  menuSwitch = 0;                            // ensure the loop runs
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
                } else if (key == txtA) {           //   East time zone = 5
                           utcOffset = 5;
                           localOffset = 5;
                           break;
                } else if (key == txtB) {          //   Centrl time zone = 6
                           utcOffset = 6;
                           localOffset = 6;
                           break;
                } else if (key == txtC) {          //   Mountain time = 7
                           utcOffset = 7;
                           localOffset = 7;
                           break;
                } else if (key == txtD) {          //   Western time zone = 8
                           utcOffset = 8;
                           localOffset = 8;
                           break;

          }
      }
  }


EEPROM.write(utcoffsetAddr, utcOffset);
EEPROM.write(localoffsetAddr, localOffset);                  
         
/***************************************
 * this routine will present each uinit of the time and date. 1st hour then minute then second.....
 */
  lcd.clear();                               // clear the diaplay
  lcd.setCursor(0, 0);
  lcd.print(functionLabels[menuSelect-1]);                   // print the title
  lcd.setCursor(0, 3);
  lcd.print(txtAorB);               // print the prompt
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
            if (key == txtHashTag) {               // cancel key
                lcd.clear();
                menuSwitch = 1;
                break;
                } else if (key == txtStar) {            // confirmation key
                           timeFldswitch++;               // bump the switch used to know which field is being updated
                           if (timeFldswitch == 1) {            // is it hour that was confirmed
                               myHour = timeCtr;                   // save the ctr in hour
                               timeCtr = 1;                      // reset the counter for the next field
                               lcd.setCursor(1, 1);              // print hour
                               if (myHour < 10) {
                                   lcd.print(txtZero);
                                   }
                               lcd.print(myHour);    
                               lcd.print(txtColon);                     // print the colon
                               } else if (timeFldswitch == 2) {      // is it minute that was confirmed
                                          myMinute = timeCtr;           // save the ctr in minute
                                          timeCtr = 1;              // rest the ctr for the next field
                                          lcd.setCursor(4, 1);      // print minute
                                          if (myMinute < 10) {
                                              lcd.print(txtZero);
                                              }
                                          lcd.print(myMinute);
                                          lcd.print(txtColon);
                               } else if (timeFldswitch == 3) {      // is second being confirmed
                                         mySecond = timeCtr;           // save the ctr in second/
                                          timeCtr = 1;               // reset the ctr for the next field
                                          lcd.setCursor(7, 1);       // print second
                                          if (mySecond < 10) {
                                              lcd.print(txtZero);
                                              }
                                          lcd.print(mySecond);
                                          lcd.print(txtSpaceThree);
                               } else if (timeFldswitch == 4) {      // is month being confirmed

                                          myMonth = timeCtr;           // save the ctr in month
                                          timeCtr = 1;               // reset the ctr for the next field
                                          lcd.setCursor(10, 1);       // print month
                                          if (myMonth < 10) {
                                              lcd.print(txtZero);
                                              }
                                          lcd.print(myMonth);
                                          lcd.print(txtSlash);
                               } else if (timeFldswitch == 5) {      // is day being confirmed
                                          myMonthDay = timeCtr;           // save the ctr in day
                                          timeCtr = 2015;               // reset the ctr for the next field
                                          lcd.setCursor(13, 1);       // print day
                                          if (myMonthDay < 10) {
                                              lcd.print(txtZero);
                                              }
                                          lcd.print(myMonthDay);
                                          lcd.print(F("/   "));
                               } else if (timeFldswitch == 6) {      // is day being confirmed
                                          myYear = timeCtr;           // save the ctr in year
                                          lcd.setCursor(16, 1);       // print year
                                          lcd.print(myYear);
                                          lcd.setCursor(0, 4);
                                          lcd.print(F("Time updated       "));
                                          delay2k();
                          // This sets the system time 
                          // set your seperated date/time variables out as normal and update system time FIRST
                                          rtc.setTime(myHour, myMinute, mySecond); 
                                          rtc.setDate(myMonthDay, myMonth, myYear);
                                           lcd.clear();
                                           menuSwitch = 1;
                                           break;
                                           } 
                  printTimefld();            
                  } else if (key == txtA) {              // increment Time value
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
                } else if (key == txtB) {              // decrement Time value
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

  lcd.setCursor(0, 2);              // print each unit being worked upon on line 3 
  if (timeFldswitch == 0) {
      lcd.print(F("Hour = "));
      if (timeCtr < 10) {
          lcd.print(txtZero);
      }
      lcd.print(timeCtr);
      lcd.print(txtSpaceTen);
  } else if (timeFldswitch == 1) {
             lcd.print(F("Minute = "));
             if (timeCtr < 10) {
                 lcd.print(txtZero);
                 }
             lcd.print(timeCtr);
             lcd.print(txtSpaceTen);    
  } else if (timeFldswitch == 2) {
             lcd.print(F("Second = "));
             if (timeCtr < 10) {
                 lcd.print(txtZero);
                 }
              lcd.print(timeCtr);
              lcd.print(txtSpaceTen);    
  } else if (timeFldswitch == 3) {
             lcd.print(F("Month = "));
             if (timeCtr < 10) {
                 lcd.print(txtZero);
                 }
              lcd.print(timeCtr);
              lcd.print(txtSpaceTen);    
  } else if (timeFldswitch == 4) {
             lcd.print(F("Day = "));
             if (timeCtr < 10) {
                 lcd.print(txtZero);
                 }
              lcd.print(timeCtr);
              lcd.print(txtSpaceTen);    
  } else if (timeFldswitch == 5) {
             lcd.print(F("Year = "));
             if (timeCtr < 10) {
                 lcd.print(txtZero);
                 }
              lcd.print(timeCtr);
              lcd.print(txtSpaceTen);    
              }
}             


  


