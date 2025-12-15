#include "NAND2.h"
#include <fstream>
using namespace std;
NAND2::NAND2(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void NAND2::Operate()
{
	// NAND gate: output is LOW only if ALL inputs are HIGH
	STATUS input1 = m_InputPins[0].getStatus();
	STATUS input2 = m_InputPins[1].getStatus();

	if (input1 == HIGH && input2 == HIGH)
		m_OutputPin.setStatus(LOW);
	else
		m_OutputPin.setStatus(HIGH);
}
// In NAND2.cpp (replace NAND2 with gate name)


// Function Draw
// Draws 2-input NAND gate
void NAND2::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawNAND2(m_GfxInfo, IsSelected());
	string label = GetLabel();
	if (label != "")
	{
		int labelX = (m_GfxInfo.x1 + m_GfxInfo.x2) / 2 - 20;
		int labelY = m_GfxInfo.y1 - 15;
		pOut->DrawText(labelX, labelY, label);
	}
}

//returns status of outputpin
int NAND2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int NAND2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}
// Clone for Copy/Paste
Component* NAND2::Clone() const
{
	return new NAND2(this->GetGraphicsInfo(), AND2_FANOUT);
}
//Set status of an input pin ot HIGH OR LOW
void NAND2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
