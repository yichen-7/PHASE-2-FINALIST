#include "Move.h"
#include "ApplicationManager.h"
#include "Components/Connection.h"
#include "Components/InputPin.h"
#include "Components/OutputPin.h"
#include "GUI/Input.h"
#include "GUI/Output.h"

Move::Move(ApplicationManager* pApp) : Action(pApp)
{
    pComp = nullptr;
}

Move::~Move()
{
}

void Move::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    // Check if multiple components are selected
    int selectedCount = pManager->GetSelectedCount();

    if (selectedCount > 1)
    {
        // MULTI-MOVE MODE
        pOut->PrintMsg("Multi-Move: Click to set reference point");
        pIn->GetPointClicked(Cx, Cy);

        pOut->PrintMsg("Multi-Move: Click where you want to move the components");
        pIn->GetPointClicked(NewCx, NewCy);

        pComp = nullptr; // Signal that we're in multi-move mode
    }
    else if (selectedCount == 1)
    {
        // Single component is already selected - move it
        Component** selected = pManager->GetSelectedComponents();
        pComp = selected[0];

        // Check if it's a connection
        Connection* conn = dynamic_cast<Connection*>(pComp);
        if (conn)
        {
            pOut->PrintMsg("Error: Cannot move connections. Move the connected components instead.");
            pComp = nullptr;
            return;
        }

        pOut->PrintMsg("Move: Click on the new position for the component");
        pIn->GetPointClicked(NewCx, NewCy);
    }
    else
    {
        // No selection - ask user to select component first
        pOut->PrintMsg("Move: Click on the component you want to move");
        pIn->GetPointClicked(Cx, Cy);

        pComp = pManager->GetComponentAt(Cx, Cy);

        if (!pComp)
        {
            pOut->PrintMsg("Error: No component found at this position");
            return;
        }

        // Check if it's a connection
        Connection* conn = dynamic_cast<Connection*>(pComp);
        if (conn)
        {
            pOut->PrintMsg("Error: Cannot move connections. Move the connected components instead.");
            pComp = nullptr;
            return;
        }

        pOut->PrintMsg("Move: Click on the new position for the component");
        pIn->GetPointClicked(NewCx, NewCy);
    }

    pOut->ClearStatusBar();
}

void Move::Execute()
{
    ReadActionParameters();

    Output* pOut = pManager->GetOutput();
    int selectedCount = pManager->GetSelectedCount();

    // CASE 1: Multi-Move (multiple components selected)
    if (selectedCount > 1 && pComp == nullptr)
    {
        // Calculate the offset
        int dx = NewCx - Cx;
        int dy = NewCy - Cy;

        Component** selectedComps = pManager->GetSelectedComponents();

        // Move all selected components (skip connections - they'll update automatically)
        for (int i = 0; i < selectedCount; i++)
        {
            Component* comp = selectedComps[i];

            // Don't move connections directly - they update automatically
            Connection* conn = dynamic_cast<Connection*>(comp);
            if (!conn)
            {
                GraphicsInfo oldGfx = comp->GetGraphicsInfo();
                GraphicsInfo newGfx;
                newGfx.x1 = oldGfx.x1 + dx;
                newGfx.x2 = oldGfx.x2 + dx;
                newGfx.y1 = oldGfx.y1 + dy;
                newGfx.y2 = oldGfx.y2 + dy;
                comp->SetGraphicsInfo(newGfx);
            }
        }

        // Now update all connections in the circuit
        UpdateAllConnections();

        pOut->ClearDrawingArea();
        pManager->UpdateInterface();
        pOut->PrintMsg("Multiple components moved successfully!");
    }
    // CASE 2: Single component move
    else if (pComp)
    {
        GraphicsInfo oldGfx = pComp->GetGraphicsInfo();
        int oldCenterX = (oldGfx.x1 + oldGfx.x2) / 2;
        int oldCenterY = (oldGfx.y1 + oldGfx.y2) / 2;

        int dx = NewCx - oldCenterX;
        int dy = NewCy - oldCenterY;

        GraphicsInfo newGfx;
        newGfx.x1 = oldGfx.x1 + dx;
        newGfx.x2 = oldGfx.x2 + dx;
        newGfx.y1 = oldGfx.y1 + dy;
        newGfx.y2 = oldGfx.y2 + dy;

        pComp->SetGraphicsInfo(newGfx);

        // Update all connections
        UpdateAllConnections();

        pOut->ClearDrawingArea();
        pManager->UpdateInterface();
        pOut->PrintMsg("Component moved successfully!");
    }
}

void Move::UpdateAllConnections()
{
    int compCount = pManager->GetComponentCount();
    Component** compList = pManager->GetComponentList();

    for (int i = 0; i < compCount; i++)
    {
        Connection* conn = dynamic_cast<Connection*>(compList[i]);
        if (conn)
        {
            OutputPin* srcPin = conn->getSourcePin();
            InputPin* dstPin = conn->getDestPin();

            if (srcPin && dstPin)
            {
                GraphicsInfo connGfx;
                connGfx.x1 = srcPin->getX();
                connGfx.y1 = srcPin->getY();
                connGfx.x2 = dstPin->getX();
                connGfx.y2 = dstPin->getY();

                conn->SetGraphicsInfo(connGfx);
            }
        }
    }
}

void Move::Undo()
{
    // TODO: Implement undo
}

void Move::Redo()
{
    // TODO: Implement redo
}