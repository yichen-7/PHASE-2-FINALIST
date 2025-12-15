#include "DesignMode.h"
#include "ApplicationManager.h"
#include "GUI/Output.h"
#include "GUI/Input.h"

SwitchToDesignMode::SwitchToDesignMode(ApplicationManager* pApp) : Action(pApp)
{
}

SwitchToDesignMode::~SwitchToDesignMode()
{
}

void SwitchToDesignMode::ReadActionParameters()
{
    // No parameters needed
}

void SwitchToDesignMode::Execute()
{
    Output* pOut = pManager->GetOutput();

    // Switch back to design mode
    pOut->CreateDesignToolBar();
    pOut->PrintMsg("Switched to Design Mode");

    // Clear any simulation state if needed
    // Reset all component states, clear highlights, etc.
}

void SwitchToDesignMode::Undo()
{
    // Cannot undo mode switch
}

void SwitchToDesignMode::Redo()
{
    // Cannot redo mode switch
}