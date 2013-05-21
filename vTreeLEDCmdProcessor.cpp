
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
                  sprintf(buffer,"Ok:Address: %d Red:%d Yellow:%d Green:%d Blue:%d",
                    _pPC->myAddr,
                    _pPC->redValue,
                    _pPC->yellowValue,
                    _pPC->greenValue,
                    _pPC->blueValue
                    );
                _pHW->println(buffer);

// This command sets RGB values for lights
// This command is accepted by address or broadcast.
// This command should have a short command name.
// This command does not talk back.
// TODO get rid of the talking back on the ELSE

            } else if(strcmp(pCmd,"setRYGB") == 0) {
                uint8_t address = 0;
                int redValue = -1;
                int yellowValue = -1;
                int greenValue = -1;
                int blueValue = -1;
                if (paramCnt() > 4) {
                    getParam(0,address);
                    getParam(1,redValue);
                    getParam(2,yellowValue);
                    getParam(3,greenValue);
                    getParam(4,blueValue);
                    if ( _pPC->IsMyOrBcast(address)){
                        _pPC->setRedValue(redValue);
                        _pPC->setYellowValue(yellowValue);
                        _pPC->setGreenValue(greenValue);
                        _pPC->setBlueValue(blueValue);
                    }
                } else {
                    _pHW->println("Fail:setRYGB Requires an address plus 4 values 0-255");
                }
// This command sets Red value
// This command is accepted by address or broadcast.
// This command should have a short command name.
// This command does not talk back.


            } else if(strcmp(pCmd,"setRed") == 0) {
                uint8_t address = 0;
                int redValue = -1;
                if (paramCnt() == 2) {
                    getParam(0,address);
                    getParam(1,redValue);
                    if ( _pPC->IsMyOrBcast(address)){
                        _pPC->setRedValue(redValue);
                    }
                } else {
                    //_pHW->print("Fail:\n");
                }
// This command sets Red value
// This command is accepted by address or broadcast.
// This command should have a short command name.
// This command does not talk back.


            } else if(strcmp(pCmd,"setYellow") == 0) {
                uint8_t address = 0;
                int yellowValue = -1;
                if (paramCnt() == 2) {
                    getParam(0,address);
                    getParam(1,yellowValue);
                    if ( _pPC->IsMyOrBcast(address)){
                        _pPC->setYellowValue(yellowValue);
                    }
                } else {
                    //_pHW->print("Fail:\n");
                }
// This command sets Green value
// This command is accepted by address or broadcast.
// This command should have a short command name.
// This command does not talk back.

            } else if(strcmp(pCmd,"setGreen") == 0) {
                uint8_t address = 0;
                int greenValue = -1;
                if (paramCnt() == 2) {
                    getParam(0,address);
                    getParam(1,greenValue);
                    if ( _pPC->IsMyOrBcast(address)){
                        _pPC->setGreenValue(greenValue);
                    }
                } else {
                    //_pHW->print("Fail:\n");
                }
// This command sets Blue value
// This command is accepted by address or broadcast.
// This command should have a short command name.
// This command does not talk back.

            } else if(strcmp(pCmd,"setBlue") == 0) {
                uint8_t address = 0;
                int blueValue = -1;
                if (paramCnt() == 2) {
                    getParam(0,address);
                    getParam(1,blueValue);
                    if ( _pPC->IsMyOrBcast(address)){
                        _pPC->setBlueValue(blueValue);
                    }
                } else {
                    //_pHW->print("Fail:\n");
                }
// This command sets the programmable Address
// This command is accepted by address or broadcast.
// This command does not require a short command name.
// This command talks back on success or failure.
            } else if(strcmp(pCmd,"setAddress") == 0) {
                uint8_t oldAddress = 0;
                uint8_t address = 0;
                uint8_t newAddress = 0;
                if (paramCnt() == 2) {
                    getParam(0,address);
                    getParam(1,newAddress);
                    if ( _pPC->IsMyOrBcast(address)){
                        oldAddress = _pPC->myAddr;
                        _pPC->setAddress(newAddress);
                        sprintf(buffer,"OK: Address Changed from: 0x%02x: to 0x%02x",
                        oldAddress,
                        newAddress
                        );
                        _pHW->println(buffer);
                    }
                } else {
                    _pHW->println("Fail:setAddress requires exactly 2 arguments: oldAddress(bCast ok) + newAddress");
                }
            } else {
                sprintf(buffer,"Fail:This is an Invalid Cmd:%s",pCmd);
                _pHW->println(buffer);
            }       
        resetCmd();
    }

}


