#ifndef vTreeLEDCTRL_H
#define vTreeLEDCTRL_H

class vTreeLEDControl
{
public:

    static const int redPin = 12;
    static const int greenPin = 15;
    static const int bluePin = 14;

    // We will eventually need a pin for reading the IR.
//    static const int IRPin = 2;

    int redValue;
    int greenValue;
    int blueValue;
    int intensityValue;


public:
    vTreeLEDControl();
    ~vTreeLEDControl();
//not sure if we need a loop, but i'll leave this for now
    void Loop(); // Call periodically, about once a second


void setRedValue(int value);
void setGreenValue(int value);
void setBlueValue(int value);
};

#endif
