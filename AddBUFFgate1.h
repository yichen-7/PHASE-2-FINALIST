#ifndef _ADD_BUFF_GATE_H
#define _ADD_BUFF_GATE_H

#include "Actions/Action.h"            
#include "BUFF1.h"

class AddBUFFgate1 : public Action
{
private:
    int Cx, Cy;
    int x1, y1, x2, y2;

public:
    AddBUFFgate1(ApplicationManager* pApp);
    virtual ~AddBUFFgate1(void);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif
