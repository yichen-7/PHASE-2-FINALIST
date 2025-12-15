#ifndef _OUTPUTPIN_H
#define _OUTPUTPIN_H

#include "Pin.h"

class Connection;  // Forward declaration
class Component;   // Forward declaration

class OutputPin : public Pin
{
private:
    Connection* m_Connections[MAX_CONNS];
    int m_FanOut;     // Maximum connections
    int m_Conn;       // Current number of connections
    Component* pComp; // Component this pin belongs to

public:
    OutputPin(int r_FanOut);

    bool ConnectTo(Connection* r_Conn);

    void RemoveConnection(Connection* r_Conn);

    void setComponent(Component* c);
    Component* getComponent();

    // Implement coordinate getters
    virtual int getX() const override;
    virtual int getY() const override;
};

#endif