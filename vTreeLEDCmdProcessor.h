#ifndef vTreeLEDCMDPROCESSOR_H
#define vTreeLEDCMDPROCESSOR_H

#include "CmdProcessor.h"
#include "vTreeLEDControl.h"


class vTreeLEDCmdProcessor : public CmdProcessor
{
    uint8_t  myAddr;

    vTreeLEDControl* _pPC;

public:
    vTreeLEDCmdProcessor(vTreeLEDControl* vTreeLEDCtrl);
    ~vTreeLEDCmdProcessor();
    
    bool IsMyAddress(uint8_t address);
    bool IsBcastAddress(uint8_t address);
    bool IsMyOrBcast(uint8_t address);

    void Loop();
    
};

#endif
