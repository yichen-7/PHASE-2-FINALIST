#include "AddSWITCH.h"
#include "ApplicationManager.h"
#include "Actions/Action.h"
#include "GUI/Input.h"
#include "GUI/Output.h"


AddSWITCH::AddSWITCH(ApplicationManager* pApp) : Action(pApp)
{
}

AddSWITCH::~AddSWITCH()
{
}

void AddSWITCH::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pOut->PrintMsg("Click to place the switch");
	pIn->GetPointClicked(Cx, Cy);      // store position
	pOut->ClearStatusBar();
}

void AddSWITCH::Execute()
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

	SWITCH* pS = new SWITCH(GInfo);
	
	//ADDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
	pManager->AddComponent(pS);
}

void AddSWITCH::Undo()
{
}

void AddSWITCH::Redo()
{
}