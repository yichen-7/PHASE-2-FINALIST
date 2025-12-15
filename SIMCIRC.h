#ifndef _SIMULATE_CIRCUIT_H
#define _SIMULATE_CIRCUIT_H

#include "Actions/Action.h"

class SimulateCircuit : public Action
{
private:
	int Cx, Cy;  // Click position

public:
	SimulateCircuit(ApplicationManager* pApp);
	virtual ~SimulateCircuit();

	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

#endif