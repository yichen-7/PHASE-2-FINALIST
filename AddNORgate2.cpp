#include "AddNORgate2.h"
#include "ApplicationManager.h"
#include "Actions/Action.h"

AddNORgate2::AddNORgate2(ApplicationManager* pApp) :Action(pApp)
{
}

AddNORgate2::~AddNORgate2(void)
{
}

void AddNORgate2::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Input NOR Gate: Click to add the gate");

	//Wait fNOR User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddNORgate2::Execute()
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

    NOR2* pA = new NOR2(GInfo, AND2_FANOUT);
    pManager->AddComponent(pA);
}
void AddNORgate2::Undo()
{
}

void AddNORgate2::Redo()
{
}

