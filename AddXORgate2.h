#ifndef _ADD_XOR_GATE_H
#define _ADD_XOR_GATE_H

#include "Actions/Action.h"            
#include "XOR2.h"

class AddXORgate2 : public Action
{
private:
    int Cx, Cy;
    int x1, y1, x2, y2;

public:
    AddXORgate2(ApplicationManager* pApp);
    virtual ~AddXORgate2(void);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif
