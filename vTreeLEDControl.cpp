#include <EEPROM.h>
#include "Arduino.h"
#include "vTreeLEDControl.h"

/**
	
*/
vTreeLEDControl::vTreeLEDControl() {

    // Initialize this in the constructor of the class.
    vTreeLEDControl::myAddr = 0;
    vTreeLEDControl::myAddr = EEPROM.read(0);

    //May as well have it start fully on.
    vTreeLEDControl::redValue = 255;
    vTreeLEDControl::greenValue = 255;
    vTreeLEDControl::blueValue = 255;
    // Intensity value may be used later to allow for scalaing back off the initial values without changing the
    // color of the light.  This will probably require some math or something.
    //But basically its intended that the math will always look at the RGB values and then calculate a level
    //shifted intensity downward from there. At 255 it would be those exact values.
    // This is intended for later with higher bit PWMing
    intensityValue = 255;
    
    // Configure Pins
    // And write their initial state.
  pinMode(vTreeLEDControl::redPin,OUTPUT);
  analogWrite(vTreeLEDControl::redPin, vTreeLEDControl::redValue);

  pinMode(vTreeLEDControl::greenPin,OUTPUT);
  analogWrite(vTreeLEDControl::greenPin, vTreeLEDControl::greenValue);

  pinMode(vTreeLEDControl::bluePin,OUTPUT);
  analogWrite(vTreeLEDControl::bluePin, vTreeLEDControl::blueValue);

}

vTreeLEDControl::~vTreeLEDControl() {}

void vTreeLEDControl::setAddress(uint8_t address){
    vTreeLEDControl::myAddr = address;
    EEPROM.write(0,address);
}
void vTreeLEDControl::setRedValue(int value){
    //int redValue = -1;
    vTreeLEDControl::redValue = value;
    analogWrite(vTreeLEDControl::redPin, value);
}

void vTreeLEDControl::setGreenValue(int value){
    //int greenValue = -1;
    vTreeLEDControl::greenValue = value;
    analogWrite(vTreeLEDControl::greenPin, value);
}

void vTreeLEDControl::setBlueValue(int value){
    //int blueValue = -1;
    vTreeLEDControl::blueValue = value;
    analogWrite(vTreeLEDControl::bluePin, value);
}

bool vTreeLEDControl::IsMyAddress(uint8_t address) {
    return(address == vTreeLEDControl::myAddr);
}
bool vTreeLEDControl::IsBcastAddress(uint8_t address){
    return(address == 0);
}
bool vTreeLEDControl::IsMyOrBcast(uint8_t address){
    return(IsMyAddress(address) || IsBcastAddress(address));
}