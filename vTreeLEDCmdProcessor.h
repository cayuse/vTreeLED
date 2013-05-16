#ifndef vTreeLEDCMDPROCESSOR_H
#define vTreeLEDCMDPROCESSOR_H

#include "CmdProcessor.h"
#include "vTreeLEDControl.h"


class vTreeLEDCmdProcessor : public CmdProcessor
{

    vTreeLEDControl* _pPC;

public:
    vTreeLEDCmdProcessor(vTreeLEDControl* vTreeLEDCtrl);
    ~vTreeLEDCmdProcessor();
    
    bool IsMyAddress(int address);
    bool IsBcastAddress(int address);
    bool IsMyOrBroadcast(int address);

    void Loop();
    
};

#endif
