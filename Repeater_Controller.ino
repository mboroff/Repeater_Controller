/*********************************************************************
 * UV-RS3 Repeater Controller
 * We invest time and resources providing this open source code, 
  please support us and open-source hardware by purchasing 
  products from HobbyPCB!

  Written by Martin Boroff WD9GYM.  
  BSD license, all text above must be included in any redistribution

  Frequency display function taken from VFO project in
  Arduino Projects for Amateur Radio, McGraw-Hill Publishing 
  by Jack Purdum & Dennis Kidder. 

*********************************************************************/

/******************
 * DEBUG statemnts
 */
//#define DEBUG 1
//#define DEBUGGETUVBUFF 1
//#define DEBUGTIME 1
//#define DEBUGC 1 
//#define DEBUGTM 1

/******************************************
 *         Includes
******************************************/
#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Time.h>
#include <DS1307RTC.h>
//#include <SoftwareSerial.h>
#include <stdint.h>
#include <EEPROM.h>

#define BUZZER 12.

#define FANPIN      11
#define REPEATERPIN 10
#define relayOn 0
#define relayOff 1
/***********************************
 * Time 
************************************/
tmElements_t tm;
const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};


/*********************************************************
 *   Valid pins for serial software ATMEGA2560
* RX: 10, 11, 12, 13, 14, 15, 50, 51, 52, 53, A8 (62), 
* A9 (63), A10 (64), A11 (65), A12 (66), A13 (67), 
* A14 (68), A15 (69). 
*********************************************************/
//SoftwareSerial UV3A(52, 53); // RX, TX
//SoftwareSerial UV3B(50, 51); // RX, TX

/*******************************************
 *           LCD definitions
 *******************************************           
 */
/*-----( Declare Constants )-----*/
/*-----( Declare objects )-----*/
// set the LCD address to 0x27 for a 20 chars 4 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
char lcdBuffer[21] = "                    ";
int lcdBufferctr = 0;
#define LCDCOLS          20               // LCD stuff
#define LCDROWS           4

/*************************************************
 *         keypad definitions
 **************************************************/
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

/***************************
 *  Global Variables
***************************/
    
int bufferIndex = 0;
int buzzerAddr = 0; /** the current address in the EEPROM (i.e. which byte we're going to write to next) **/
int deviceAddr = 1;
int freqSwitch = 0, CTCCSswitch = 0;
int fanAddr = 2;
int keyIndex = 0;
int keySwitch = 0;
unsigned int myHr,myMin,mySec,myDay,myMonth,myYr;
int inputCtr = 0, CTCCSctr = 1;
int menuSwitch = 0,  menuSelect = 1, currentDevice = 0;
int prevSecond = 99;
int radioCTCCSi;
int repeaterAddr = 2;
int fanEnabled = relayOn, repeaterEnabled = relayOn;
int returnCode;
int squelchValue;
int timeFldswitch = 0;
int timeCtr = 0;
int tmCtr = 0;
int volumeCtr = 0;

float radioCTCCSf;
  
char callSignbuffer[21];
char currentKey[2];
char dataFld[32];
char inputFld[8];
char key;
char memoryChannel[2];
char myCallsign[16];
char prevKey;
char radioCallsign[16];
char radioCTCCS[6];
char radioTemp[4];
char recvFreq[8], xmitFreq[8], oldFreq[8];
char squelchLevel[2] = " ";
char temp[17];
char toneMode[5];
char UV3buff[32];
char UV3volume[3];

boolean keyEntered = false;
boolean repeaterSwitch = true, buzzerEnabled = true;

boolean SQ_OP = false;

#define TWOMUPPERFREQUENCYLIMIT      148000L  // Upper band edge
#define TWOMLOWERFREQUENCYLIMIT      144000L  // Lower band edge
#define TWOTWENTYUPPERFREQUENCYLIMIT 225000L  // Upper band edge
#define TWOTWENTYLOWERFREQUENCYLIMIT 222000L  // Lower band edge
#define FOURFORTYUPPERFREQUENCYLIMIT 450000L  // Upper band edge
#define FOURFORTYLOWERFREQUENCYLIMIT 420000L  // Lower band edge
#define FREQINBAND        0               // Used with range checking
#define FREQOUTOFBAND     1

volatile int_fast32_t currentFrequency;

byte ones, tens, hundreds, thousands, tenthousands, hundredthousands, millions; // Placeholders

String str;  
String squelchStr;
String radioCTCCSstr;
String volumeStr;

/***********************************
 *    Function menu titles
***********************************/
#define MAXFUNCTIONS 14
#define MAXITEMSIZE 20
char functionLabels[MAXFUNCTIONS][MAXITEMSIZE] = 
       { "Set Rx Freq        ", "Set Tx Freq        ", 
         "Set Sqlch Level    ", "Tone Sqlch Mode    ", 
         "Set CTCSS          ", "Repeater ON/OFF    ", 
         "BEEP ON/OFF        ", "Fan ON/OFF         ",
         "Set Clock          ", "Set Volume         ",        
         "Display System Info", "Reset RS-UV3       ",
         "Set Call Sign      ", "Transmit Call Sign "
         };
#define NUMBEROFTONES 50
#define SIZEOFTONE 6
char CTCSStable[NUMBEROFTONES][SIZEOFTONE] =
      { "67.0 ", "69.3 ", "71.9 ", "74.4 ",
        "77.0 ", "79.7 ", "82.5 ", "85.4 ",
        "88.5 ", "91.5 ", "94.8 ", "97.4 ",
        "100.0", "103.5", "107.2", "110.9",
        "114.8", "118.8", "123.0", "127.3",
        "131.8", "136.5", "141.3", "146.2",
        "151.4", "156.7", "159.8", "162.2",
        "165.5", "167.9", "171.3", "173.8",
        "177.8", "179.9", "183.5", "186.2",
        "189.9", "192.8", "196.6", "199.5",
        "203.5", "206.5", "210.7", "218.1",
        "225.7", "229.1", "233.6", "241.8",
        "250.3", "254.1"
      };
/*********************************
 *  keypad tables
*********************************/
#define MAXKEYVALUES 5
#define KEYVALUESIZE 2
char keyTable2[MAXKEYVALUES][KEYVALUESIZE] = 
       { "A", "B","C", "2"," "};
char keyTable3[MAXKEYVALUES][KEYVALUESIZE] = 
       { "D", "E","F", "3"," "};
char keyTable4[MAXKEYVALUES][KEYVALUESIZE] = 
       { "G", "H","I", "4"," "};
char keyTable5[MAXKEYVALUES][KEYVALUESIZE] = 
       { "J", "K","L", "5"," "};
char keyTable6[MAXKEYVALUES][KEYVALUESIZE] = 
       { "M", "N","O", "6"," "};
char keyTable7[MAXKEYVALUES][KEYVALUESIZE] = 
       { "P", "Q","R", "S","7"};
char keyTable8[MAXKEYVALUES][KEYVALUESIZE] = 
       { "T", "U","V", "8"," "};
char keyTable9[MAXKEYVALUES][KEYVALUESIZE] = 
       { "W", "X","Y", "Z","9"};


/****************************************************
 *                  Setup
*****************************************************/
void setup(){
   pinMode(BUZZER, OUTPUT);
   digitalWrite(BUZZER, LOW);            // turn off the relay

   pinMode(FANPIN, OUTPUT);
   digitalWrite(FANPIN, HIGH);            // turn off the relay
   pinMode(REPEATERPIN, OUTPUT);
   digitalWrite(REPEATERPIN, HIGH);       // turn off the relay
/*******************************
 *         Serial start
********************************/
  Serial.begin(19200);
  Serial3.begin(19200);
  Serial2.begin(19200);

    // Set the clock to run-mode

  lcd.begin(20,4);         // initialize the lcd for 20 chars 4 lines, turn on backlight
  lcd.setBacklight(15);
  lcd.clear();
  lcd.setCursor(3, 0);     // print the version screen
  lcd.print("WD9GYM RS-UV3");
  lcd.setCursor(0, 1);
  lcd.print("Repeater Controller");
  lcd.setCursor(0,2);
  lcd.print("10/14/2015  Rel 1.0");
  delay(3000);
 

/******************************************
 *  get the UV-RS3 Info
*******************************************/
#ifdef DEBUG
Serial.println("Setup code");
#endif

  memoryChannel[0] = '0';
  memoryChannel[1] = '\0';

 // read a bytes from the current address of the EEPROM
  buzzerEnabled = EEPROM.read(buzzerAddr);
  if (buzzerEnabled != true && buzzerEnabled != false) {
      buzzerEnabled = false;
      }
  currentDevice = EEPROM.read(deviceAddr);
  if (currentDevice != 0 && currentDevice != 1) {
      currentDevice = 0;
  }
  
  fanEnabled = EEPROM.read(fanAddr);
#ifdef DEBUG  
Serial.print("Startup fanEnabled = "); Serial.println(fanEnabled);
#endif
  if (fanEnabled == relayOn){
      digitalWrite(FANPIN, LOW);          // turn the relay on          
     } else {
            digitalWrite(FANPIN, HIGH);        // turn off the relay             
            }

  repeaterEnabled = EEPROM.read(repeaterAddr);
#ifdef DEBUG  
Serial.print("Startup repeaterEnabled = "); Serial.println(repeaterEnabled);
#endif
  if (fanEnabled == relayOn) {
      digitalWrite(REPEATERPIN, LOW);   // turn the relay on   
  } else {
          digitalWrite(REPEATERPIN, HIGH);  // turn the relay off
  }

  delay(1000);
  
  getConfiginfo();
  lcd.clear();  
  getFreq();
  printFreq();
   
  
   if (timeStatus()!= timeSet) {
#ifdef DEBUGTIME
    lcd.print("Unable to sync RTC");
    Serial.println("Unable to sync with the RTC");
    delay2k();
#endif
    } else {
#ifdef DEBUGTIME
    Serial.println("RTC has set the system time");
    lcd.print("RTC set the sys time");
    delay2k();
#endif
  }

  bool parse=false;
  bool config=false;

  // get the date and time the compiler was run
  if (getDate(__DATE__) && getTime(__TIME__)) {
    parse = true;
    // and configure the RTC with this info
    if (RTC.write(tm)) {
      config = true;
    }
  }

  if (parse && config) {
#ifdef DEBUG    
    Serial.print("DS1307 configured Time=");
    Serial.print(__TIME__);
    Serial.print(", Date=");
    Serial.println(__DATE__);
#endif
  } else if (parse) {
#ifdef DEBUG    
    Serial.println("DS1307 Communication Error :-{");
    Serial.println("Please check your circuitry");
#endif    
  } else {
#ifdef DEBUG    
    Serial.print("Could not parse info from the compiler, Time=\"");
    Serial.print(__TIME__);
    Serial.print("\", Date=\"");
    Serial.print(__DATE__);
    Serial.println("\"");
#endif    
  }



#ifdef DEBUG  
Serial.println("end of setup");  
#endif

}
/************************************  
 *       Loop
*************************************/
void loop(){
 if (RTC.read(tm)) {
  if (prevSecond != tm.Second) {        // if a new second display new time
      prevSecond = tm.Second; 
      digitalClockDisplay();
  }
 }
   key = keypad.getKey();      // see if a key has been pressed

/******************************  
 *   keypad check 
******************************/
  if (key){
    
    if (buzzerEnabled == true){
        beep();                    
        }
    if (key == '*') {               // Did user activate function menu
        mainMenu();               // process the menu request
        printFreq();
        }

    else if (key == 'A') {               // Did user change/refresh device A
        currentDevice = 0;
        EEPROM.write(deviceAddr, currentDevice);
Serial.print("currentDevice = "); Serial.println(currentDevice);Serial.print("repeaterEnabled = "); Serial.println(repeaterEnabled);        
        getConfiginfo();
        printFreq();
        }
    else if (key == 'B') {               // Did user change/refresh device
        currentDevice = 1;
        EEPROM.write(deviceAddr, currentDevice);
Serial.print("currentDevice = "); Serial.println(currentDevice);Serial.print("repeaterEnabled = "); Serial.println(repeaterEnabled);
        getConfiginfo();
        printFreq();
        }
  }

}
/******************************
 * get_UV3buff
 */
byte get_UV3buff(){
#ifdef DEBUG
Serial.println("get_VU3buff");
#endif
  byte k = 0;
  long T = millis() + 100;
  char c = 0;
 if (currentDevice == 0) {  
  while ((millis() < T) && (c != '\r')){
    if(Serial3.available()){
      c = Serial3.read();
      UV3buff[k++] = c;
      if (c == '\r') UV3buff[--k] = 0;
    }
  }
 } else {
  while ((millis() < T) && (c != '\r')){
    if(Serial2.available()){
      c = Serial2.read();
#ifdef DEBUGC      
Serial.println(c);
#endif
      UV3buff[k++] = c;
      if (c == '\r') UV3buff[--k] = 0;
    }
  }
 }
#ifdef DEBUG 
Serial.print("UV3buff = "); Serial.println(UV3buff);
#endif
  if (c == 13){
    return 1;
  }
  return 0;
}



/****************************************
 * Clock routine
****************************************/
void digitalClockDisplay() {
  // digital clock display of the time
#ifdef DEBUGTIME
  Serial.print(tm.Hour);
  printDigits(tm.Minute);
  printDigits(tm.Second);
  Serial.print(" ");
  Serial.print(tm.Day);
  Serial.print(" ");
  Serial.print(tm.Month);
  Serial.print(" ");
  Serial.print(tmYearToCalendar(tm.Year)); 
  Serial.println();
#endif 
  lcd.setCursor(0, 3);           // Time displayed on line 4
  if (tm.Hour < 10) {
     lcd.print("0");
  }
  lcd.print(tm.Hour);
  lcd.print(":");
  if (tm.Minute < 10) {
    lcd.print("0");
  }
  lcd.print(tm.Minute);
  lcd.print(":");
  if (tm.Second < 10) {
    lcd.print("0");
  }
  lcd.print(tm.Second);
  lcd.print("  ");
  if (tm.Month < 10) {
     lcd.print("0");
  }
  lcd.print(tm.Month);
  lcd.print("/");
  if (tm.Day < 10) {
     lcd.print("0");
  }
  lcd.print(tm.Day);
  lcd.print("/");
  lcd.print(tmYearToCalendar(tm.Year));
  
}


bool getTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

bool getDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}


