
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

// Check and initialize if necessary the eeProm since we don't know what was there.
// Since we don't know what is in the eeprom, we just want to make sure that we aren't.
// required to use the broadcast address to talk to the thing, so we set it to 255 if its 0.

    int address = EEPROM.read(0);
    if (address == 0) {
        address = 255;
        EEPROM.write(0,address);
    }

    Serial.begin(9600);
    //Uart.begin(9600);

    Serial.setTimeout(1000);
    cmdProc.setSerial(Serial);
    
	pinMode(statusLed,OUTPUT);
	uint8_t u_addr = EEPROM.read(0);
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



