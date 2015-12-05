/*********************************************************************
 * UV-RS3 Repeater Controller
 * We invest time and resources providing this open source code, 
  please support them and open-source hardware by purchasing 
  products from HobbyPCB!

  Written by Martin Boroff WD9GYM.  
  BSD license, all text above must be included in any redistribution

  Frequency display function taken from VFO project in
  Arduino Projects for Amateur Radio, McGraw-Hill Publishing 
  by Jack Purdum & Dennis Kidder. 


 Menu Functions
      1) - Set Rx Freq
      2) - Set Tx Freq
      3) - Set Sqlch Level
      4)  -Tone Sqlch Mode
      5) - Set CTCSS
      6) - Repeater ON/OFF
      7) - BEEP ON/OFF
      8) - Fan ON/OFF
      9) - Set Clock
     10) - Set Volume
     11) - Display System Info
     12) - Reset RS-UV3
     13) - Set Call Sign
     14) - Transmit Call Sign      
     V2 additions
     15) - Set Hang Time
     16) - Set ID Timer
     17) - Display temp history
     Store the temp each hour
     18) RESET EEPROM
     
 
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
#include <stdint.h>
#include <EEPROM.h>
#include <DS3231.h>
#define BUZZER 12.

#define FANPIN      11
#define REPEATERPIN 10
#define relayOn 0
#define relayOff 1
/***********************************
 * Time 
************************************/
DS3231  rtc(SDA, SCL);

Time t; // structure for time

int daysInmonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


char   janStr[]  = "Jan";
char   febStr[]  = "Feb";
char   marStr[]  = "Mar";
char   aprStr[]  = "Apr";
char   mayStr[]  = "May";
char   junStr[]  = "Jun";
char   julStr[]  = "Jul";
char   augStr[]  = "Aug";
char   sepStr[]  = "Sep";
char   octStr[]  = "Oct";
char   novStr[]  = "Nov";
char   decStr[]  = "Dec"; 

char*  monthStrs[] = { janStr, febStr, marStr, aprStr, mayStr, junStr,
                                          julStr, augStr, sepStr, octStr, novStr, decStr}; 


int utcOffset = 1;
int localOffset = 1; 
int myMonth = 0, myMonthDay = 0, myYear = 0;     // used for setDate
int myHour = 0, myMinute = 0, mySecond = 0;      // used for setTime
int prevSecond = 0, prevHour = 0;
int localHour;

char wrkMonth[4] = "   ";                        // temp work values
char wrkMonthday[3] = "  ";
char wrkYear[5] = "    ";
char wrkHour[3] = " ";
char wrkMinute[3] = "  ";
char wrkSecond[3] = "  ";
int workMonth, workDay, workYear, workHour;


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
  {'*', '0','#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

/***************************
 *  Global Variables
***************************/
    
int bufferIndex = 0;
int buzzerAddr = 0; /** the current address in the EEPROM (i.e. which byte we're going to write to next) **/
int deviceAddr = 1;  // last device user used A or B
int fanAddr = 2;     // switch for fan relay status
int repeaterAddr = 3;  // switch for repeater relay status
int utcoffsetAddr = 4; 
int localoffsetAddr = 5;  // local time offset
int temperaturesaveAddr = 6; // reserving 48 memory slots for temp - 24 A then 24 B
int txstateAddr = 55;   // transmitter state
int nextAvalableaddress = 57;

int displayHour;
int freqSwitch = 0, CTCCSswitch = 0;
int keyIndex = 0;
int keySwitch = 0;
int inputCtr = 0, CTCCSctr = 1, idTimer = 0, hangTimer = 0;
int menuSwitch = 0,  menuSelect = 1, currentDevice = 0;
int radioCTCCSi;
int fanEnabled = relayOn, repeaterEnabled = relayOn;
int returnCode;
int prevtimeOutctr = 0;
int squelchValue;
int timeFldswitch = 0;
int timeCtr = 0;
int tmCtr = 0;
int timeOut = 0;
int timeOutctr = 0;
int txStatectr = 0;
int volumeCtr = 0;
int workTemperature;

float radioCTCCSf;
  
char callSignbuffer[21];
char currentKey[2];
char dataFld[32];
char dtfmState[4];
char dtfmSwitch[2];
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
char tempIDtimer[4];
char tempHangtimer[5];
char timeOuttime[4] = "000";
char toneMode[5];
char txState[2] = "0";
char UV3buff[32];
char UV3volume[3];

boolean keyEntered = false;
boolean repeaterSwitch = true, buzzerEnabled = true;
boolean tempSave = true;
boolean SQ_OP = false;

#define TWOMUPPERFREQUENCYLIMIT      147999L  // Upper band edge
#define TWOMLOWERFREQUENCYLIMIT      144000L  // Lower band edge
#define TWOTWENTYUPPERFREQUENCYLIMIT 224999L  // Upper band edge
#define TWOTWENTYLOWERFREQUENCYLIMIT 222000L  // Lower band edge
#define FOURFORTYUPPERFREQUENCYLIMIT 449999L  // Upper band edge
#define FOURFORTYLOWERFREQUENCYLIMIT 420000L  // Lower band edge
#define FREQINBAND        0               // Used with range checking
#define FREQOUTOFBAND     1

volatile int_fast32_t currentFrequency;

byte ones, tens, hundreds, thousands, tenthousands, hundredthousands, millions; // Placeholders

String str;  
String squelchStr;
String radioCTCCSstr;
String volumeStr;

/**********************************
 *    Constant chars
**********************************/
const char txtProgName[14] = "WD9GYM RS-UV3";
const char txtHexZero = '0';
const char txtNull = '\0';
const char txtStar = '*';
const char txtA = 'A';
const char txtB = 'B';
const char txtC = 'C';
const char txtD = 'D';
const char txtHashTag = '#';
const char txtSpace20[21] = "                    ";
const char txtColon[2] = ":";
const char txtZero[2] = "0";
const char txtZeroZero[3] = "00";
const char txtOne[2] = "1";
const char txtTwo[2] = "2";
const char txtSlash[2] = "/";
const char txtAorB[13] = "Press A or B";
const char txtAorBorC[19] = "Press A or B or C";
const char txtPressAtoToggle[18] = "Press A to toggle";
const char txtOn[4] = "ON ";
const char txtOff[4] = "OFF";
const char txtSpaceEqualSpace[4] = " = ";
const char txtCspace[3] = "C ";
const char txtRxColonSpace[5] = "RX: ";
const char txtTxColonSpace[5] = "TX: ";
const char txtSpaceOne[2] = " ";
const char txtSpaceTwo[3] = "  ";
const char txtSpaceThree[4] = "   ";
const char txtSpaceTen[11] = "          ";
const char txtFunction[9] = "Function";
const char txtZerDashTwo[12] = "Enter 0 - 2";


/***********************************
 *    Function menu titles
***********************************/
#define MAXFUNCTIONS 21
#define MAXITEMSIZE 20
char functionLabels[MAXFUNCTIONS][MAXITEMSIZE] = 
       { "Set Rx Freq        ", "Set Tx Freq        ", 
         "Set Sqlch Level    ", "Tone Sqlch Mode    ", 
         "Set CTCSS          ", "Repeater ON/OFF    ", 
         "BEEP ON/OFF        ", "Fan ON/OFF         ",
         "Set Clock          ", "Set Volume         ",        
         "Display System Info", "Reset RS-UV3       ",
         "Set Call Sign      ", "Transmit Call Sign ",
         "Set Hang Timer     ", "Set ID Timer       ",
         "Display temp Hist  ", "Erease Arduino Mem ",
         "Set Time Out Timer ", "Toggle Transmitter ",
         "Toggle DTFM Detect "
         };
/***********************************
 *      Tones Table
***********************************/
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

/**********************************
 * LCD start
***********************************/
  lcd.begin(20,4);         // initialize the lcd for 20 chars 4 lines, turn on backlight
  lcd.setBacklight(15);
  lcd.clear();
  lcd.setCursor(3, 0);     // print the version screen
  lcd.print(txtProgName);  // print WD9GYM RS-UV3
  lcd.setCursor(0, 1);
  lcd.print("Repeater Controller");
  lcd.setCursor(0,2);
  lcd.print(F("12/04/2015  Rel 2.0"));
  delay(3000);
 

/******************************************
 *  get the UV-RS3 Info
*******************************************/
#ifdef DEBUG
Serial.println(F("Setup code"));
#endif

  memoryChannel[0] = txtZero[0];           // txtZero Use memory channel zero for storing values
  memoryChannel[1] = txtNull;

 // read a bytes from the current address of the EEPROM for buzzer fan and repeater
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
Serial.print(F("Startup fanEnabled = ")); Serial.println(fanEnabled);
#endif
  if (fanEnabled == relayOn){
      digitalWrite(FANPIN, LOW);          // turn the relay on          
     } else {
            digitalWrite(FANPIN, HIGH);        // turn off the relay             
            }

  repeaterEnabled = EEPROM.read(repeaterAddr);
#ifdef DEBUG  
Serial.print(F("Startup repeaterEnabled = ")); Serial.println(repeaterEnabled);
#endif
  if (repeaterEnabled == relayOn) {
      digitalWrite(REPEATERPIN, LOW);   // turn the relay on   
  } else {
          digitalWrite(REPEATERPIN, HIGH);  // turn the relay off
  }

   txState[0] = EEPROM.read(txstateAddr);   // read the state of the transmitter
   txState[1] = '\0';
   txStatectr = atoi(txState);

  delay(500);
 lcd.clear();     // clear the LCD
 
  getConfiginfo();   // get infor from the rs-uv3
  getFreq();
  printFreq();

  
/*************************
 *   start the clock
 ***********************/
  rtc.begin();  
  t = rtc.getTime();                // get the time  
#ifdef DEBUG
   Serial.println(rtc.getDateStr(FORMAT_SHORT, FORMAT_MIDDLEENDIAN, '/'));
#endif   
  // that are connected to the SPI bus do not hold drive bus
  // The following lines can be uncommented to set the date and time
//  rtc.setDOW(TUESDAY);     // Set Day-of-Week to SUNDAY
//  rtc.setTime(23, 29, 0);     // Set the time to 12:00:00 (24hr format)
//  rtc.setDate(20, 10, 2015);   // Set the date to January 1st, 2014
  
 utcOffset = EEPROM.read(utcoffsetAddr);
 localOffset = EEPROM.read(localoffsetAddr);

#ifdef DEBUG  
Serial.println(F("end of setup"));  
#endif

}


/************************************  
 *       Loop
*************************************/
void loop(){
  
 t = rtc.getTime();                // get the time
  myMonth = t.mon;
  myMonthDay = t.date;
  myYear = t.year;
  myHour = t.hour;
  myMinute = t.min;
  mySecond = t.sec;                 // get the second

  if (prevSecond != mySecond) {      // check for a new second
      prevSecond = mySecond;
      DisplayDateAndTime();
      if (prevHour != myHour && tempSave == true) {    // check for a new hour
          tempSave = false;
          prevHour = myHour;
          saveThetemp();
          }
       if (prevHour == myHour && tempSave == false) {
          tempSave = true;   
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
    if (key == txtStar) {               // Did user activate function menu
        mainMenu();               // process the menu request
        lcd.clear();              // on return clear the lcd and get info fro rs-uv3
        getConfiginfo();
        getFreq();
        printFreq();
        }

    else if (key == txtA) {               // Did user change/refresh device A
        currentDevice = 0;
        EEPROM.write(deviceAddr, currentDevice);
#ifdef DEBUG
Serial.print(F("currentDevice = ")); Serial.println(currentDevice);Serial.print(F("repeaterEnabled = ")); 
Serial.println(repeaterEnabled);        
#endif        
        getConfiginfo();
        getFreq();
        printFreq();
        }
    else if (key == txtB) {               // Did user change/refresh device
        currentDevice = 1;
        EEPROM.write(deviceAddr, currentDevice);
#ifdef DEBUG
Serial.print(F("currentDevice = ")); Serial.println(currentDevice);Serial.print(F("repeaterEnabled = ")); 
Serial.println(repeaterEnabled);
#endif
        getConfiginfo();
        getFreq();
        printFreq();
        }
  }

}

/***********************************
 *     saveThetemp
***********************************/

void saveThetemp()
{
#ifdef DEBUG
   Serial.println(F("save temp"));    
#endif
   lcd.setCursor(0, 3);
   lcd.print(F("Saving temperature"));
   int tempDevice;
   tempDevice = currentDevice;     // save the current device because we need to get from both devices
   currentDevice = 0;
   getradioTemp();                    // get the temp from device 0
   workTemperature = atoi(radioTemp);

#ifdef DEBUG
   Serial.print(F("workTemperature = ")); Serial.println(workTemperature);
   Serial.print(F("radioTemp = ")); Serial.println(radioTemp);
   Serial.print(F("localHour = ")); Serial.println(localHour); 
   Serial.print(F("temperaturesaveAddr = ")); Serial.println(temperaturesaveAddr);
   Serial.print(F("temperaturesaveAddr + localHour = ")); Serial.println(temperaturesaveAddr + localHour);
#endif
   EEPROM.write(temperaturesaveAddr  + localHour, workTemperature);
   currentDevice = 1;                          // get the temp from device 1
   getradioTemp();
   workTemperature = atoi(radioTemp);
#ifdef DEBUG
   Serial.print(F("workTemperature = ")); Serial.println(workTemperature);
   Serial.print(F("radioTemp = ")); Serial.println(radioTemp);
   Serial.print(F("localHour = ")); Serial.println(localHour); 
   Serial.print(F("temperaturesaveAddr = ")); Serial.println(temperaturesaveAddr);
   Serial.print(F("temperaturesaveAddr + 24 + localHour = ")); Serial.println(temperaturesaveAddr + 24 + localHour);
#endif
   EEPROM.write(temperaturesaveAddr + 24 + localHour, workTemperature);
   currentDevice = tempDevice;           // restore the current device number
   delay(2000);
   lcd.setCursor(0, 3);
   lcd.print(txtSpace20);    // blank line   
}

