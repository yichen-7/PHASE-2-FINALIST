#include "SimMode.h"
#include "ApplicationManager.h"  // Add this line
#include "GUI/Output.h"
#include "GUI/Input.h"

SwitchToSimMode::SwitchToSimMode(ApplicationManager* pApp) : Action(pApp)
{
}

SwitchToSimMode::~SwitchToSimMode()
{
}

void SwitchToSimMode::ReadActionParameters()
{
    // No parameters needed
}

void SwitchToSimMode::Execute()
{
    Output* pOut = pManager->GetOutput();

    // Validate circuit
    string errorMsg;
    if (pManager->ValidateCircuit(errorMsg))
    {
        // Circuit is valid, switch to simulation mode
        pOut->CreateSimulationToolBar();
        pOut->PrintMsg("Switched to Simulation Mode - Circuit is valid!");
    }
    else
    {
        // Circuit is invalid, show error message
        pOut->PrintMsg(errorMsg);
    }
}

void SwitchToSimMode::Undo()
{
    // Cannot undo mode switch
}

void SwitchToSimMode::Redo()
{
    // Cannot redo mode switch
}