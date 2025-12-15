#include "AddINVgate1.h"
#include "ApplicationManager.h"
#include "Actions/Action.h"

AddINVgate1::AddINVgate1(ApplicationManager* pApp) :Action(pApp)
{
}

AddINVgate1::~AddINVgate1(void)
{
}

void AddINVgate1::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("1-Input INVERTER Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddINVgate1::Execute()
{
    ReadActionParameters();

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

    INV1* pA = new INV1(GInfo, AND2_FANOUT);
    pManager->AddComponent(pA);
}

void AddINVgate1::Undo()
{
}

void AddINVgate1::Redo()
{
}

