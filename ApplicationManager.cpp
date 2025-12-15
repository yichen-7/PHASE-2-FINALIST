#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddORgate2.h"
#include "AddNANDgate2.h"
#include "AddNORgate2.h"
#include "AddXORgate2.h"
#include "AddXNORgate2.h"
#include "AddINVgate1.h"
#include "AddBUFFgate1.h"
#include "AddANDgate3.h"
#include "AddXORgate3.h"
#include "AddNORgate3.h"
#include "AddLED.h"
#include "AddSWITCH.h"
#include "Delete.h"
#include "AddConnection.h"
#include "EditLabel.h"
#include "Components/Connection.h"
#include "MOVE.h"
#include "SELECT.h"
#include "Copy.h" 
#include "Cut.h"    
#include "Paste.h"
#include "simmode.h"
#include "DESIGNmode.h"
#include "SimCirc.h"  
#include "Components\Gate.h"          
#include "LED.h"                       
#include "SWITCH.h"  
#include "PROBE.h"  
#include "GenerateTruthTable.h"

using namespace std;
ApplicationManager::ApplicationManager()
{
	CompCount = 0;

	for (int i = 0; i < MaxCompCount; i++)
		CompList[i] = NULL;
	// --- NEW INITIALIZATION ---
	m_SelectedComponent = nullptr;
	m_Clipboard = nullptr;
	m_ClipboardIsCut = false;
	// --- INITIALIZE SELECTION LIST ---
	m_SelectedCount = 0;
	for (int i = 0; i < MaxCompCount; i++)
		m_SelectedComponents[i] = NULL;

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
	// --- NEW INITIALIZATION ---
	m_SelectedComponent = nullptr;
	m_Clipboard = nullptr;
	m_ClipboardIsCut = false;

}

// Add these new methods at the end of the file (before destructor):

void ApplicationManager::AddToSelection(Component* pComp)
{
	if (!pComp) return;

	// Check if already selected
	if (IsSelected(pComp)) return;

	// Add to selection list
	if (m_SelectedCount < MaxCompCount)
	{
		m_SelectedComponents[m_SelectedCount++] = pComp;
		pComp->SetSelected(true);
	}
}
bool ApplicationManager::IsValidPlacement(int x, int y, int width, int height) const
{
	// Calculate component boundaries
	int x1 = x - width / 2;
	int x2 = x + width / 2;
	int y1 = y - height / 2;
	int y2 = y + height / 2;

	// Check if component is fully within drawing area
	if (x1 < 0 || x2 >1000)
		return false;

	if (y1 < 80 || y2 > 620)
		return false;

	return true;
}


void ApplicationManager::RemoveFromSelection(Component* pComp)
{
	if (!pComp) return;

	// Find the component in selection list
	int index = -1;
	for (int i = 0; i < m_SelectedCount; i++)
	{
		if (m_SelectedComponents[i] == pComp)
		{
			index = i;
			break;
		}
	}

	if (index == -1) return; // Not found

	// Remove from list by shifting
	for (int i = index; i < m_SelectedCount - 1; i++)
		m_SelectedComponents[i] = m_SelectedComponents[i + 1];

	m_SelectedComponents[m_SelectedCount - 1] = NULL;
	m_SelectedCount--;

	pComp->SetSelected(false);
}

void ApplicationManager::ClearSelection()
{
	// Unselect all components
	for (int i = 0; i < m_SelectedCount; i++)
	{
		if (m_SelectedComponents[i])
			m_SelectedComponents[i]->SetSelected(false);
		m_SelectedComponents[i] = NULL;
	}
	m_SelectedCount = 0;
}
bool ApplicationManager::HasSwitches()
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] != NULL)
		{
			// Check if component is a SWITCH
			SWITCH* sw = dynamic_cast<SWITCH*>(CompList[i]);
			if (sw != NULL)
				return true;
		}
	}
	return false;
}

bool ApplicationManager::HasLEDs()
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] != NULL)
		{
			// Check if component is an LED
			LED* led = dynamic_cast<LED*>(CompList[i]);
			if (led != NULL)
				return true;
		}
	}
	return false;
}
bool ApplicationManager::AllInputsConnected(string& errorMsg)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] != NULL)
		{
			// Skip switches (they have no inputs)
			SWITCH* sw = dynamic_cast<SWITCH*>(CompList[i]);
			if (sw != NULL)
				continue;

			// Skip connections (they're not components with pins)
			Connection* conn = dynamic_cast<Connection*>(CompList[i]);
			if (conn != NULL)
				continue;

			// Check all input pins of this component
			int inputCount = CompList[i]->GetInputPinCount();

			for (int j = 0; j < inputCount; j++)
			{
				InputPin* pin = CompList[i]->GetInputPin(j);

				if (pin != NULL && pin->getConnection() == NULL)
				{
					// Found an unconnected input pin!
					string label = CompList[i]->GetLabel();
					if (label != "")
						errorMsg = "Component '" + label + "' has unconnected input pin!";
					else
						errorMsg = "A component has unconnected input pin!";

					return false;
				}
			}
		}
	}
	return true;  // All inputs are connected
}
bool ApplicationManager::ValidateCircuit(string& errorMsg)
{
	// Step 1: Check if circuit is empty
	if (CompCount == 0)
	{
		errorMsg = "Circuit is empty! Add components first.";
		return false;
	}

	// Step 2: Check for at least one switch
	if (!HasSwitches())
	{
		errorMsg = "No switches found! Add at least one switch.";
		return false;
	}

	// Step 3: Check for at least one LED
	if (!HasLEDs())
	{
		errorMsg = "No LEDs found! Add at least one LED.";
		return false;
	}

	// Step 4: Check all inputs are connected
	if (!AllInputsConnected(errorMsg))
	{
		// errorMsg already set by AllInputsConnected
		return false;
	}

	// All validation checks passed!
	errorMsg = "Circuit is valid!";
	return true;
}
bool ApplicationManager::IsSelected(Component* pComp) const
{
	if (!pComp) return false;

	for (int i = 0; i < m_SelectedCount; i++)
	{
		if (m_SelectedComponents[i] == pComp)
			return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;
}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return InputInterface->GetUserAction();
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	switch (ActType)
	{
	case ADD_AND_GATE_2:
		pAct = new AddANDgate2(this);
		break;
	case ADD_OR_GATE_2:
		pAct = new AddORgate2(this);
		break;
	case ADD_NAND_GATE_2:
		pAct = new AddNANDgate2(this);
		break;
	case ADD_NOR_GATE_2:
		pAct = new AddNORgate2(this);
		break;
	case ADD_XOR_GATE_2:
		pAct = new AddXORgate2(this);
		break;
	case ADD_XNOR_GATE_2:
		pAct = new AddXNORgate2(this);
		break;
	case ADD_INV:
		pAct = new AddINVgate1(this);
		break;
	case ADD_Buff:
		pAct = new AddBUFFgate1(this);
		break;
	case ADD_AND_GATE_3:
		pAct = new AddANDgate3(this);
		break;
	case ADD_XOR_GATE_3:
		pAct = new AddXORgate3(this);
		break;
	case ADD_NOR_GATE_3:
		pAct = new AddNORgate3(this);
		break;
	case ADD_LED:
		pAct = new AddLED(this);
		break;
	case ADD_Switch:
		pAct = new AddSWITCH(this);
		break;
	case MOVE:
		pAct = new Move(this);
		break;

	case DEL:
		pAct = new Delete(this);
		break;

	case ADD_CONNECTION:
		pAct = new AddConnection(this);
		break;
	case EDIT_Label:
		pAct = new EditLabel(this);
		break;
	case SELECT:
		pAct = new Select(this);
		break;
	case COPY:
		pAct = new Copy(this);
		break;
	case CUT:
		pAct = new Cut(this);
		break;
	case PASTE:
		pAct = new Paste(this);
		break;
	case SIM_MODE:
		pAct = new SwitchToSimMode(this);
		break;
	case DSN_MODE:
		pAct = new SwitchToDesignMode(this);
		break;
	case Change_Switch:
		pAct = new SimulateCircuit(this);
		break;
	case PROBE:
		pAct = new ProbeCircuit(this);
		break;
	case Create_TruthTable:
		pAct = new GenerateTruthTable(this);
		break;

	case EXIT:
		///TODO: create ExitAction here
		break;
	}
	if (pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}

void ApplicationManager::UpdateInterface()
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] != NULL)
			CompList[i]->Draw(OutputInterface);
	}
}
////////////////////////////////////////////////////////////////////
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}

////////////////////////////////////////////////////////////////////
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}
void ApplicationManager::PropagateSignal()
{
	// Multi-level circuit requires multiple propagation passes
	// We'll iterate until no changes occur (signals stabilize)

	const int MAX_ITERATIONS = 100;  // Prevent infinite loops

	for (int iteration = 0; iteration < MAX_ITERATIONS; iteration++)
	{
		bool changed = false;

		// Step 1: Propagate through all connections
		for (int i = 0; i < CompCount; i++)
		{
			if (CompList[i] != NULL)
			{
				Connection* conn = dynamic_cast<Connection*>(CompList[i]);
				if (conn != NULL)
				{
					OutputPin* srcPin = conn->getSourcePin();
					InputPin* dstPin = conn->getDestPin();

					if (srcPin && dstPin)
					{
						STATUS oldStatus = dstPin->getStatus();
						STATUS newStatus = srcPin->getStatus();

						if (oldStatus != newStatus)
						{
							dstPin->setStatus(newStatus);
							changed = true;
						}
					}
				}
			}
		}

		// Step 2: Make all gates operate
		for (int i = 0; i < CompCount; i++)
		{
			if (CompList[i] != NULL)
			{
				// Skip switches
				SWITCH* sw = dynamic_cast<SWITCH*>(CompList[i]);
				if (sw != NULL) continue;

				// Skip LEDs
				LED* led = dynamic_cast<LED*>(CompList[i]);
				if (led != NULL) continue;

				// Skip connections
				Connection* conn = dynamic_cast<Connection*>(CompList[i]);
				if (conn != NULL) continue;

				// This is a gate - check if output will change
				Gate* gate = dynamic_cast<Gate*>(CompList[i]);
				if (gate != NULL)
				{
					int oldOutput = gate->GetOutPinStatus();  // int, not STATUS
					gate->Operate();  // Calculate new output
					int newOutput = gate->GetOutPinStatus();  // int, not STATUS

					if (oldOutput != newOutput)
						changed = true;
				}
			}
		}

		// If nothing changed, circuit is stable
		if (!changed)
			break;
	}
}
////////////////////////////////////////////////////////////////////
Component* ApplicationManager::GetComponentAt(int x, int y)
{
	// Loop through all components from top to bottom (reverse order)
	// This ensures we get the component drawn on top if overlapping
	for (int i = CompCount - 1; i >= 0; i--)
	{
		if (CompList[i] != NULL)
		{
			// Check if the click is inside this component's boundaries
			if (CompList[i]->IsInside(x, y))
			{
				return CompList[i];
			}
		}
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////
void ApplicationManager::DeleteComponent(Component* pComp)
{
	if (pComp == NULL) return;

	// Check if the component to delete is itself a Connection
	Connection* targetConn = dynamic_cast<Connection*>(pComp);

	if (targetConn)
	{
		// It's a connection - just delete it and clean up pins
		OutputPin* sPin = targetConn->getSourcePin();
		InputPin* dPin = targetConn->getDestPin();

		// Deregister from source output pin
		if (sPin)
		{
			sPin->RemoveConnection(targetConn);
		}

		// Deregister from destination input pin
		if (dPin)
		{
			dPin->setConnection(nullptr);
		}

		// Remove from list
		for (int i = 0; i < CompCount; i++)
		{
			if (CompList[i] == targetConn)
			{
				delete CompList[i];

				// Shift remaining components
				for (int j = i; j < CompCount - 1; j++)
					CompList[j] = CompList[j + 1];

				CompList[CompCount - 1] = NULL;
				CompCount--;
				return; // Done!
			}
		}
	}
	else
	{
		// It's a gate/LED/switch - delete all connections referencing it first
		for (int i = 0; i < CompCount; /*increment inside*/)
		{
			Connection* conn = dynamic_cast<Connection*>(CompList[i]);
			if (conn)
			{
				OutputPin* sPin = conn->getSourcePin();
				InputPin* dPin = conn->getDestPin();

				bool refersToTarget = false;
				if (sPin && sPin->getComponent() == pComp) refersToTarget = true;
				if (dPin && dPin->getComponent() == pComp) refersToTarget = true;

				if (refersToTarget)
				{
					// Deregister connection from source output pin (if any)
					if (sPin)
					{
						sPin->RemoveConnection(conn);
					}

					// Deregister connection from destination input pin (if any)
					if (dPin)
					{
						dPin->setConnection(nullptr);
					}

					// Delete connection component and compact list
					delete CompList[i];
					for (int j = i; j < CompCount - 1; j++)
						CompList[j] = CompList[j + 1];
					CompList[CompCount - 1] = NULL;
					CompCount--;
					continue; // stay on same index because list shifted
				}
			}
			i++;
		}

		// Now delete the gate/LED/switch itself
		for (int i = 0; i < CompCount; i++)
		{
			if (CompList[i] == pComp)
			{
				delete CompList[i];

				// Shift remaining
				for (int j = i; j < CompCount - 1; j++)
					CompList[j] = CompList[j + 1];

				CompList[CompCount - 1] = NULL;
				CompCount--;
				break;
			}
		}
	}
}
void ApplicationManager::CopyComponent(Component* pComp)
{
	if (!pComp) {
		GetOutput()->PrintMsg("No component selected to copy");
		return;
	}

	// Clear any existing clipboard prototype
	if (m_Clipboard) { delete m_Clipboard; m_Clipboard = nullptr; m_ClipboardIsCut = false; }

	m_Clipboard = pComp->Clone();
	m_ClipboardIsCut = false;
	GetOutput()->PrintMsg("Component copied");
}

void ApplicationManager::CutComponent(Component* pComp)
{
	if (!pComp) {
		GetOutput()->PrintMsg("No component selected to cut");
		return;
	}

	// Clear any existing clipboard prototype
	if (m_Clipboard) { delete m_Clipboard; m_Clipboard = nullptr; m_ClipboardIsCut = false; }

	// Store a prototype clone (we will move the stored clone into the canvas on paste)
	m_Clipboard = pComp->Clone();
	m_ClipboardIsCut = true;

	// Remove the original and its connections
	DeleteComponent(pComp);

	GetOutput()->PrintMsg("Component cut");
}

void ApplicationManager::PasteAt(int x, int y)
{
	if (!m_Clipboard) {
		GetOutput()->PrintMsg("Clipboard empty");
		return;
	}

	if (m_ClipboardIsCut)
	{
		// Move the clipped object into the canvas at (x,y)
		int centerX = (m_Clipboard->GetX1() + m_Clipboard->GetX2()) / 2;
		int centerY = (m_Clipboard->GetY1() + m_Clipboard->GetY2()) / 2;
		int dx = x - centerX;
		int dy = y - centerY;
		m_Clipboard->Move(dx, dy);

		// Add the actual stored object to the components list and clear clipboard
		AddComponent(m_Clipboard);
		m_Clipboard = nullptr;
		m_ClipboardIsCut = false;
		GetOutput()->PrintMsg("Component pasted (cut)");
	}
	else
	{
		// Create a fresh clone from the prototype and add it
		Component* newC = m_Clipboard->Clone();
		int centerX = (newC->GetX1() + newC->GetX2()) / 2;
		int centerY = (newC->GetY1() + newC->GetY2()) / 2;
		int dx = x - centerX;
		int dy = y - centerY;
		newC->Move(dx, dy);
		AddComponent(newC);
		GetOutput()->PrintMsg("Component pasted (copy)");
	}
}

void ApplicationManager::ClearClipboard()
{
	if (m_Clipboard) { delete m_Clipboard; m_Clipboard = nullptr; m_ClipboardIsCut = false; }
}

////////////////////////////////////////////////////////////////////
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;
}
////////////////////////////////////////////////////////////////////
Component* ApplicationManager::GetComponentAt(int x, int y) const
{
	// Loop through all components from top to bottom (reverse order)
	for (int i = CompCount - 1; i >= 0; i--)
	{
		if (CompList[i] != NULL && CompList[i]->IsInside(x, y))
			return CompList[i];
	}
	return nullptr;
}