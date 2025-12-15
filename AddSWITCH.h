#pragma once
#ifndef _ADD_SWITCH_H
#define _ADD_SWITCH_H

#include "Actions/Action.h"
#include "SWITCH.h"

class AddSWITCH : public Action
{
private:
	// Parameters for rectangular area to be occupied by the Switch
	int Cx, Cy;	// Center point of the Switch
	int x1, y1, x2, y2;	// Two corners of the rectangular area

public:
	AddSWITCH(ApplicationManager* pApp);
	virtual ~AddSWITCH();
	// Reads parameters required for action to execute
	virtual void ReadActionParameters();
	// Execute action (adds Switch to the circuit)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif
