#ifndef _SELECT_H
#define _SELECT_H

#include "Actions/Action.h"

class Select : public Action
{
private:
    int Cx, Cy;  // Click position

public:
    Select(ApplicationManager* pApp);
    virtual ~Select();

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif