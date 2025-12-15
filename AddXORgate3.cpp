#include "AddXORgate3.h"
#include "ApplicationManager.h"
#include "Actions/Action.h"

AddXORgate3::AddXORgate3(ApplicationManager* pApp) :Action(pApp)
{
}

AddXORgate3::~AddXORgate3(void)
{
}

void AddXORgate3::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("3-Input XOR Gate: Click to add the gate");

	//Wait fXOR User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddXORgate3::Execute()
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

    XOR3* pA = new XOR3(GInfo, AND2_FANOUT);
    pManager->AddComponent(pA);
}
void AddXORgate3::Undo()
{
}

void AddXORgate3::Redo()
{
}