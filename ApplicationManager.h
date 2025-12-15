#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include "Actions\Action.h"
#include "Components\Component.h"

//Main class that manages everything in the application.
class ApplicationManager
{

	enum { MaxCompCount = 200 };	//Max no of Components	

private:
	int CompCount;		//Actual number of Components
	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)
	Output* OutputInterface; //pointer to the Output Clase Interface
	Input* InputInterface; //pointer to the Input Clase Interface

	// --- MULTIPLE SELECTION: List of selected components ---
	Component* m_SelectedComponents[MaxCompCount];
	int m_SelectedCount;
	// --- NEW MEMBER: Selected Component Pointer ---
	Component* m_SelectedComponent;

	// --- NEW: Clipboard for Copy/Cut/Paste ---
	Component* m_Clipboard;      // stores a prototype (clone) or the cut object
	bool m_ClipboardIsCut;       // true if clipboard holds a cut object

public:
	ApplicationManager(); //constructor

	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();

	//Creates an action and executes it
	void ExecuteAction(ActionType);

	void UpdateInterface();	//Redraws all the drawing window

	//Gets a pointer to Input / Output Object
	Output* GetOutput();
	Input* GetInput();

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);

	//Finds the component at the specified coordinates (x, y)
	Component* GetComponentAt(int x, int y);

	//Deletes a specific component from the list
	void DeleteComponent(Component* pComp);
	Component* GetComponentAt(int x, int y) const;

	// --- MULTIPLE SELECTION FUNCTIONS ---
	void AddToSelection(Component* pComp);
	void RemoveFromSelection(Component* pComp);
	void ClearSelection();
	bool IsSelected(Component* pComp) const;
	int GetSelectedCount() const { return m_SelectedCount; }
	Component** GetSelectedComponents() { return m_SelectedComponents; }

	int GetComponentCount() const { return CompCount; }
	Component** GetComponentList() { return CompList; }

	// --- NEW FUNCTIONS: Selected Component Accessors ---
	Component* GetSelectedComponent() const { return m_SelectedComponent; }
	void SetSelectedComponent(Component* pComp) { m_SelectedComponent = pComp; }

	// --- NEW: Clipboard API ---
	void CopyComponent(Component* pComp);
	void CutComponent(Component* pComp);
	void PasteAt(int x, int y);
	void ClearClipboard();

	// --- CIRCUIT VALIDATION FOR SIMULATION MODE ---
	bool ValidateCircuit(string& errorMsg);
	bool HasSwitches();
	bool HasLEDs();
	bool AllInputsConnected(string& errorMsg);

	// --- SIGNAL PROPAGATION FOR SIMULATION ---
	void PropagateSignal();
	void ClearAllComponents();
	// --- BOUNDARY VALIDATION ---
	bool IsValidPlacement(int x, int y, int width, int height) const;
	//destructor
	~ApplicationManager();
};

#endif