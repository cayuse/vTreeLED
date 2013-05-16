
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
            if (strcmp(pCmd,"status") == 0) {
                  sprintf(buffer,"Ok:Ditch:%d Sump:%d PC:%d P:%d NC:%d N:%d SC:%d S:%d ST:%d STen:%d\n",
                    _pPC->ditchCurr,
                    _pPC->sumpCurr,
                    _pPC->vTreeLEDCall,
                    _pPC->isvTreeLEDOn(),
                    _pPC->northCall, _pPC->isNorthOn(),
                    _pPC->southCall, _pPC->isSouthOn(),
                    _pPC->sumpLowTrigger,
                    _pPC->enableSumpTrigger
                    );
                _pHW->print(buffer);

            } else if(strcmp(pCmd,"vTreeLED") == 0) {
                int idx = -1;
                if (paramCnt() > 0) {
                    getParam(0,idx);
                    _pPC->setvTreeLED(idx != 0);
                    _pHW->print("Ok\n");
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


