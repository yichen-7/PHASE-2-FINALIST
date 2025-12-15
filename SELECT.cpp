#include "SELECT.h"
#include "ApplicationManager.h"
#include "GUI/Input.h"
#include "GUI/Output.h"

Select::Select(ApplicationManager* pApp) : Action(pApp)
{
}

Select::~Select()
{
}

void Select::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Click on components to select/unselect them (multiple selection enabled)");
    pIn->GetPointClicked(Cx, Cy);
    pOut->ClearStatusBar();
}

void Select::Execute()
{
    ReadActionParameters();

    // Find component at clicked position
    Component* pComp = pManager->GetComponentAt(Cx, Cy);

    Output* pOut = pManager->GetOutput();

    if (pComp != nullptr)
    {
        // Toggle selection for this component
        if (pManager->IsSelected(pComp))
        {
            // Already selected - unselect it
            pManager->RemoveFromSelection(pComp);
            pOut->PrintMsg("Component unselected");
        }
        else
        {
            // Not selected - add to selection
            pManager->AddToSelection(pComp);

            int count = pManager->GetSelectedCount();
            if (count == 1)
                pOut->PrintMsg("1 component selected");
            else
                pOut->PrintMsg(to_string(count) + " components selected");
        }
    }
    else
    {
        // Clicked on empty space - clear all selections
        pManager->ClearSelection();
        pOut->PrintMsg("All selections cleared");
    }

    // Redraw to show selection changes
    pOut->ClearDrawingArea();
    pManager->UpdateInterface();
}

void Select::Undo()
{
    // TODO: Implement undo
}

void Select::Redo()
{
    // TODO: Implement redo
}