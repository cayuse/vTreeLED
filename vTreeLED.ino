
#include <Stream.h>
#include <stdio.h>
#include "vTreeLEDCmdProcessor.h"
#include <EEPROM.h>

vTreeLEDControl pctrl = vTreeLEDControl();
vTreeLEDCmdProcessor cmdProc = vTreeLEDCmdProcessor(&pctrl);

int statusLed = 11;
int errorLed = 11;
int loopCtr = 0;


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

// Serial1 is the uart that talks to the xBee we could talk directly
// to the program by just using Serial for debug purposes so we don't have to
// hook up two teensy modules

    Serial.begin(38400);

    //Serial.setTimeout(1000);
    //cmdProc.setSerial(Serial);
    cmdProc.setSerial(Serial);
    
	pinMode(statusLed,OUTPUT);
	pctrl.setup();
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



