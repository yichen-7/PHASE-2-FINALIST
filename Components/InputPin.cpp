#include "InputPin.h"
#include "Component.h"

InputPin::InputPin() : Pin()
{
    pComp = nullptr;
    m_pConn = nullptr;
    m_PinIndex = 0;    // Initialize
    m_TotalPins = 1;   // Initialize
}

void InputPin::setComponent(Component* pCmp)
{
    pComp = pCmp;
}

Component* InputPin::getComponent()
{
    return pComp;
}

void InputPin::setConnection(Connection* c)
{
    m_pConn = c;
}

Connection* InputPin::getConnection()
{
    return m_pConn;
}

void InputPin::setPinIndex(int index)
{
    m_PinIndex = index;
}

void InputPin::setTotalPins(int total)
{
    m_TotalPins = total;
}

int InputPin::getX() const
{
    if (!pComp) return 0;

    GraphicsInfo gfx = pComp->GetGraphicsInfo();
    // Input pins are on the LEFT side
    return gfx.x1;
}

int InputPin::getY() const
{
    if (!pComp) return 0;

    GraphicsInfo gfx = pComp->GetGraphicsInfo();
    int height = gfx.y2 - gfx.y1;

    // Calculate Y position based on pin index and total pins
    if (m_TotalPins == 1)
    {
        // Single input: center
        return (gfx.y1 + gfx.y2) / 2;
    }
    else if (m_TotalPins == 2)
    {
        // Two inputs: divide into thirds
        if (m_PinIndex == 0)
            return gfx.y1 + height / 3;      // Top third
        else
            return gfx.y1 + (2 * height) / 3; // Bottom third
    }
    else if (m_TotalPins == 3)
    {
        // Three inputs: divide into quarters
        if (m_PinIndex == 0)
            return gfx.y1 + height / 4;       // Top quarter
        else if (m_PinIndex == 1)
            return gfx.y1 + height / 2;       // Middle
        else
            return gfx.y1 + (3 * height) / 4; // Bottom quarter
    }

    // Default: center
    return (gfx.y1 + gfx.y2) / 2;
}