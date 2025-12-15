#include "Paste.h"
#include "ApplicationManager.h"
#include "GUI/Input.h"
#include "GUI/Output.h"

Paste::Paste(ApplicationManager* pApp) : Action(pApp) {}
Paste::~Paste() {}

void Paste::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Paste: Click where you want to place the component");
    int x, y;
    pIn->GetPointClicked(x, y);
    pOut->ClearStatusBar();

    pManager->PasteAt(x, y);
}

void Paste::Execute()
{
    ReadActionParameters();
}

void Paste::Undo() {}
void Paste::Redo() {}
