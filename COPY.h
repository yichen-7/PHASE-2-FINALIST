#ifndef _COPY_H
#define _COPY_H

#include "Actions/Action.h"

class Copy : public Action
{
public:
    Copy(ApplicationManager* pApp);
    virtual ~Copy();

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif
