#ifndef _EDIT_LABEL_H
#define _EDIT_LABEL_H

#include "Actions/Action.h"
#include "ApplicationManager.h"

class EditLabel : public Action
{
private:
	int Cx, Cy;  // Position where user clicks
	string newLabel;  // New label to set

public:
	EditLabel(ApplicationManager* pApp);
	virtual ~EditLabel(void);

	// Reads parameters required for action to execute
	virtual void ReadActionParameters();

	// Execute action (edits label of selected component)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif
