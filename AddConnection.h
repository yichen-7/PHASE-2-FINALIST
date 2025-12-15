
#ifndef _ACTION_ADD_CONNECTION_H
#define _ACTION_ADD_CONNECTION_H

#include "Actions/Action.h"
#include "Defs.H"

class OutputPin;
class InputPin;
class Connection;

class AddConnection : public Action
{
private:
    GraphicsInfo GInfo;
    OutputPin* SrcPin;
    InputPin* DstPin;
    Connection* pConn;

public:
    AddConnection(ApplicationManager* pApp);
    virtual ~AddConnection();

    virtual void ReadActionParameters() override;
    virtual void Execute() override;
    virtual void Undo() override;
    virtual void Redo() override;
};

#endif