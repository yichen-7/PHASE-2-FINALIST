#include "INV1.h"

INV1::INV1(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(1, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void INV1::Operate()
{
	// NOT gate: output is opposite of input
	STATUS input = m_InputPins[0].getStatus();

	if (input == HIGH)
		m_OutputPin.setStatus(LOW);
	else
		m_OutputPin.setStatus(HIGH);
}

void INV1::Draw(Output* pOut)
{
	pOut->DrawINV1(m_GfxInfo, IsSelected());
	string label = GetLabel();
	if (label != "")
	{
		int labelX = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2 - 20;
		int labelY = m_GfxInfo.y1 - 15;
		pOut->DrawText(labelX, labelY, label);
	}
}

int INV1::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

int INV1::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();
}

void INV1::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}