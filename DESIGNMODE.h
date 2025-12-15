#ifndef _SWITCH_TO_DESIGN_MODE_H
#define _SWITCH_TO_DESIGN_MODE_H

#include "Actions/Action.h"

class SwitchToDesignMode : public Action
{
public:
    SwitchToDesignMode(ApplicationManager* pApp);
    virtual ~SwitchToDesignMode();

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif
