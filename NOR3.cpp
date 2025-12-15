#include "NOR3.h"
#include <fstream>
using namespace std;
NOR3::NOR3(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(3, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void NOR3::Operate()
{
	// 3-input NOR: output HIGH only if ALL three inputs are LOW
	STATUS input1 = m_InputPins[0].getStatus();
	STATUS input2 = m_InputPins[1].getStatus();
	STATUS input3 = m_InputPins[2].getStatus();

	if (input1 == LOW && input2 == LOW && input3 == LOW)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}


// Function Draw
// Draws 2-input NOR gate
void NOR3::Draw(Output* pOut)
{
	//Call output class NOR pass gate drawing info to it.
	pOut->DrawNOR3(m_GfxInfo, IsSelected());
	string label = GetLabel();
	if (label != "")
	{
		int labelX = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2 - 20;
		int labelY = m_GfxInfo.y1 - 15;
		pOut->DrawText(labelX, labelY, label);
	}
}

//returns status of outputpin
int NOR3::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}
// In NOR3.cpp (replace NOR3 with gate name)

// Clone for Copy/Paste
Component* NOR3::Clone() const
{
	return new NOR3(this->GetGraphicsInfo(), AND2_FANOUT);
}
//returns status of Inputpin #n
int NOR3::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH NOR LOW
void NOR3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}