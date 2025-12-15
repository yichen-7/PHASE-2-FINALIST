#include "Connection.h"
#include "OutputPin.h"
#include "InputPin.h"

Connection::Connection(const GraphicsInfo& r_GfxInfo, OutputPin* pSrcPin, InputPin* pDstPin)
    : Component(r_GfxInfo)
{
    SrcPin = pSrcPin;
    DstPin = pDstPin;
}

void Connection::setSourcePin(OutputPin* pSrcPin)
{
    SrcPin = pSrcPin;
}

OutputPin* Connection::getSourcePin()
{
    return SrcPin;
}

void Connection::setDestPin(InputPin* pDstPin)
{
    DstPin = pDstPin;
}

InputPin* Connection::getDestPin()
{
    return DstPin;
}

void Connection::Operate()
{
    if (SrcPin && DstPin)
    {
        DstPin->setStatus(SrcPin->getStatus());
    }
}

void Connection::Draw(Output* pOut)
{
    if (SrcPin && DstPin)
    {
        m_GfxInfo.x1 = SrcPin->getX();
        m_GfxInfo.y1 = SrcPin->getY();
        m_GfxInfo.x2 = DstPin->getX();
        m_GfxInfo.y2 = DstPin->getY();
    }
    pOut->DrawConnection(m_GfxInfo, IsSelected());

    string label = GetLabel();
    if (label != "")
    {
        int midX = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2;
        int midY = (m_GfxInfo.y1 + m_GfxInfo.y2) / 2;
        pOut->DrawText(midX - 20, midY - 25, label);
    }
}

bool Connection::IsInside(int x, int y) const
{
    int x1, y1, x2, y2;

    if (SrcPin && DstPin)
    {
        x1 = SrcPin->getX();
        y1 = SrcPin->getY();
        x2 = DstPin->getX();
        y2 = DstPin->getY();
    }
    else
    {
        x1 = m_GfxInfo.x1;
        y1 = m_GfxInfo.y1;
        x2 = m_GfxInfo.x2;
        y2 = m_GfxInfo.y2;
    }

    int midX = (x1 + x2) / 2;
    const int TOLERANCE = 25;

    // Segment 1: Horizontal
    int seg1_minX = (x1 < midX) ? x1 : midX;
    int seg1_maxX = (x1 > midX) ? x1 : midX;
    if (x >= seg1_minX - TOLERANCE && x <= seg1_maxX + TOLERANCE)
    {
        if (y >= y1 - TOLERANCE && y <= y1 + TOLERANCE)
            return true;
    }

    // Segment 2: Vertical
    int seg2_minY = (y1 < y2) ? y1 : y2;
    int seg2_maxY = (y1 > y2) ? y1 : y2;
    if (y >= seg2_minY - TOLERANCE && y <= seg2_maxY + TOLERANCE)
    {
        if (x >= midX - TOLERANCE && x <= midX + TOLERANCE)
            return true;
    }

    // Segment 3: Horizontal
    int seg3_minX = (midX < x2) ? midX : x2;
    int seg3_maxX = (midX > x2) ? midX : x2;
    if (x >= seg3_minX - TOLERANCE && x <= seg3_maxX + TOLERANCE)
    {
        if (y >= y2 - TOLERANCE && y <= y2 + TOLERANCE)
            return true;
    }

    return false;
}

int Connection::GetOutPinStatus()
{
    return DstPin ? DstPin->getStatus() : -1;
}

int Connection::GetInputPinStatus(int n)
{
    return SrcPin ? SrcPin->getStatus() : -1;
}

void Connection::setInputPinStatus(int n, STATUS s)
{
    if (SrcPin)
        SrcPin->setStatus(s);
}