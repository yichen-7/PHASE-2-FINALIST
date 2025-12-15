#ifndef _PROBE_CIRCUIT_H
#define _PROBE_CIRCUIT_H

#include "Actions/Action.h"

class ProbeCircuit : public Action
{
private:
	int Cx, Cy;  // Click position

public:
	ProbeCircuit(ApplicationManager* pApp);
	virtual ~ProbeCircuit();

	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

#endif