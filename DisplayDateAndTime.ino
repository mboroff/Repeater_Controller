/**********************************
 * Display the date and time.
 * Time is adjusted for DST
 * Time is displayed in 12 Hr format
 */

void DisplayDateAndTime()
{
 
  lcd.setCursor(0, 3);
    // Get time
   localHour = myHour - utcOffset;  // set the local hour
  
  //   the adjustment following is for DST good till 2099
  
  int beginDSTDay = (14 - (1 + myYear * 5 / 4) % 7);  
  int beginDSTMonth=3;
  int endDSTDay = (7 - (1 + myYear * 5 / 4) % 7);
  int endDSTMonth=11;
  if (((workMonth > beginDSTMonth) && (workMonth < endDSTMonth))
   || ((workMonth == beginDSTMonth) && (workDay > beginDSTDay))
   || ((workMonth == beginDSTMonth) && (workDay == beginDSTDay) && (myHour >= 2))
   || ((workMonth == endDSTMonth) && (workDay < endDSTDay))
   || ((workMonth == endDSTMonth) && (workDay == endDSTDay) && (myHour < 1))) {
        localHour++;
        }
 
  if (localHour < 0) {
      localHour = localHour +24;
  }
  workHour = localHour;            // print local time not UTC time
  
  if (workHour == 0) {                 // adjust hour for 12 hour format
      workHour = 12;
  }
  if (workHour > 12) {
      workHour = workHour - 12;
  }
  if (workHour < 10) {
      lcd.print(txtZero);
  }
  lcd.print(workHour);
  lcd.print(txtColon);
  if (myMinute < 10) {
      lcd.print(txtZero);
  }
  lcd.print(myMinute);                // print minute
  lcd.print(txtColon);
  if (mySecond < 10) {
      lcd.print(txtZero);
  }
  lcd.print(mySecond);              // print second
  lcd.print(" ");
   

   workYear = myYear;            // need to check for leapyear
  if (checkLeapYear(myYear)) {
      daysInmonth[1] = 29;
  }
  workMonth = myMonth;              /// get ready to print date and adjust if UTC is on next day
  workDay = myMonthDay;
  if (localHour > myHour) {       // UTC is next day so let us adjust the date
      workDay = myMonthDay - 1;     //    display to previous day put in leap year later
      if (workDay < 1) {          // change table from static and adjust with get NTP
          workMonth = myMonth - 1;
          if (workMonth < 0) {
              workMonth = 11;
          }
          workDay = daysInmonth[workMonth-1];
      }
      
      if (workMonth < 10) {
          lcd.print(txtZero);
      }
      lcd.print(workMonth);        // print month / day / year
      lcd.print(txtSlash);
      if (workDay < 10) {
          lcd.print(txtZero);
      }
      lcd.print(workDay);
      lcd.print(txtSlash);
      lcd.print(workYear - 2000);
  }
  else {
     lcd.print(rtc.getDateStr(FORMAT_SHORT, FORMAT_MIDDLEENDIAN, '/'));
  }
  

}

boolean checkLeapYear(int yearRequest){              // check for leap year
 if ( yearRequest%4 == 0 && yearRequest%100 != 0 || yearRequest % 400 == 0 ) return true;
     else  return false;
}

