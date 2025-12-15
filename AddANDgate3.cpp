#include "AddANDgate3.h"
#include "ApplicationManager.h"
#include "Actions/Action.h"

AddANDgate3::AddANDgate3(ApplicationManager* pApp) :Action(pApp)
{
}

AddANDgate3::~AddANDgate3(void)
{
}

void AddANDgate3::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("3-Input AND Gate: Click to add the gate");

	//Wait fAND User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddANDgate3::Execute()
{
    ReadActionParameters();

    // STRICTLY using AND2 dimensions as requested
    int Len = UI.AND2_Width;
    int Wdth = UI.AND2_Height;

    if (!pManager->IsValidPlacement(Cx, Cy, Len, Wdth))
    {
        pManager->GetOutput()->PrintMsg("Invalid placement! Component must be within drawing area.");
        return;
    }

    GraphicsInfo GInfo;
    GInfo.x1 = Cx - Len / 2;
    GInfo.x2 = Cx + Len / 2;
    GInfo.y1 = Cy - Wdth / 2;
    GInfo.y2 = Cy + Wdth / 2;

    // STRICTLY using AND2_FANOUT as requested
    AND3* pA = new AND3(GInfo, AND2_FANOUT);
    pManager->AddComponent(pA);
}

void AddANDgate3::Undo()
{
}

void AddANDgate3::Redo()
{
}