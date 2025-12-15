#include "Cut.h"
#include "ApplicationManager.h"
#include "GUI/Input.h"
#include "GUI/Output.h"

Cut::Cut(ApplicationManager* pApp) : Action(pApp) {}
Cut::~Cut() {}

void Cut::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Cut: Click on the component to cut");
    int x, y;
    pIn->GetPointClicked(x, y);
    pOut->ClearStatusBar();

    Component* c = pManager->GetComponentAt(x, y);
    if (c)
    {
        pManager->CutComponent(c);

        // Force interface refresh
        pOut->ClearDrawingArea();
        pManager->UpdateInterface();
        pOut->PrintMsg("Component cut - click Paste to place it");
    }
    else
        pOut->PrintMsg("No component at clicked position");
}

void Cut::Execute()
{
    ReadActionParameters();
}

void Cut::Undo() {}
void Cut::Redo() {}