
#include <Stream.h>
#include <stdio.h>
#include "vTreeLEDCmdProcessor.h"
#include "vTreeLEDControl.h"
#include <EEPROM.h>

vTreeLEDControl pctrl = vTreeLEDControl();
vTreeLEDCmdProcessor cmdProc = vTreeLEDCmdProcessor(&pctrl);

int statusLed = 11;
int errorLed = 11;
int loopCtr = 0;

uint8_t u_addr = 0;


// Timeout handling
long oneSecondInterval = 1000;
long oneSecondCounter = 0;
int ledCounter = 0;

int counter = 0;

void flashLed(int pin, int times, int wait) {

  for (int i = 0; i < times; i++) {
    digitalWrite(pin, HIGH);
    delay(wait);
    digitalWrite(pin, LOW);

    if (i + 1 < times) {
      delay(wait);
    }
  }
}

// ------------------ S E T U P ----------------------------------------------

void setup() {

// Check and initialize if necessary the eeProm since we don't know what was there.
// Since we don't know what is in the eeprom, we just want to make sure that we aren't.
// required to use the broadcast address to talk to the thing, so we set it to 255 if its 0.

    u_addr = EEPROM.read(0);
    if (u_addr == 0) {
        u_addr = 255;
        EEPROM.write(0,u_addr);
    }

// Serial1 is the uart that talks to the xBee we could talk directly
// to the program by just using Serial for debug purposes so we don't have to
// hook up two teensy modules

    Serial.begin(9600);

    //Serial.setTimeout(1000);
    //cmdProc.setSerial(Serial);
    cmdProc.setSerial(Serial);
    
	pinMode(statusLed,OUTPUT);
}

void toggleLed()
{
  // blink
  if (ledCounter % 2) {
    digitalWrite(statusLed, HIGH);
  } else {
    digitalWrite(statusLed, LOW);
  }
  ledCounter++;
}  


// ------------------ M A I N ( ) --------------------------------------------

void loop()
{
    char buffer[128];

    cmdProc.Loop();

    delay(1);

    loopCtr++;

}



