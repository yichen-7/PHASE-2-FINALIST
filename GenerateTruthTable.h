#ifndef _GENERATE_TRUTH_TABLE_H
#define _GENERATE_TRUTH_TABLE_H

#include "Actions/Action.h"
#include <vector>
#include <string>
using namespace std;

class SWITCH;
class LED;

class GenerateTruthTable : public Action
{
private:
	vector<SWITCH*> m_Switches;  // List of all switches (inputs)
	vector<LED*> m_LEDs;          // List of all LEDs (outputs)
	int m_InputCount;
	int m_OutputCount;

	// Helper methods
	void CollectSwitchesAndLEDs();
	void GenerateAndDisplay();
	void GenerateAndSaveToFile();
	void SetSwitchCombination(int combination);
	string GetTruthTableString();
	void DisplayTruthTableInDrawingArea();

public:
	GenerateTruthTable(ApplicationManager* pApp);
	virtual ~GenerateTruthTable();

	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

#endif