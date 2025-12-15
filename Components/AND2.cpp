#include "AND2.h"

AND2::AND2(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void AND2::Operate()
{
	//caclulate the output status as the ANDing of the two input pins
	STATUS s1 = m_InputPins[0].getStatus();
	STATUS s2 = m_InputPins[1].getStatus();

	if (s1 == HIGH && s2 == HIGH)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
	//Add you code here
}


// Function Draw
// Draws 2-input AND gate
void AND2::Draw(Output* pOut)
{
	pOut->DrawAND2(m_GfxInfo, IsSelected());
	string label = GetLabel();
	if (label != "")
	{
		int labelX = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2 - 20;
		int labelY = m_GfxInfo.y1 - 15;
		pOut->DrawText(labelX, labelY, label);
	}
}

//returns status of outputpin
int AND2::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int AND2::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();	//n starts from 1 but array index starts from 0.
}
// Clone for Copy/Paste



//Set status of an input pin ot HIGH or LOW
void AND2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}
