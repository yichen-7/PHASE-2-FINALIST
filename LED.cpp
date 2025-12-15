#include "LED.h"

LED::LED(const GraphicsInfo& r_GfxInfo) : Component(r_GfxInfo)
{
    // Initialize the input pin
    m_InputPin.setComponent(this);
    m_InputPin.setPinIndex(0);      // LED has only 1 input (index 0)
    m_InputPin.setTotalPins(1);     // LED has 1 total input pin
}

void LED::Operate()
{
    // LED just displays the status of its input pin
}

void LED::Draw(Output* pOut)
{
    bool isLit = (m_InputPin.getStatus() == HIGH);
    pOut->DRAWLED(m_GfxInfo, isLit);

    string label = GetLabel();
    if (label != "")
    {
        int labelX = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2 - 20;
        int labelY = m_GfxInfo.y1 - 15;
        pOut->DrawText(labelX, labelY, label);
    }
}

int LED::GetOutPinStatus()
{
    return -1;  // LED has no output
}

int LED::GetInputPinStatus(int n)
{
    if (n == 1)  // n starts from 1
        return m_InputPin.getStatus();
    return -1;
}

void LED::setInputPinStatus(int n, STATUS s)
{
    if (n == 1)  // n starts from 1
        m_InputPin.setStatus(s);
}

InputPin* LED::GetInputPin(int index)
{
    if (index == 0)  // index starts from 0
        return &m_InputPin;
    return nullptr;
}