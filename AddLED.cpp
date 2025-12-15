#include "AddLED.h"
#include "ApplicationManager.h"
#include "Actions/Action.h"

AddLED::AddLED(ApplicationManager* pApp) : Action(pApp)
{
}

AddLED::~AddLED(void)
{
}

void AddLED::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	// Print Action Message
	pOut->PrintMsg("LED: Click to add the LED");

	// Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	// Clear Status Bar
	pOut->ClearStatusBar();
}

void AddLED::Execute()
{
	// Get Center point of the LED
	ReadActionParameters();

	// Calculate the rectangle Corners
	int Len = UI.AND2_Width;   // Use same width as gates
	int Wdth = UI.AND2_Height; // Use same height as gates
	if (!pManager->IsValidPlacement(Cx, Cy, Len, Wdth))
	{
		pManager->GetOutput()->PrintMsg("Invalid placement! Component must be within drawing area.");
		return;
	}
	GraphicsInfo GInfo; // Gfx info to be used to construct the LED

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;

	// Create new LED component
	LED* pLED = new LED(GInfo);
	
	
	//ADDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
	// Add the LED to the component list

	pManager->AddComponent(pLED);
}

void AddLED::Undo()
{
	// TODO: Implement undo functionality
}

void AddLED::Redo()
{
	// TODO: Implement redo functionality
}