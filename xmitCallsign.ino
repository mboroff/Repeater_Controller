/****************************
 * xmitCallsign
****************************/

void xmitCallsign()
{

   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Transmit Call Sign");
   lcd.setCursor(0, 3);
   lcd.print("Sending call sign");
   sendDatacmd("CT", myCallsign);
   delay(5000);
   lcd.clear();
  
}

