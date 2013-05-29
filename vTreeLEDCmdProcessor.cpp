
#include <string.h>
#include "vTreeLEDCmdProcessor.h"
#include "vTreeLEDControl.h"

static char buffer[80];

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

    if (checkCommands()) {

        // Process the command

        const char *pCmd = getCmd();

        // What is the best way? An enum would work, but hard to
        // manage. A string is easy, but inefficient... but easy.
        // This command responds always and with the following information. It should also include address.
        // But i have to go so I can't do that right atm.

        if (strcmp(pCmd,"status") == 0) {
            sprintf(buffer,"Status: UID=%02X GID=%20X Red=%u Green=%u Blue=%u Bright=%u",
                    _pPC->unitID,
                    _pPC->groupID,
                    _pPC->red,
                    _pPC->green,
                    _pPC->blue,
                    _pPC->brightness
            );
            _pHW->println(buffer);
        }

        // This command sets RGB values for lights
        // This command is accepted by UID,GID or broadcast.
        // This command should have a short command name.
        // This command does not talk back.
        // TODO get rid of the talking back on the ELSE

        else if(strcmp(pCmd,"RGB") == 0) {
            uint8_t address;
            uint8_t red;
            uint8_t green;
            uint8_t blue;

            if (paramCnt() > 3) {
                getParam(0, address);
                getParam(1, red);
                getParam(2, green);
                getParam(3, blue);
                if (_pPC->isAny(address)) {
                    _pPC->setRed(red);
                    _pPC->setGreen(green);
                    _pPC->setBlue(blue);
                }
            }
            else {
//              _pHW->println("Fail: RGB requires address plus 3 values 0-255");
            }
        }

        // This command sets Red value
        // This command is accepted by UID,GID or broadcast.
        // This command should have a short command name.
        // This command does not talk back.

        else if(strcmp(pCmd,"R") == 0) {
            uint8_t address;
            uint8_t red;

            if (paramCnt() == 2) {
                getParam(0, address);
                getParam(1, red);
                if (_pPC->isAny(address)) {
                   _pPC->setRed(red);
                }
            }
            else {
                //_pHW->print("Fail:\n");
            }
        }

        // This command sets Green value
        // This command is accepted by UID,GID or broadcast.
        // This command should have a short command name.
        // This command does not talk back.

        else if(strcmp(pCmd,"G") == 0) {
            uint8_t address;
            uint8_t green;

            if (paramCnt() == 2) {
                getParam(0, address);
                getParam(1, green);
                if (_pPC->isAny(address)) {
                    _pPC->setGreen(green);
                }
            }
            else {
                //_pHW->print("Fail:\n");
            }
        }

        // This command sets Blue value
        // This command is accepted by UID,GID or broadcast.
        // This command should have a short command name.
        // This command does not talk back.

        else if (strcmp(pCmd,"B") == 0) {
            uint8_t address;
            uint8_t blue;

            if (paramCnt() == 2) {
                getParam(0, address);
                getParam(1, blue);
                if (_pPC->isAny(address)) {
                    _pPC->setBlue(blue);
                }
            }
            else {
                //_pHW->print("Fail:\n");
            }
        }

        // Set overall brightness

        else if (strcmp(pCmd,"bright") == 0) {
            uint8_t address;
            uint8_t bright;

            if (paramCnt() == 2) {
                getParam(0, address);
                getParam(1, bright);
                if (_pPC->isAny(address)) {
                    _pPC->setBrightness(bright);
                }
            }
            else {
                //_pHW->print("Fail:\n");
            }
        }

        // This command sets the temporary Group ID
        // This command is accepted by address only.
        // This command does not talk back.

        else if (strcmp(pCmd,"GID") == 0) {
            uint8_t address;
            uint8_t newAddress;

            if (paramCnt() == 2) {
                getParam(0, address);
                getParam(1, newAddress);
                if (_pPC->isUnit(address)) {
                    _pPC->setGroupID(newAddress);
                }
            }
            else {
//              _pHW->println("Fail:setAddress requires exactly 2 arguments: oldAddress(bCast ok) + newAddress");
            }
        }
        
        // This command sets the programmable Unit ID
        // This command is accepted by address or broadcast.
        // This command does not require a short command name.
        // This command talks back on success or failure.
        // This command has an intentionally long name to
        //      prevent mixing up with the "GID" command.

        else if (strcmp(pCmd,"set_unit_id") == 0) {
            uint8_t oldAddress;
            uint8_t address;
            uint8_t newAddress;

            if (paramCnt() == 2) {
                getParam(0, address);
                getParam(1, newAddress);
                if (_pPC->isUnitOrBcast(address)) {
                    oldAddress = _pPC->unitID;
                    _pPC->setUnitID(newAddress);
                    sprintf(buffer,"Unit ID changed, old:%02X new:%02X",
                            oldAddress,
                            newAddress
                    );
                    _pHW->println(buffer);
                }
            }
            else {
//              _pHW->println("Fail:setAddress requires exactly 2 arguments: oldAddress(bCast ok) + newAddress");
            }
        }

        // Command not recognized

        else {
            sprintf(buffer,"Invalid command: %s", pCmd);
                    _pHW->println(buffer);
        }       

        resetCmd();

    }

}


