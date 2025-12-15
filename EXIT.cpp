#include "Exit.h"
#include "ApplicationManager.h"
#include "GUI/Output.h"

Exit::Exit(ApplicationManager* pApp) : Action(pApp)
{
}

Exit::~Exit()
{
}

void Exit::ReadActionParameters()
{
    // No parameters needed for exit
    Output* pOut = pManager->GetOutput();
    pOut->PrintMsg("Exiting application...");
}

void Exit::Execute()
{
    ReadActionParameters();
    // The actual exit is handled in main.cpp when EXIT action is returned
}

void Exit::Undo()
{
    // Cannot undo exit
}

void Exit::Redo()
{
    // Cannot redo exit
}