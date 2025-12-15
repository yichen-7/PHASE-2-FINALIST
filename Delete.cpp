#include "Delete.h"
#include "ApplicationManager.h"
#include "Components\Connection.h"
#include "GUI/Input.h"
#include "GUI/Output.h"

Delete::Delete(ApplicationManager* pApp) : Action(pApp)
{
}

Delete::~Delete(void)
{
}

void Delete::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    int selectedCount = pManager->GetSelectedCount();

    if (selectedCount > 0)
    {
        // Components are already selected - just confirm
        pOut->PrintMsg("Delete: Click anywhere to confirm deletion of selected components (or click outside to cancel)");
    }
    else
    {
        // No selection - ask user to click on component
        pOut->PrintMsg("Click on the component or connection you want to delete");
    }

    pIn->GetPointClicked(Cx, Cy);
    pOut->ClearStatusBar();
}

void Delete::Execute()
{
    ReadActionParameters();

    Output* pOut = pManager->GetOutput();
    int selectedCount = pManager->GetSelectedCount();

    // CASE 1: Multi-Delete (multiple components selected)
    if (selectedCount > 1)
    {
        Component** selectedComps = pManager->GetSelectedComponents();

        // Create a copy of the selection list because deleting modifies the original
        Component* toDelete[200]; // Using same max as ApplicationManager
        int deleteCount = selectedCount;

        for (int i = 0; i < deleteCount; i++)
        {
            toDelete[i] = selectedComps[i];
        }

        // Clear the selection first (important!)
        pManager->ClearSelection();

        // Now delete all components
        for (int i = 0; i < deleteCount; i++)
        {
            pManager->DeleteComponent(toDelete[i]);
        }

        pOut->ClearDrawingArea();
        pManager->UpdateInterface();
        pOut->PrintMsg("Multiple components deleted successfully");
    }
    // CASE 2: Single component delete (either selected or clicked)
    else
    {
        Component* pComp = nullptr;

        if (selectedCount == 1)
        {
            // One component is selected
            Component** selected = pManager->GetSelectedComponents();
            pComp = selected[0];
            pManager->ClearSelection(); // Clear selection before deleting
        }
        else
        {
            // No selection - find component at clicked position
            pComp = pManager->GetComponentAt(Cx, Cy);
        }

        if (pComp != NULL)
        {
            Connection* conn = dynamic_cast<Connection*>(pComp);

            if (conn)
            {
                pManager->DeleteComponent(conn);
                pOut->PrintMsg("Connection deleted successfully");
            }
            else
            {
                pManager->DeleteComponent(pComp);
                pOut->PrintMsg("Component deleted successfully");
            }

            pOut->ClearDrawingArea();
            pManager->UpdateInterface();
        }
        else
        {
            pOut->PrintMsg("No component found at this position");
        }
    }
}

void Delete::Undo()
{
}

void Delete::Redo()
{
}