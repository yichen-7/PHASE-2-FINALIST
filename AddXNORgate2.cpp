#include "AddXNORgate2.h"
#include "ApplicationManager.h"
#include "Actions/Action.h"

AddXNORgate2::AddXNORgate2(ApplicationManager* pApp) :Action(pApp)
{
}

AddXNORgate2::~AddXNORgate2(void)
{
}

void AddXNORgate2::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Input XNOR Gate: Click to add the gate");

	//Wait fXNOR User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddXNORgate2::Execute()
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

    XNOR2* pA = new XNOR2(GInfo, AND2_FANOUT);
    pManager->AddComponent(pA);
}
void AddXNORgate2::Undo()
{
}

void AddXNORgate2::Redo()
{
}