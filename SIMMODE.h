#ifndef _SWITCH_TO_SIM_MODE_H
#define _SWITCH_TO_SIM_MODE_H

#include "Actions/Action.h" 

class SwitchToSimMode : public Action
{
public:
	SwitchToSimMode(ApplicationManager* pApp);
	virtual ~SwitchToSimMode();

	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

#endif

