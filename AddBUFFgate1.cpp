#include "AddBUFFgate1.h"
#include "ApplicationManager.h"
#include "Actions/Action.h"

AddBUFFgate1::AddBUFFgate1(ApplicationManager* pApp) :Action(pApp)
{
}

AddBUFFgate1::~AddBUFFgate1(void)
{
}

void AddBUFFgate1::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("1-Input BUFFER Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddBUFFgate1::Execute()
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

    BUFF1* pA = new BUFF1(GInfo, AND2_FANOUT);

    pManager->AddComponent(pA);
}
    void AddBUFFgate1::Undo()
    {
    }

    void AddBUFFgate1::Redo()
    {
    }

