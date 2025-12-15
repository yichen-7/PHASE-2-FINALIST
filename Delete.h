#ifndef _DELETE_H
#define _DELETE_H

#include "Actions\Action.h"
#include "ApplicationManager.h"
#include "Components\Connection.h"

class Delete : public Action
{
private:
    int Cx, Cy;  // Position where user clicks

public:
    Delete(ApplicationManager* pApp);
    virtual ~Delete(void);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif