#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "..\Defs.h"
#include "..\GUI\Output.h"

//Base class for classes Gate, Switch, and LED.
class Component
{
private:
	string m_Label;
	bool m_Selected;  // Selection state
protected:
	GraphicsInfo m_GfxInfo;	//The parameters required to draw a component
public:
	Component(const GraphicsInfo& r_GfxInfo);
	Component();

	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut) = 0;	//for each component to Draw itself

	virtual int GetOutPinStatus() = 0;	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n) = 0;	//returns status of Inputpin # n if SWITCH, return -1
	virtual void setInputPinStatus(int n, STATUS s) = 0;	//set status of Inputpin # n, to be used by connection class.

	// Label functions
	void SetLabel(const string& label) { m_Label = label; }
	string GetLabel() const { return m_Label; }

	// Selection functions
	void SetSelected(bool sel) { m_Selected = sel; }
	bool IsSelected() const { return m_Selected; }

	// Boundary checking
	virtual bool IsInside(int x, int y) const {
		return (x >= m_GfxInfo.x1 && x <= m_GfxInfo.x2 &&
			y >= m_GfxInfo.y1 && y <= m_GfxInfo.y2);
	}

	// Get coordinates for moving
	int GetX1() const { return m_GfxInfo.x1; }
	int GetY1() const { return m_GfxInfo.y1; }
	int GetX2() const { return m_GfxInfo.x2; }
	int GetY2() const { return m_GfxInfo.y2; }

	// Get graphics info
	GraphicsInfo GetGraphicsInfo() const { return m_GfxInfo; }

	// Set graphics info (for moving)
	void SetGraphicsInfo(const GraphicsInfo& gfx) { m_GfxInfo = gfx; }

	// Move function
	virtual void Move(int dx, int dy) {
		m_GfxInfo.x1 += dx;
		m_GfxInfo.x2 += dx;
		m_GfxInfo.y1 += dy;
		m_GfxInfo.y2 += dy;
	}

	// Clone function for copy/paste
	virtual Component* Clone() const = 0;

	// Pin access methods (default implementations return nullptr)
	virtual class OutputPin* GetOutputPin() { return nullptr; }
	virtual class InputPin* GetInputPin(int index) { return nullptr; }
	virtual int GetInputPinCount() const { return 0; }

	//Destructor must be virtual
	virtual ~Component();
};

#endif