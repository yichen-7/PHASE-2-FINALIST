#ifndef _MOVE_H
#define _MOVE_H

#include "Actions/Action.h"

// Forward declaration
class Component;

class Move : public Action
{
private:
    int Cx, Cy;           // First click - reference point
    int NewCx, NewCy;     // Second click - where to move
    Component* pComp;     // Component to move (nullptr for multi-move)

    // Helper function to update all connections after moving components
    void UpdateAllConnections();

public:
    Move(ApplicationManager* pApp);
    virtual ~Move();

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();
    virtual void Redo();
};

#endif