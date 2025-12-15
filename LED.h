#ifndef _LED_H
#define _LED_H

#include "Components/Component.h"
#include "Components/InputPin.h"

class LED : public Component
{
private:
	InputPin m_InputPin;
public:
	LED(const GraphicsInfo& r_GfxInfo);

	virtual void Operate();
	virtual void Draw(Output* pOut);

	virtual int GetOutPinStatus();
	virtual int GetInputPinStatus(int n);
	virtual void setInputPinStatus(int n, STATUS s);

	virtual InputPin* GetInputPin(int index);
	virtual int GetInputPinCount() const { return 1; }

	InputPin* getInputPin() { return &m_InputPin; }

	// Clone for Copy/Paste
	virtual Component* Clone() const override {
		return new LED(m_GfxInfo);
	}
};
#endif