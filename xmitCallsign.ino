/****************************
 * xmitCallsign
****************************/

void xmitCallsign()
{

   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Transmit Call Sign");
   getCallsign();
   lcd.setCursor(0, 2);
   lcd.print(radioCallsign);
   lcd.setCursor(0, 3);
   lcd.print("Sending call sign");
   sendDatacmd("CT", radioCallsign);
   delay(5000);
   lcd.clear();
  
}

