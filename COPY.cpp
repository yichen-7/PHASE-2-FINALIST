#include "Copy.h"
#include "ApplicationManager.h"
#include "GUI/Input.h"
#include "GUI/Output.h"

Copy::Copy(ApplicationManager* pApp) : Action(pApp) {}
Copy::~Copy() {}

void Copy::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Copy: Click on the component to copy");
    int x, y;
    pIn->GetPointClicked(x, y);
    pOut->ClearStatusBar();

    Component* c = pManager->GetComponentAt(x, y);
    if (c)
        pManager->CopyComponent(c);
    else
        pOut->PrintMsg("No component at clicked position");
}

void Copy::Execute()
{
    ReadActionParameters();
}

void Copy::Undo() {}
void Copy::Redo() {}