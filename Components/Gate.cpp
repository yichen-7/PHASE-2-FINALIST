#include "Gate.h"

//Gate Constructor
//Parameters:
//r_Inputs: no. of gate's input pins
//r_FanOut: Fan out of the gate's output pin
Gate::Gate(int r_Inputs, int r_FanOut) : m_OutputPin(r_FanOut)
{
	//Allocate number of input pins (equals r_Inputs)
	m_InputPins = new InputPin[r_Inputs];
	m_Inputs = r_Inputs;	//set no. of inputs of that gate

	//Associate all input pins to this gate AND set their index/total
	for (int i = 0; i < m_Inputs; i++)
	{
		m_InputPins[i].setComponent(this);
		m_InputPins[i].setPinIndex(i);        // NEW: Set which pin this is (0, 1, 2)
		m_InputPins[i].setTotalPins(m_Inputs); // NEW: Set total number of inputs
	}

	// Associate output pin to this gate
	m_OutputPin.setComponent(this);
}

// NEW: Return pointer to output pin
OutputPin* Gate::GetOutputPin()
{
	return &m_OutputPin;
}

// NEW: Return pointer to input pin at index
InputPin* Gate::GetInputPin(int index)
{
	if (index >= 0 && index < m_Inputs)
		return &m_InputPins[index];
	return nullptr;
}

// NEW: Return number of input pins
int Gate::GetInputPinCount() const
{
	return m_Inputs;
}

Gate::~Gate()
{
	delete[] m_InputPins;
}