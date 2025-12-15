#ifndef _ADD_LED_H
#define _ADD_LED_H

#include "Actions/Action.h"
#include "LED.h"

class AddLED : public Action
{
private:
	// Parameters for rectangular area to be occupied by the LED
	int Cx, Cy;	// Center point of the LED
	int x1, y1, x2, y2;	// Two corners of the rectangular area

public:
	AddLED(ApplicationManager* pApp);
	virtual ~AddLED(void);

	// Reads parameters required for action to execute
	virtual void ReadActionParameters();

	// Execute action (adds LED to the circuit)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif
