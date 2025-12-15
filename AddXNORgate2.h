#ifndef _ADD_XNOR_GATE_H
#define _ADD_XNOR_GATE_H

#include "Actions/Action.h"            
#include "XNOR2.h"

class AddXNORgate2 : public Action
{
private:
    int Cx, Cy;
    int x1, y1, x2, y2;

public:
    AddXNORgate2(ApplicationManager* pApp);
    virtual ~AddXNORgate2(void);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif
