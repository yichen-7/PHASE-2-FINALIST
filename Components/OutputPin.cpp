#include "OutputPin.h"
#include "Component.h"
#include "Connection.h"    // <<-- ADDED: needed so RemoveConnection implementation compiles

OutputPin::OutputPin(int r_FanOut) : Pin()
{
    m_Conn = 0;
    m_FanOut = (r_FanOut > MAX_CONNS) ? MAX_CONNS : r_FanOut;
    pComp = nullptr;

    for (int i = 0; i < MAX_CONNS; i++)
        m_Connections[i] = nullptr;
}

bool OutputPin::ConnectTo(Connection* r_Conn)
{
    if (m_Conn < m_FanOut)
    {
        m_Connections[m_Conn++] = r_Conn;
        return true;
    }
    return false;
}

void OutputPin::RemoveConnection(Connection* r_Conn)
{
    if (r_Conn == nullptr) return;

    // Find the connection in the array
    int found = -1;
    for (int i = 0; i < m_Conn; ++i)
    {
        if (m_Connections[i] == r_Conn)
        {
            found = i;
            break;
        }
    }
    if (found == -1) return;

    // Shift remaining connections left to fill the gap
    for (int i = found; i < m_Conn - 1; ++i)
        m_Connections[i] = m_Connections[i + 1];

    // Null the last slot and decrease count
    m_Connections[m_Conn - 1] = nullptr;
    m_Conn--;
}

void OutputPin::setComponent(Component* c)
{
    pComp = c;
}

Component* OutputPin::getComponent()
{
    return pComp;
}

int OutputPin::getX() const
{
    if (!pComp) return 0;

    GraphicsInfo gfx = pComp->GetGraphicsInfo();
    // Output pins are on the RIGHT side
    return gfx.x2;
}

int OutputPin::getY() const
{
    if (!pComp) return 0;

    GraphicsInfo gfx = pComp->GetGraphicsInfo();
    // Center vertically
    return (gfx.y1 + gfx.y2) / 2;
}