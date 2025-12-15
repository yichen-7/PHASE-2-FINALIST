#include "SWITCH.h"
#include "GUI/Output.h"

SWITCH::SWITCH(const GraphicsInfo& r_GfxInfo) : Component(r_GfxInfo), m_OutputPin(5)
{
	// Initialize switch to OFF (LOW)
	m_OutputPin.setStatus(LOW);
	m_OutputPin.setComponent(this);
}

void SWITCH::Operate()
{
	// Switch doesn't perform operations
	// Its output status is controlled by Toggle() method
}

void SWITCH::Draw(Output* pOut)
{
	bool isOn = (m_OutputPin.getStatus() == HIGH);
	pOut->DRAWSWITCH(m_GfxInfo, isOn);

	string label = GetLabel();
	if (label != "")
	{
		int labelX = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2 - 20;
		int labelY = m_GfxInfo.y1 - 15;
		pOut->DrawText(labelX, labelY, label);
	}
}

int SWITCH::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

int SWITCH::GetInputPinStatus(int n)
{
	return -1;  // Switch has no inputs
}

void SWITCH::setInputPinStatus(int n, STATUS s)
{
	// Switch has no inputs - do nothing
}

OutputPin* SWITCH::GetOutputPin()
{
	return &m_OutputPin;
}

void SWITCH::Toggle()
{
	if (m_OutputPin.getStatus() == LOW)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}