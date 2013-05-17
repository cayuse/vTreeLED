
#include <string.h>
#include "vTreeLEDCmdProcessor.h"
#include "vTreeLEDControl.h"

static char buffer[1024];

vTreeLEDCmdProcessor::vTreeLEDCmdProcessor(vTreeLEDControl* pc) : CmdProcessor()
{
    _pPC = pc;

}

vTreeLEDCmdProcessor::~vTreeLEDCmdProcessor()
{
}


void vTreeLEDCmdProcessor::Loop()
{
    // Process commands from the command interface.
    //if (false) {
    if (checkCommands()) {
        // Process the command

        const char *pCmd = getCmd();

            // What is the best way? An enum would work, but hard to
            // manage. A string is easy, but inefficient... but easy.
//This command responds always and with the following information. It should also include address.
//But i have to go so I can't do that right atm.
            if (strcmp(pCmd,"status") == 0) {
                  sprintf(buffer,"Ok:Red:%d Green:%d Blue:%d Intensity:%d\n",
                    _pPC->redValue,
                    _pPC->greenValue,
                    _pPC->blueValue,
                    _pPC->intensityValue
                    );
                _pHW->print(buffer);

// This command sets RGB values for lights, this command is accepted by address or broadcast.
// This command does not talk back.
// TODO get rid of the talking back on the ELSE

            } else if(strcmp(pCmd,"setRGB") == 0) {
                uint8_t address = -1;
                int redValue = -1;
                int greenValue = -1;
                int blueValue = -1;
                if (paramCnt() > 3) {
                    getParam(0,address);
                    getParam(1,redValue);
                    getParam(2,greenValue);
                    getParam(3,blueValue);
                    if ( _pPC->IsMyOrBcast(address)){
                        _pPC->setRedValue(redValue);
                        _pPC->setGreenValue(greenValue);
                        _pPC->setBlueValue(blueValue);
                    }
                } else {
                    _pHW->print("Fail:vTreeLED requires a single param: 1 | 0.\n");
                }

            } else {
                sprintf(buffer,"Fail:This is an Invalid Cmd:%s\n",pCmd);
                _pHW->print(buffer);
            }       
        resetCmd();
    }

}


