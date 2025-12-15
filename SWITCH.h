#ifndef _SWITCH_H
#define _SWITCH_H

#include "Components/Component.h"
#include "Components/OutputPin.h"

class SWITCH : public Component
{
private:
	OutputPin m_OutputPin;

public:
	SWITCH(const GraphicsInfo& r_GfxInfo);

	virtual void Operate();
	virtual void Draw(Output* pOut);

	virtual int GetOutPinStatus();
	virtual int GetInputPinStatus(int n);
	virtual void setInputPinStatus(int n, STATUS s);

	virtual OutputPin* GetOutputPin();

	void Toggle();

	// Clone for Copy/Paste
	virtual Component* Clone() const override {
		return new SWITCH(m_GfxInfo);
	}
};

#endif