#pragma once
#include "..\Defs.h"
#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:
	window* pWind;	//Pointer to the Graphics Window

public:
	Output(); // Performs the Window Initialization
	Input* CreateInput() const; //creates a pointer to the Input object
	void ChangeTitle(string Title) const;

	void CreateDesignToolBar() const;	//Tool bar of the design mode
	void CreateSimulationToolBar() const;//Tool bar of the simulation mode
	void CreateStatusBar() const;	//Create Status bar

	void ClearStatusBar() const;		//Clears the status bar
	void ClearDrawingArea() const;	//Clears the drawing area

	window* CreateWind(int wd, int h, int x, int y) const; //Creates user interface window

	void DrawBUFF1(GraphicsInfo r_GfxInfo, bool selected = false) const;

	// Draws 2-input AND gate
	void DrawAND2(GraphicsInfo r_GfxInfo, bool selected = false) const;

	// Draws 2-input OR gate
	void DrawOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;

	// Draws 1-input NOT gate
	void DrawINV1(GraphicsInfo r_GfxInfo, bool selected = false) const;

	// Draws 2-input XOR gate
	void DrawXOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;

	// Draws 2-input NOR gate
	void DrawNOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;

	// Draws 2-input NAND gate
	void DrawNAND2(GraphicsInfo r_GfxInfo, bool selected = false) const;

	// Draws 2-input XNOR gate
	void DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;

	// Draws 3-INPUT AND
	void DrawAND3(GraphicsInfo r_GfxInfo, bool selected = false) const;

	// Draws 3-INPUT AND
	void DrawNOR3(GraphicsInfo r_GfxInfo, bool selected = false) const;

	// Draws 3-INPUT AND
	void DrawXOR3(GraphicsInfo r_GfxInfo, bool selected = false) const;

	// Draws switch
	void DRAWSWITCH(GraphicsInfo r_GfxInfo, bool selected = false) const;

	// Draws LED
	void DRAWLED(GraphicsInfo r_GfxInfo, bool selected = false) const;

	// Draws Connection
	void DrawConnection(GraphicsInfo r_GfxInfo, bool selected = false) const;
	// Draws HORIZANTAL Connection
	void DrawConnectionH(GraphicsInfo r_GfxInfo, bool selected = false) const;
	// Draws VERTICAL Connection
	void DrawConnectionV(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawText(int x, int y, string text) const; // Draws Text
	void PrintMsg(string msg) const;	//Print a message on Status bar


	~Output();
};