#ifndef _ADD_INV_GATE_H
#define _ADD_INV_GATE_H

#include "Actions/Action.h"            
#include "INV1.h"

class AddINVgate1 : public Action
{
private:
    int Cx, Cy;
    int x1, y1, x2, y2;

public:
    AddINVgate1(ApplicationManager* pApp);
    virtual ~AddINVgate1(void);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif