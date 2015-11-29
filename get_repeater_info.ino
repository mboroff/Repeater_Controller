/**************************************************
 *   get_repeater_info all information
 *   the name of each field read is listed 
 *   in the routine
**************************************************/

void get_repeater_info()
{
#ifdef DEBUG
Serial.println(functionLabels[menuSelect-1]);
#endif
  sendReadcmd("AF?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Audio LPF"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("AI?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Arduino In Pin"));
  lcd.setCursor(0, 1);
  lcd.print(txtFunction);               // "Function"
  lcd.setCursor(0, 2);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("AO?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Arduino Output Pin"));
  lcd.setCursor(0, 1);
  lcd.print(txtFunction);
  lcd.setCursor(0, 2);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("B1?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Arduino USB Speed"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("B2?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("I/O Connector Serial"));
  lcd.setCursor(0, 1);
  lcd.print(F("Baud Rate"));
  lcd.setCursor(0, 2);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("BM?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Beacon Message"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("BT?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Beacon Timer"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("CF?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("CW Audio Freq"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("CL?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("CW Call Sign"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("CS?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("CW Speed"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("DD?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("DTMF Tone Duration"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("DP?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Pre-emphasis State"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("DR?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("DTMF Detector State"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("EX?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("E-pin state "));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  lcd.clear();
  getFreq();
  printFreq();
  delay(4000);
  
  sendReadcmd("FW\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Firmware Version"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("GM?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Mic Gain"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("GT?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("CW/DTMF Tone Gain"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("HT?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("HangTime"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("IT?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("CW ID Timer"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("PD?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Power Down State"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("PW?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("TX Power Level"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("SD?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Side Tone State"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("SO?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Squelch State"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("SQ?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Squelch Level"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("TF?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("CTCCS Tone Freq"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("TG?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("TX Time Out CW"));
  lcd.setCursor(0, 1);
  lcd.print(F("Message"));
  lcd.setCursor(0, 2);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("TM?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Tone Squelch Mode"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("TO?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("TX Time Out Timer"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("TP?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("PCB Temperature"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("VT\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Operating Voltage"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("VU?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Volume"));
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();

  lcd.clear();
}

