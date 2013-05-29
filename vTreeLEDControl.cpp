#include <EEPROM.h>
#include "Arduino.h"
#include "vTreeLEDControl.h"
#include "T1PWM.h"


#define BROADCAST_ID 0x00
//ID_STORE is a EEProm memory locaton
#define ID_STORE     0x00
#define INIT_ID      0xFF
#define PWM_PERIOD   0x3FFF
#define PWM_SHIFT    2

vTreeLEDControl::vTreeLEDControl() {

    // Check and initialize if necessary the eeProm since we don't know what was there.
    // Since we don't know what is in the eeprom, we just want to make sure...
    // its not BROADCAST_ID if so we set it to INIT_ID
    //Initialize Unit ID
    unitID = 0;
    unitID = EEPROM.read(ID_STORE);
    if (unitID == BROADCAST_ID) {
        unitID = INIT_ID;
        EEPROM.write(ID_STORE,unitID);
    }
    //Initialize Group ID
    groupID = unitID;
}

void vTreeLEDControl::setup() {

    // Start with everything on (half)
    // Why the hell would you plug in a light and not expect it to come on?

    brightness = 0xFF;
    red = 0x80;
    green = 0x80;
    blue = 0x80;

    // Initialize timer for high resolution fast PWM mode
    // Configure PWM period

    T1PWMInit();    
    SetPWM1Period(PWM_PERIOD);

    SetPWM1A(red);
    SetPWM1B(green);
    SetPWM1C(blue);
}

vTreeLEDControl::~vTreeLEDControl() {}

void vTreeLEDControl::setUnitID(uint8_t id){
    unitID = id;
    EEPROM.write(0, id);
}

void vTreeLEDControl::setGroupID(uint8_t id){
    groupID = groupID;
}

void vTreeLEDControl::resetGroupID(void) {
    groupID = unitID;
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
    SetPWM1C(width);
}

void vTreeLEDControl::setBrightness(uint8_t bright)
{
    brightness = bright;
    setRed(red);
    setGreen(green);
    setBlue(blue);
}

bool vTreeLEDControl::isUnit(uint8_t id) {
    return(id == unitID);
}

bool vTreeLEDControl::isGroup(uint8_t id){
    return(groupID == id);
}

bool vTreeLEDControl::isBcast(uint8_t id){
    return(id == BROADCAST_ID);
}

bool vTreeLEDControl::isUnitOrBcast(uint8_t id){
    return(isUnit(id) || isBcast(id));
}

bool vTreeLEDControl::isAny(uint8_t id){
    return(isBcast(id) || isGroup(id) || isUnit(id));
}
