/**************************************************
 *   get_repeater_info
**************************************************/

void get_repeater_info()
{

  sendReadcmd("AF?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Audio LPF");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("AI?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Arduino In Pin");
  lcd.setCursor(0, 1);
  lcd.print("Function");
  lcd.setCursor(0, 2);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("AO?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Arduino Output Pin");
  lcd.setCursor(0, 1);
  lcd.print("Function");
  lcd.setCursor(0, 2);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("B1?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Arduino USB Speed");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("B2?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("I/O Connector Serial");
  lcd.setCursor(0, 1);
  lcd.print("Baud Rate");
  lcd.setCursor(0, 2);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("BM?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Beacon Message");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("BT?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Beacon Timer");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("CF?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CW Audio Freq");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("CL?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CW Call Sign");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("CS?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CW Speed");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("DD?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DTMF Tone Duration");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("DP?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pre-emphasis State");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("DR?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DTMF Detector State");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("EX?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("E-pin state ");
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
  lcd.print("Firmware Version");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("GM?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mic Gain");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("GT?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CW/DTMF Tone Gain");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("HT?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("HangTime");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("IT?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CW ID Timer");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("PD?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Power Down State");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("PW?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TX Power Level");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("SD?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Side Tone State");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("SO?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Squelch State");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("SQ?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Squelch Level");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("TF?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CTCCS Tone Freq");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("TG?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TX Time Out CW");
  lcd.setCursor(0, 1);
  lcd.print("Message");
  lcd.setCursor(0, 2);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("TM?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CTCSS Mode");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("TO?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TX Time Out Timer");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("TP?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PCB Temperature");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("VT\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Operating Voltage");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();
  
  sendReadcmd("VU?\r");
  get_UV3buff();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Volume");
  lcd.setCursor(0, 1);
  lcd.print(UV3buff);
  delay2k();

  lcd.clear();
}

