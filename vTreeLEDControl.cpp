#include <EEPROM.h>
#include "Arduino.h"
#include "vTreeLEDControl.h"
#include "T1PWM.h"

#define PWM_PERIOD   0x3FFF
#define PWM_SHIFT    2

vTreeLEDControl::vTreeLEDControl() {
}

void vTreeLEDControl::setup() {
    // Initialize this in the constructor of the class.

    myAddress = 0;
//  myAddress = EEPROM.read(0);

    // Start with everything off

    brightness = 0xFF;
    red = 0;
    green = 0;
    blue = 0;

    // Initialize timer for high resolution fast PWM mode
    // Configure PWM period

    T1PWMInit();    
    SetPWM1Period(PWM_PERIOD);

    SetPWM1A(red);
    SetPWM1B(green);
    SetPWM1C(blue);
}

vTreeLEDControl::~vTreeLEDControl() {}

void vTreeLEDControl::setAddress(uint8_t address){
    myAddress = address;
    EEPROM.write(0, address);
}

void vTreeLEDControl::setRed(uint8_t intensity){
    uint16_t width;

    red = intensity;
    width = (intensity * brightness) >> PWM_SHIFT;
    SetPWM1A(width);
}

void vTreeLEDControl::setGreen(uint8_t intensity){
    uint16_t width;

    green = intensity;
    width = (intensity * brightness) >> PWM_SHIFT;
    SetPWM1B(width);
}

void vTreeLEDControl::setBlue(uint8_t intensity){
    uint16_t width;

    blue = intensity;
    width = (intensity * brightness) >> PWM_SHIFT;
    SetPWM1A(width);
}

void vTreeLEDControl::setBrightness(uint8_t bright)
{
    brightness = bright;
    setRed(red);
    setGreen(green);
    setBlue(blue);
}

bool vTreeLEDControl::IsMyAddress(uint8_t address) {
    return(address == myAddress);
}

bool vTreeLEDControl::IsBcastAddress(uint8_t address){
    return(address == 0);
}

bool vTreeLEDControl::IsMyOrBcast(uint8_t address){
    return(IsMyAddress(address) || IsBcastAddress(address));
}