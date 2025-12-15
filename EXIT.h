#ifndef _EXIT_H
#define _EXIT_H

#include "Actions/Action.h"

class Exit : public Action
{
public:
    Exit(ApplicationManager* pApp);
    virtual ~Exit();

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif
