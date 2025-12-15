#ifndef _CUT_H
#define _CUT_H

#include "Actions/Action.h"

class Cut : public Action
{
public:
    Cut(ApplicationManager* pApp);
    virtual ~Cut();

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif
