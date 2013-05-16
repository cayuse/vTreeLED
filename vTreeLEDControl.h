#ifndef vTreeLEDCTRL_H
#define vTreeLEDCTRL_H

class vTreeLEDControl
{
public:

    static const int vTreeLEDPin = 2;
    // Need to swap these pins
    // The north and south are backwards
    static const int northPin = 4;
    static const int southPin = 3;

    // Analog inputs.
    static const int ditchPin = 2;
    static const int sumpPin = 5;

    // Set the vTreeLED call on when we want the vTreeLED to go..
    // we might turn it off if the levels are too low.
    bool vTreeLEDCall;

    // Set these to true when we want the valve on. The actual state of
    // the valve will be off unless the vTreeLED is on..
    bool northCall;
    bool southCall;

    int ditchCurr;
    long ditchSum;
    int ditchCount;

    int sumpCurr;
    long sumpSum;
    int sumpCount;

    // Trigger levels.. to turn off the vTreeLED if the levels are reached
    int sumpLowTrigger;
    bool enableSumpTrigger;


public:
    vTreeLEDControl();
    ~vTreeLEDControl();

    void Loop(); // Call periodically, about once a second

    bool isvTreeLEDOn();
    bool isNorthOn();
    bool isSouthOn();
    void setvTreeLED(bool bOn);
    void setNorthCall(bool bOn);
    void setNorthValve(bool bOn);
    void setSouthCall(bool bOn);
    void setSouthValve(bool bOn);
    void setSumpTrigger(int trig);
    void setSumpTriggerEnable(bool bOn);
    void levelChecks();
    void updateValves();
    void readSensors();

};

#endif
