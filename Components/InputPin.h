#ifndef _INPUTPIN_H
#define _INPUTPIN_H

#include "Pin.h"

class Component;   // Forward declaration
class Connection;  // Forward declaration

class InputPin : public Pin
{
private:
    Component* pComp;      // Component this pin belongs to
    Connection* m_pConn;   // Connection attached to this pin
    int m_PinIndex;  // Which input pin is this (0, 1, or 2)
    int m_TotalPins; // Total number of input pins on this component

public:
    InputPin();

    void setComponent(Component* pCmp);
    Component* getComponent();

    void setConnection(Connection* c);
    Connection* getConnection();

    // ADD THESE SETTER METHODS
    void setPinIndex(int index);
    void setTotalPins(int total);

    // Implement coordinate getters
    virtual int getX() const override;
    virtual int getY() const override;
};

#endif