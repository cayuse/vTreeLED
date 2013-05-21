#include <EEPROM.h>
#include "Arduino.h"
#include "vTreeLEDControl.h"

/**
	
*/
vTreeLEDControl::vTreeLEDControl() {
}

void vTreeLEDControl::setup(){
    // Initialize this in the constructor of the class.
    vTreeLEDControl::myAddr = 0;
    vTreeLEDControl::myAddr = EEPROM.read(0);

    //May as well have it start fully on.
    vTreeLEDControl::redValue = 255;
    vTreeLEDControl::yellowValue = 255;
    vTreeLEDControl::greenValue = 255;
    vTreeLEDControl::blueValue = 255;
    // Intensity value may be used later to allow for scalaing back off the initial values without changing the
    // color of the light.  This will probably require some math or something.
    //But basically its intended that the math will always look at the RGB values and then calculate a level
    //shifted intensity downward from there. At 255 it would be those exact values.
    // This is intended for later with higher bit PWMing
    
    // Configure Pins
    // And write their initial state.
  pinMode(vTreeLEDControl::redPin,OUTPUT);
  analogWrite(vTreeLEDControl::redPin, 255 - vTreeLEDControl::redValue);
  
  pinMode(vTreeLEDControl::yellowPin,OUTPUT);
  analogWrite(vTreeLEDControl::yellowPin, 255 - vTreeLEDControl::yellowValue);
  
  pinMode(vTreeLEDControl::greenPin,OUTPUT);
  analogWrite(vTreeLEDControl::greenPin, 255 - vTreeLEDControl::greenValue);

  pinMode(vTreeLEDControl::bluePin,OUTPUT);
  analogWrite(vTreeLEDControl::bluePin, 255 - vTreeLEDControl::blueValue);

}

vTreeLEDControl::~vTreeLEDControl() {}

void vTreeLEDControl::setAddress(uint8_t address){
    vTreeLEDControl::myAddr = address;
    EEPROM.write(0,address);
}
void vTreeLEDControl::setRedValue(int value){
    vTreeLEDControl::redValue = value;
    analogWrite(vTreeLEDControl::redPin, 255 - value);
}

void vTreeLEDControl::setYellowValue(int value){
    vTreeLEDControl::yellowValue = value;
    analogWrite(vTreeLEDControl::yellowPin, 255 - value);
}

void vTreeLEDControl::setGreenValue(int value){
    vTreeLEDControl::greenValue = value;
    analogWrite(vTreeLEDControl::greenPin, 255 - value);
}

void vTreeLEDControl::setBlueValue(int value){
    vTreeLEDControl::blueValue = value;
    analogWrite(vTreeLEDControl::bluePin, 255 - value);
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