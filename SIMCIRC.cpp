#include "Simcirc.h"
#include "ApplicationManager.h"
#include "SWITCH.h"
#include "GUI\Output.h"
#include "GUI\Input.h"

SimulateCircuit::SimulateCircuit(ApplicationManager* pApp) : Action(pApp)
{
}

SimulateCircuit::~SimulateCircuit()
{
}

void SimulateCircuit::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	// Get click position
	pIn->GetPointClicked(Cx, Cy);
}

void SimulateCircuit::Execute()
{
	ReadActionParameters();

	// Find component at clicked position
	Component* pComp = pManager->GetComponentAt(Cx, Cy);

	Output* pOut = pManager->GetOutput();

	if (pComp != NULL)
	{
		// Check if it's a switch
		SWITCH* pSwitch = dynamic_cast<SWITCH*>(pComp);

		if (pSwitch != NULL)
		{
			// Toggle the switch
			pSwitch->Toggle();

			// Show status
			if (pSwitch->GetOutPinStatus() == HIGH)
				pOut->PrintMsg("Switch turned ON");
			else
				pOut->PrintMsg("Switch turned OFF");

			// Propagate the signal through the circuit
			pManager->PropagateSignal();

			// Clear and redraw to show changes
			pOut->ClearDrawingArea();
			pManager->UpdateInterface();
		}
		else
		{
			pOut->PrintMsg("Click on a switch to toggle it in simulation mode");
		}
	}
	else
	{
		pOut->PrintMsg("No component at this position");
	}
}

void SimulateCircuit::Undo()
{
	// TODO: Implement undo if needed
}

void SimulateCircuit::Redo()
{
	// TODO: Implement redo if needed
}