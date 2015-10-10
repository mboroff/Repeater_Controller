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
#include <SoftwareSerial.h>
#include <stdint.h>
#include <EEPROM.h>

#define BUZZER 13
#define FANPIN      12
#define REPEATERPIN 11

SoftwareSerial UV3A(9, 10); // RX, TX
SoftwareSerial UV3B(7, 8); // RX, TX
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
byte rowPins[ROWS] = {14, 15, 16, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

/***************************
 *  Global Variables
***************************/

int buzzerAddr = 0; /** the current address in the EEPROM (i.e. which byte we're going to write to next) **/
int deviceAddr = 1;
int freqSwitch = 0, CTCCSswitch = 0;
int fanAddr = 2;
unsigned int myHr,myMin,mySec,myDay,myMonth,myYr;
int inputCtr = 0, CTCCSctr = 1;
int menuSwitch = 0,  menuSelect = 1, currentDevice = 0;
int prevSecond = 99;
int radioCTCCSi;
int repeaterAddr = 2;
int returnCode;
int squelchValue;
int timeFldswitch = 0;
int timeCtr = 0;
int tmCtr = 0;
int volumeCtr = 0;

float radioCTCCSf;
  
char dataFld[32];
char inputFld[8];
char key;
char memoryChannel[2];
char radioCTCCS[6];
char radioTemp[4];
char recvFreq[8], xmitFreq[8], oldFreq[8];
char squelchLevel[2] = " ";
char temp[17];
char toneMode[2] = " ";
char UV3buff[32];
char UV3volume[3];

boolean repeaterSwitch = true, buzzerEnabled = true;
boolean fanEnabled = true, repeaterEnabled = true;
boolean SQ_OP = false;
/***************************************
        timers
***************************************/
unsigned long lastPolltime;
#define TIMETOPOLL  20000      // Amount of time to wait (in milliseconds) to read board


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

String str;  //declaring string
String squelchStr;
String radioCTCCSstr;
String volumeStr;
/***********************************
 *    Function menu titles
***********************************/
#define MAXFUNCTIONS 12
#define MAXITEMSIZE 20
char functionLabels[MAXFUNCTIONS][MAXITEMSIZE] = 
       { "Set Rx Freq        ", "Set Tx Freq        ", 
         "Set Sqlch Level    ", "Tone Sqlch Mode    ", 
         "Set CTCSS          ", "Repeater ON/OFF    ", 
         "BEEP ON/OFF        ", "Fan ON/OFF         ",
         "Set Clock          ", "Set Volume         ",        
         "Display System Info", "Reset RS-UV3       "
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
       
/****************************************************
 *                  Setup
*****************************************************/
void setup(){
     pinMode(BUZZER, OUTPUT);
     pinMode(FANPIN, OUTPUT);
     pinMode(REPEATERPIN, OUTPUT);

 // read a bytes from the current address of the EEPROM
  buzzerEnabled = EEPROM.read(buzzerAddr);
  currentDevice = EEPROM.read(deviceAddr);
  fanEnabled = EEPROM.read(fanAddr);
  if (fanEnabled == true) {
      digitalWrite(FANPIN, LOW);
      } else {
              digitalWrite(FANPIN, HIGH);
      }
  repeaterEnabled = EEPROM.read(repeaterAddr);  
  if (repeaterEnabled == true) {
      digitalWrite(REPEATERPIN, LOW);
      delay(1000);
      } else {
              digitalWrite(REPEATERPIN, HIGH);
      }

  

/*******************************
 *         Serial start
********************************/
  Serial.begin(19200);
  UV3A.begin(19200);      // UV3 unit one
  UV3B.begin(19200);      // UV3 unit two
 // while (!Serial);  // Wait for Arduino Serial Monitor to open
  delay(500);      // Wait for Arduino Serial Monitor to open
 

  
/*******************************
 *        LCD Start
*******************************/
  lcd.begin(20,4);         // initialize the lcd for 20 chars 4 lines, turn on backlight
  lcd.setBacklight(15);
  lcd.clear();
  // set the Time library to use Teensy 3.0's RTC to keep time
  setSyncProvider(getTeensy3Time);
     lcd.setCursor(0, 0);

   if (timeStatus()!= timeSet) {
#ifdef DEBUGTIME
    lcd.print("Unable to sync RTC");
    Serial.println("Unable to sync with the RTC");
    delay(2000);
#endif
    } else {
#ifdef DEBUGTIME
    Serial.println("RTC has set the system time");
    lcd.print("RTC set the sys time");
    delay(2000);
#endif
  }
  lcd.clear();

  lcd.setCursor(3, 0);
  lcd.print("WD9GYM RS-UV3");
  lcd.setCursor(0, 1);
  lcd.print("Repeater Controller");
  lcd.setCursor(0,2);
  lcd.print("10/09/2015  Rel 1.0");
  delay(3000);
  lcd.clear();

/******************************************
 *  get the UV-RS3 Info
*******************************************/
#ifdef DEBUG
Serial.println("Setup code");
#endif

  memoryChannel[0] = '0';
  memoryChannel[1] = '\0';
/*
  UV3A.write('\r');
  UV3A.print("RC");
  UV3A.write(memoryChannel);
  UV3A.write('\r');
  UV3B.write('\r');
  UV3B.print("RC");
  UV3B.write(memoryChannel);
  UV3B.write('\r');
//  memoryChannel[0] = '1';
*/
  getConfiginfo();
  printFreq();
#ifdef DEBUG  
Serial.println("end of setup");  
#endif
  lastPolltime = millis();
}

/************************************  
 *       Loop
*************************************/
void loop() {
  if (Serial.available()) {
    time_t t = processSyncMessage();
    if (t != 0) {
      Teensy3Clock.set(t); // set the RTC
      setTime(t);
    }
  }
  if (prevSecond !=second()) {
      prevSecond =second(); 
      digitalClockDisplay();
  }
   key = keypad.getKey();      // see if a key has been pressed

/******************************  
 *   keypad check 
******************************/
  if (key){
    
    if (buzzerEnabled == true){
        beep();                    
        }
    if (key == '*') {               // Did user activate menu
        mainMenu();               // process the menu request
        printFreq();
        }

    else if (key == 'A') {               // Did user change device
        currentDevice = 0;
        EEPROM.write(deviceAddr, currentDevice);
        getConfiginfo();
        printFreq();
        }
    else if (key == 'B') {               // Did user change device
        currentDevice = 1;
        EEPROM.write(deviceAddr, currentDevice);
        getConfiginfo();
        printFreq();
        }
  }


}

void digitalClockDisplay() {
  // digital clock display of the time
#ifdef DEBUGTIME
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println();
#endif 
  lcd.setCursor(0, 3);           // Time displayed on line 4
  if (hour() < 10) {
     lcd.print("0");
  }
  lcd.print(hour());
  lcd.print(":");
  if (minute() < 10) {
    lcd.print("0");
  }
  lcd.print(minute());
  lcd.print(":");
  if (second() < 10) {
    lcd.print("0");
  }
  lcd.print(second());
  lcd.print("  ");
  if (month() < 10) {
     lcd.print("0");
  }
  lcd.print(month());
  lcd.print("/");
  if (day() < 10) {
     lcd.print("0");
  }
  lcd.print(day());
  lcd.print("/");
  lcd.print(year());
  
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

/*  code to process time sync messages from the serial port   */
#define TIME_HEADER  "T"   // Header tag for serial time sync message

unsigned long processSyncMessage() {
  unsigned long pctime = 0L;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013 

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     return pctime;
     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
       pctime = 0L; // return 0 to indicate that the time is not valid
     }
  }
  Serial.print("pctime = "); Serial.println(pctime);
  return pctime;
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

