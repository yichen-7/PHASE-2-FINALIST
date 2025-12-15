#include "GenerateTruthTable.h"
#include "ApplicationManager.h"
#include "Components\Component.h"
#include "SWITCH.h"
#include "LED.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

GenerateTruthTable::GenerateTruthTable(ApplicationManager* pApp) : Action(pApp)
{
	m_InputCount = 0;
	m_OutputCount = 0;
}

GenerateTruthTable::~GenerateTruthTable()
{
}

void GenerateTruthTable::ReadActionParameters()
{
	// No parameters needed
	Output* pOut = pManager->GetOutput();
	pOut->PrintMsg("Generating Truth Table...");
}

void GenerateTruthTable::CollectSwitchesAndLEDs()
{
	m_Switches.clear();
	m_LEDs.clear();

	Component** compList = pManager->GetComponentList();
	int compCount = pManager->GetComponentCount();

	// Collect all switches and LEDs
	for (int i = 0; i < compCount; i++)
	{
		if (compList[i] != NULL)
		{
			SWITCH* sw = dynamic_cast<SWITCH*>(compList[i]);
			if (sw != NULL)
			{
				m_Switches.push_back(sw);
			}

			LED* led = dynamic_cast<LED*>(compList[i]);
			if (led != NULL)
			{
				m_LEDs.push_back(led);
			}
		}
	}

	m_InputCount = m_Switches.size();
	m_OutputCount = m_LEDs.size();
}

void GenerateTruthTable::SetSwitchCombination(int combination)
{
	// Set each switch based on the binary representation of 'combination'
	// For example: combination = 5 (binary: 101)
	// Switch 0 = 1, Switch 1 = 0, Switch 2 = 1

	for (int i = 0; i < m_InputCount; i++)
	{
		// Check if bit i is set in combination
		bool bitSet = (combination & (1 << i)) != 0;

		// Set switch to HIGH or LOW accordingly
		if (bitSet)
		{
			// Make sure switch is ON (HIGH)
			if (m_Switches[i]->GetOutPinStatus() == LOW)
				m_Switches[i]->Toggle();
		}
		else
		{
			// Make sure switch is OFF (LOW)
			if (m_Switches[i]->GetOutPinStatus() == HIGH)
				m_Switches[i]->Toggle();
		}
	}
}

string GenerateTruthTable::GetTruthTableString()
{
	stringstream ss;

	// Calculate number of rows (2^n where n is number of inputs)
	int numRows = (int)pow(2.0, m_InputCount);

	// Header: Switch labels or default names
	for (int i = 0; i < m_InputCount; i++)
	{
		string label = m_Switches[i]->GetLabel();
		if (label == "")
			label = "IN" + to_string(i);

		ss << setw(8) << label;
	}

	ss << " | ";

	// Output labels
	for (int i = 0; i < m_OutputCount; i++)
	{
		string label = m_LEDs[i]->GetLabel();
		if (label == "")
			label = "OUT" + to_string(i);

		ss << setw(8) << label;
	}

	ss << "\n";

	// Separator line
	for (int i = 0; i < m_InputCount; i++)
		ss << "--------";
	ss << "-+-";
	for (int i = 0; i < m_OutputCount; i++)
		ss << "--------";
	ss << "\n";

	// Generate all combinations
	for (int row = 0; row < numRows; row++)
	{
		// Set switches to this combination
		SetSwitchCombination(row);

		// Propagate signals through circuit
		pManager->PropagateSignal();

		// Print input values
		for (int i = 0; i < m_InputCount; i++)
		{
			int status = m_Switches[i]->GetOutPinStatus();
			ss << setw(8) << (status == HIGH ? "1" : "0");
		}

		ss << " | ";

		// Print output values
		for (int i = 0; i < m_OutputCount; i++)
		{
			int status = m_LEDs[i]->GetInputPinStatus(1);
			ss << setw(8) << (status == HIGH ? "1" : "0");
		}

		ss << "\n";
	}

	return ss.str();
}

void GenerateTruthTable::GenerateAndDisplay()
{
	Output* pOut = pManager->GetOutput();

	// Generate truth table string
	string truthTable = GetTruthTableString();

	// Show summary
	stringstream summary;
	summary << "Truth Table Generated! Inputs: " << m_InputCount
		<< ", Outputs: " << m_OutputCount
		<< ", Rows: " << (int)pow(2.0, m_InputCount);

	pOut->PrintMsg(summary.str());

	// Also show in console for testing
	cout << "\n=== TRUTH TABLE ===\n";
	cout << truthTable;
	cout << "==================\n\n";
}

void GenerateTruthTable::GenerateAndSaveToFile()
{
	Output* pOut = pManager->GetOutput();

	// Generate truth table string
	string truthTable = GetTruthTableString();

	// Save to file
	ofstream outFile("TruthTable.txt");

	if (outFile.is_open())
	{
		outFile << "=== TRUTH TABLE ===\n";
		outFile << "Circuit: " << m_InputCount << " inputs, "
			<< m_OutputCount << " outputs\n";
		outFile << "Total Rows: " << (int)pow(2.0, m_InputCount) << "\n\n";
		outFile << truthTable;
		outFile << "\n===================\n";
		outFile.close();

		// Don't print message here, will be shown later
	}
	else
	{
		pOut->PrintMsg("Error: Could not save truth table to file");
	}
}

void GenerateTruthTable::DisplayTruthTableInDrawingArea()
{
	Output* pOut = pManager->GetOutput();

	// Clear drawing area to show truth table
	pOut->ClearDrawingArea();

	// Calculate positions for table display
	int startX = 100;
	int startY = 150;
	int rowHeight = 30;
	int colWidth = 80;

	// Calculate number of rows
	int numRows = (int)pow(2.0, m_InputCount);
	int maxDisplayRows = 16;  // Maximum rows to display on screen

	// Draw title
	pOut->DrawText(startX, startY - 50, "=== TRUTH TABLE ===");

	// Draw header row
	int x = startX;

	// Input headers
	for (int i = 0; i < m_InputCount; i++)
	{
		string label = m_Switches[i]->GetLabel();
		if (label == "")
			label = "IN" + to_string(i);

		pOut->DrawText(x, startY, label);
		x += colWidth;
	}

	// Separator column
	pOut->DrawText(x, startY, "||");
	x += colWidth;

	// Output headers
	for (int i = 0; i < m_OutputCount; i++)
	{
		string label = m_LEDs[i]->GetLabel();
		if (label == "")
			label = "OUT" + to_string(i);

		pOut->DrawText(x, startY, label);
		x += colWidth;
	}

	// Draw separator line (visual)
	string separator = "";
	for (int i = 0; i < (m_InputCount + m_OutputCount + 1); i++)
		separator += "----------";
	pOut->DrawText(startX, startY + 20, separator);

	// Draw data rows
	int y = startY + 50;
	int displayRows = min(numRows, maxDisplayRows);

	for (int row = 0; row < displayRows; row++)
	{
		// Set switches to this combination
		SetSwitchCombination(row);

		// Propagate signals
		pManager->PropagateSignal();

		x = startX;

		// Draw input values
		for (int i = 0; i < m_InputCount; i++)
		{
			int status = m_Switches[i]->GetOutPinStatus();
			pOut->DrawText(x, y, status == HIGH ? "  1" : "  0");
			x += colWidth;
		}

		// Separator
		pOut->DrawText(x, y, "||");
		x += colWidth;

		// Draw output values
		for (int i = 0; i < m_OutputCount; i++)
		{
			int status = m_LEDs[i]->GetInputPinStatus(1);
			pOut->DrawText(x, y, status == HIGH ? "  1" : "  0");
			x += colWidth;
		}

		y += rowHeight;
	}

	// Show message about file save
	string infoMsg = "Truth table displayed above. ";
	if (numRows > maxDisplayRows)
		infoMsg += "Showing first " + to_string(maxDisplayRows) + " of " + to_string(numRows) + " rows. ";
	infoMsg += "Full table saved to TruthTable.txt. Click anywhere to continue...";

	pOut->PrintMsg(infoMsg);

	// Wait for user to click before continuing
	Input* pIn = pManager->GetInput();
	int tempX, tempY;
	pIn->GetPointClicked(tempX, tempY);

	// Clear and restore normal view
	pOut->ClearDrawingArea();
	pManager->UpdateInterface();
}

void GenerateTruthTable::Execute()
{
	ReadActionParameters();

	Output* pOut = pManager->GetOutput();

	// Validate circuit first
	string errorMsg;
	if (!pManager->ValidateCircuit(errorMsg))
	{
		pOut->PrintMsg("Cannot generate truth table: " + errorMsg);
		return;
	}

	// Collect all switches and LEDs
	CollectSwitchesAndLEDs();

	// Validate we have inputs and outputs
	if (m_InputCount == 0)
	{
		pOut->PrintMsg("Error: No switches found in circuit!");
		return;
	}

	if (m_OutputCount == 0)
	{
		pOut->PrintMsg("Error: No LEDs found in circuit!");
		return;
	}

	// Always save to file first
	GenerateAndSaveToFile();

	// Check if we can display on screen (5 or fewer inputs)
	if (m_InputCount <= 5)
	{
		// Display visually in the drawing area
		DisplayTruthTableInDrawingArea();
	}
	else
	{
		// Too many rows, just inform user about file
		stringstream msg;
		int numRows = (int)pow(2.0, m_InputCount);
		msg << "Circuit has " << m_InputCount << " inputs ("
			<< numRows << " rows). Truth table saved to TruthTable.txt";
		pOut->PrintMsg(msg.str());
	}

	// Restore original switch states (all OFF)
	for (int i = 0; i < m_InputCount; i++)
	{
		if (m_Switches[i]->GetOutPinStatus() == HIGH)
			m_Switches[i]->Toggle();
	}

	// Propagate to restore circuit
	pManager->PropagateSignal();

	// Final redraw
	pOut->ClearDrawingArea();
	pManager->UpdateInterface();
}

void GenerateTruthTable::Undo()
{
	// Cannot undo truth table generation
}

void GenerateTruthTable::Redo()
{
	// Cannot redo truth table generation
}