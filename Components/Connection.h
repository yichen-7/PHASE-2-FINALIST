#ifndef _CONNECTION_H
#define _CONNECTION_H
#include "Component.h"

class OutputPin;
class InputPin;

class Connection : public Component
{
private:
    OutputPin* SrcPin;
    InputPin* DstPin;
public:
    Connection(const GraphicsInfo& r_GfxInfo, OutputPin* pSrcPin, InputPin* pDstPin);

    void setSourcePin(OutputPin* pSrcPin);
    OutputPin* getSourcePin();
    void setDestPin(InputPin* pDstPin);
    InputPin* getDestPin();

    virtual bool IsInside(int x, int y) const override;

    virtual void Operate() override;
    virtual void Draw(Output* pOut) override;
    virtual int GetOutPinStatus() override;
    virtual int GetInputPinStatus(int n) override;
    virtual void setInputPinStatus(int n, STATUS s) override;

    // Clone for Copy/Paste
    virtual Component* Clone() const override {
        return new Connection(m_GfxInfo, SrcPin, DstPin);
    }
};
#endif