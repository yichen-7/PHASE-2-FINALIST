#ifndef _GATE_H
#define _GATE_H

#include "InputPin.h"
#include "OutputPin.h"
#include "Component.h"

class Gate : public Component
{
protected:
	InputPin* m_InputPins;
	OutputPin m_OutputPin;
	int m_Inputs;

public:
	Gate(int r_Inputs, int r_FanOut);
	virtual ~Gate();

	// Pin access methods - these are DECLARED here and IMPLEMENTED in Gate.cpp
	virtual int GetInputPinCount() const;
	virtual InputPin* GetInputPin(int index);
	virtual OutputPin* GetOutputPin();
};

#endif