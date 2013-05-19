#ifndef vTreeLEDCTRL_H
#define vTreeLEDCTRL_H

#include "CmdProcessor.h"

class vTreeLEDControl
{
public:

    static const int redPin = 12;
    static const int greenPin = 15;
    static const int bluePin = 14;

    uint8_t  myAddr;

    // We will eventually need a pin for reading the IR.
//    static const int IRPin = 2;

    int redValue;
    int greenValue;
    int blueValue;
    int intensityValue;



public:
    vTreeLEDControl();
    ~vTreeLEDControl();
//we will want to loop, and we'll have modes of operation here are the ones i'm pondering now
// this list is by no means complete or well thought out, just some ideas
// mode 0:  loop is not called at all.. only the command interpreter this is 'fully host driven mode'
// mode 1:  light is acting as a host, its doing (something) but also broadcasting to its friends
//          at least some kind of sync pulse or maybe its aware of relative locations and is telling them when/what
//          to update
// mode 3:  light is on, light is set to some color, not much else happening
// mode 4:  light is doing some pre-programmed shifting
// mode 5:  same as above with synchronisation inputs
// mode 6:  light is doing some algorithmic shifting
// mode 7:  same as above with synchronization inputs
	void setup();
    void Loop(); // Call periodically, about once a second

    void setAddress(uint8_t address);
    void setRedValue(int value);
    void setGreenValue(int value);
    void setBlueValue(int value);

    bool IsMyAddress(uint8_t address);
    bool IsBcastAddress(uint8_t address);
    bool IsMyOrBcast(uint8_t address);
};

#endif
