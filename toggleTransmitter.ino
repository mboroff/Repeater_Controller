/**************************
 * toggleTransmitter
*************************/

void toggleTransmitter()
{

#ifdef DEBUG
  Serial.println(functionLabels[menuSelect-1]);
#endif
  lcd.clear();                               // clear the diaplay
  lcd.setCursor(0, 0);
  lcd.print(functionLabels[menuSelect-1]);           // print the function title
  printTransmitterstate();
  lcd.setCursor(0, 3);
  lcd.print(txtAorB);

  menuSwitch = 0;                            // esure the loop runs

  while (menuSwitch == 0){             // loop until the * or # are pressed

      key = keypad.getKey();               // see if a key has been pressed
      if (key) {
          if (buzzerEnabled == true){        // check if buzzer should buzz
              beep();                    
              }
          if (key == txtHashTag) {               // cancel key
              lcd.clear();
              menuSwitch = 1;                      // kill the loop
              break;
              }
          else if (key == txtStar) {            // confirmation key
                  sendtxState();               // send the tx state
                  lcd.clear();
                  menuSwitch = 1;                // kill the loop
                  break;
                  }
          else if (key == txtA ) {              // increment xmitter off timer value
                   txStatectr++;
                   if (txStatectr >5) {
                       txStatectr = 0;
                   }
                   printTransmitterstate();
                }
          else if (key == txtB) {              // decrement xmitter time out time value
                  txStatectr--;
                  if (txStatectr < 0) {
                      txStatectr = 5;
                  }
                  printTransmitterstate();
                }
      }
  }
  
}

/*******************************************
 * Print tranmitter state
********************************************/

void printTransmitterstate()
{
#ifdef DEBUG
Serial.print(F("txState = ")); Serial.println(txState);  
#endif
   lcd.setCursor(0,2);                       // position the cursor
   lcd.print(F("xmitterState = "));
   lcd.print(txStatectr);
}
/***********************************
 *   settxState
***********************************/
void sendtxState()
{
#ifdef DEBUG
  Serial.println(F("sendtxState"));
#endif  
   
   sprintf(txState, "%0i", txStatectr);      // format xmitter state before sending to uv3
   txState[1] = txtNull;
   sendStorecmd("TX", txState);

   lcd.setCursor(0, 3);
   lcd.print(F("xmitter state saved "));
   delay2k();
}



