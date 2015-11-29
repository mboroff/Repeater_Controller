/****************************
 * xmitCallsign
****************************/

void xmitCallsign()
{
#ifdef DEBUG
Serial.println(functionLabels[menuSelect-1]);
#endif
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print(functionLabels[menuSelect-1]);   // print the function title
   getCallsign();
   lcd.setCursor(0, 2);
   lcd.print(radioCallsign);
   lcd.setCursor(0, 3);
   lcd.print(F("Sending call sign"));
   sendDatacmd("CT", radioCallsign);
   delay(10000);
   lcd.clear();
  
}

