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
    


    void Loop();
    
};

#endif
