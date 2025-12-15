#include "Output.h"

// NOTE: Assuming 'UI' variable is declared externally and accessible here
extern UI_Info UI;

Output::Output()
{
	//Initialize user interface parameters

	UI.AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	UI.DrawColor = BLACK;
	UI.SelectColor = BLUE;
	UI.ConnColor = RED;
	UI.MsgColor = BLUE;
	UI.BkGrndColor = WHITE;

	//Create the drawing window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	ChangeTitle("Programming Techniques Project");

	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();//Create Status bar
	ClearDrawingArea();// XX we made added drawing area as a constructor to make it blue at the start

}

Input* Output::CreateInput() const
{
	//Create an Input Object & assign it to the Same Window
	Input* pIn = new Input(pWind);
	return pIn;
}


//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y) const
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(MEDIUMPURPLE, 3);
	pWind->DrawLine(0, UI.height - UI.StatusBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight;

	// Print the Message
	pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(UI.MsgColor);
	pWind->DrawString(MsgX, UI.height - MsgY, msg);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(LIGHTCYAN);
	pWind->DrawRectangle(MsgX - 25, UI.height - MsgY - 8, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void Output::ClearDrawingArea() const
{
	pWind->SetPen(BLACK, 1);
	pWind->SetBrush(LIGHTCYAN);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - 80 - UI.StatusBarHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
	UI.AppMode = DESIGN;	//Design Mode

	// --- 1. DESIGN MENU ITEMS (Bottom Bar) ---
	string DsnItemImages[ITM_DSN_CNT];
	DsnItemImages[ITM_BUFF] = "images\\Menu\\BUFF.jpg";
	DsnItemImages[ITM_INV] = "images\\Menu\\NOT.jpg";
	DsnItemImages[ITM_AND2] = "images\\Menu\\Menu_AND2.jpg";
	DsnItemImages[ITM_OR2] = "images\\Menu\\OR-Gate.jpg";
	DsnItemImages[ITM_NAND2] = "images\\Menu\\NAND.jpg";
	DsnItemImages[ITM_NOR2] = "images\\Menu\\NOR.jpg";
	DsnItemImages[ITM_XOR2] = "images\\Menu\\XOR.jpg";
	DsnItemImages[ITM_XNOR2] = "images\\Menu\\XNOR.jpg";
	DsnItemImages[ITM_AND3] = "images\\Menu\\AND3.jpg";
	DsnItemImages[ITM_NOR3] = "images\\Menu\\NOR3.jpg";
	DsnItemImages[ITM_XOR3] = "images\\Menu\\XOR3.jpg";
	DsnItemImages[ITM_SWITCH] = "images\\Menu\\SWITCH.jpg";
	DsnItemImages[ITM_LED] = "images\\Menu\\LED.jpg";
	DsnItemImages[ITM_EXIT] = "images\\Menu\\Menu_Exit.jpg";

	// --- 2. ACTION MENU ITEMS (Top Bar) ---
	string ActItemImages[ACT_DSN_CNT];
	ActItemImages[ACT_DELETE] = "images\\Menu\\DEL.jpg";
	ActItemImages[ACT_CONNECTION] = "images\\Menu\\CONNECTION.jpg";
	ActItemImages[ACT_EDIT] = "images\\Menu\\EDIT.jpg";
	ActItemImages[ACT_SIM] = "images\\Menu\\SIM.jpg";
	ActItemImages[ACT_MOVE] = "images\\Menu\\MOVE.jpg";
	ActItemImages[ACT_SELECT] = "images\\Menu\\SELECT.jpg";
	ActItemImages[ACT_COPY] = "images\\Menu\\COPY.jpg";
	ActItemImages[ACT_PASTE] = "images\\Menu\\PASTE.jpg";
	ActItemImages[ACT_CUT] = "images\\Menu\\CUT.jpg";
	ActItemImages[ACT_SAVE] = "images\\Menu\\SAVE.jpg";
	ActItemImages[ACT_LOAD] = "images\\Menu\\LOAD.jpg";


	// ----------------------------------------------------
	// DRAW ACTION TOOLBAR (TOP BAR)
	for (int i = 0; i < ACT_DSN_CNT; i++)
	{
		pWind->DrawImage(ActItemImages[i], i * UI.ToolItemWidth, 0, UI.ToolItemWidth + 5, UI.ToolBarHeight);
	}

	// DRAW DESIGN TOOLBAR (BOTTOM BAR)
	for (int i = 0; i < ITM_DSN_CNT; i++)
	{
		pWind->DrawImage(DsnItemImages[i], i * UI.ToolItemWidth, 620, UI.ToolItemWidth + 5, UI.ToolBarHeight);
	}


	//Draw a line under the toolbar
	pWind->SetPen(MEDIUMPURPLE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight + 540, UI.width, UI.ToolBarHeight + 540);
	// THIS IS A VERTICAL LINE TO SEPERATE BETWEEN GATES AND OTHER BUTTONS
	pWind->SetPen(MEDIUMPURPLE, 3);
	pWind->DrawLine(770, UI.ToolBarHeight + 540, UI.width - 230, UI.ToolBarHeight + 620);
	// THIS IS A LINE TO DRAW A VERTICAL LINE AT THE START TO FORM A BOUNDARY
	pWind->SetPen(MEDIUMPURPLE, 3);
	pWind->DrawLine(1, UI.ToolBarHeight + 540, UI.width - 999, UI.ToolBarHeight + 620);
	// THIS IS A LINE TO DRAW A VERTICAL LINE AT THE END TO FORM A BOUNDARY
	pWind->SetPen(MEDIUMPURPLE, 3);
	pWind->DrawLine(985, UI.ToolBarHeight + 540, UI.width - 15, UI.ToolBarHeight + 620);
}


//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void Output::CreateSimulationToolBar() const
{
	UI.AppMode = SIMULATION;

	//Clear the toolbar area
	pWind->SetPen(BLACK);
	pWind->SetBrush(LIGHTCYAN);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

	//Prepare List of images for simulation menu items
	string SimItemImages[ITM_SIM_CNT];
	SimItemImages[ITM_SIM] = "images\\Menu\\SIM.jpg";
	SimItemImages[ITM_TRUTH] = "images\\Menu\\TRUTH.jpg";
	SimItemImages[ITM_MENU] = "images\\Menu\\MENU.jpg";
	SimItemImages[ITM_PROBE] = "images\\Menu\\PROBE.jpg";

	//Draw simulation menu items
	for (int i = 0; i < ITM_SIM_CNT; i++)
	{
		pWind->DrawImage(SimItemImages[i], i * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);
	}

	//Draw a line under the toolbar
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//
void Output::DrawBUFF1(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\BUFFH.jpg";
	else
		GateImage = "Images\\Gates\\BUFF.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);

}

void Output::DrawINV1(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\NOTH.jpg";
	else
		GateImage = "Images\\Gates\\NOT.jpg";

	//Draw NOT1 Gate at Gfx_Info (1st corner)
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}
void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\ANDH.jpg";
	else
		GateImage = "Images\\Gates\\AND.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\ORH.jpg";
	else
		GateImage = "Images\\Gates\\OR.jpg";

	//Draw OR2 Gate at Gfx_Info (1st corner)
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}



void Output::DrawNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\NORH.jpg";
	else
		GateImage = "Images\\Gates\\NOR.jpg";

	//Draw NOR2 Gate at Gfx_Info (1st corner)
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\NANDH.jpg";
	else
		GateImage = "Images\\Gates\\NAND.jpg";

	//Draw NAND2 Gate at Gfx_Info (1st corner)
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}


void Output::DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\XNORH.jpg";
	else
		GateImage = "Images\\Gates\\XNOR.jpg";

	//Draw XNOR2 Gate at Gfx_Info (1st corner)
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\XORH.jpg";
	else
		GateImage = "Images\\Gates\\XOR.jpg";

	//Draw XOR2 Gate at Gfx_Info (1st corner)
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}


void Output::DrawAND3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\AND3H.jpg";
	else
		GateImage = "Images\\Gates\\AND3.jpg";

	//Draw AND3 Gate at Gfx_Info (1st corner)
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\NOR3H.jpg";
	else
		GateImage = "Images\\Gates\\NOR3.jpg";

	//Draw NOR3 Gate at Gfx_Info (1st corner)
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\XOR3H.jpg";
	else
		GateImage = "Images\\Gates\\XOR3.jpg";

	//Draw XOR3 Gate at Gfx_Info (1st corner)
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DRAWSWITCH(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\SWITCH-ON.jpg";
	else
		GateImage = "Images\\Gates\\SWITCH.jpg";

	//Draw SWITCH (ON/OFF) at Gfx_Info (1st corner)
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

// Draws LED and user can choose color of LED incase it's ON and if user doesn't choose color, RED is default
void Output::DRAWLED(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\LEDH.jpg";
	else
		GateImage = "Images\\Gates\\LED.jpg";

	//Draw LED at Gfx_Info (1st corner)
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}


void Output::DrawConnection(GraphicsInfo r_GfxInfo, bool selected) const
{
	if (selected)
		pWind->SetPen(RED, 2);  // Blue and thicker when selected
	else
		pWind->SetPen(BLACK, 2);  // Black normal thickness

	// Get start and end points
	int x1 = r_GfxInfo.x1;  // Source (output pin on right)
	int y1 = r_GfxInfo.y1;
	int x2 = r_GfxInfo.x2;  // Destination (input pin on left)
	int y2 = r_GfxInfo.y2;

	// Draw with horizontal and vertical lines only
	// Strategy: Go horizontal first, then vertical

	// Calculate middle X point (halfway between source and destination)
	int midX = (x1 + x2) / 2;

	// Draw three segments:
	// 1. Horizontal line from source to middle
	pWind->DrawLine(x1, y1, midX, y1);

	// 2. Vertical line from middle at y1 to middle at y2
	pWind->DrawLine(midX, y1, midX, y2);

	// 3. Horizontal line from middle to destination
	pWind->DrawLine(midX, y2, x2, y2);

	// Reset pen
	pWind->SetPen(BLACK, 1);

}
// DRAW HORIZANTAL CONNECTION NO  CHANGE IN Y COORDINATE
void Output::DrawConnectionH(GraphicsInfo r_GfxInfo, bool selected) const

{
	if (selected)
		pWind->SetPen(BLUE, 2);  // Blue and thicker when selected
	else
		pWind->SetPen(BLACK, 1);     // Red and normal when not selected

	//Draw the connection line from (x1,y1) to (x2,y1)
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x2, r_GfxInfo.y1);


}


// DRAW VERTICAL CONNECTION NO  CHANGE IN X COORDINATE
void Output::DrawConnectionV(GraphicsInfo r_GfxInfo, bool selected) const
{
	if (selected)
		pWind->SetPen(BLUE, 2);
	else
		pWind->SetPen(BLACK, 1);

	//Draw the connection line from (x1,y1) to (x2,y2)
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x1, r_GfxInfo.y2);
}

void Output::DrawText(int x, int y, string text) const
{
	pWind->SetPen(BLACK);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(x, y, text);
}

Output::~Output()
{
	delete pWind;
}