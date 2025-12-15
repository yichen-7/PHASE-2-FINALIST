#include "EditLabel.h"
#include "ApplicationManager.h"
#include "Components\Connection.h"
#include "Components\InputPin.h"
#include "Components\OutputPin.h"
EditLabel::EditLabel(ApplicationManager* pApp) : Action(pApp)
{
}

EditLabel::~EditLabel(void)
{
}

void EditLabel::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Click on the component/connection you want to edit");
    pIn->GetPointClicked(Cx, Cy);
    pOut->ClearStatusBar();
}

void EditLabel::Execute()
{
    ReadActionParameters();

    Component* pComp = pManager->GetComponentAt(Cx, Cy);
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    if (pComp == NULL)
    {
        pOut->PrintMsg("No component found at this position");
        return;
    }

    // Check if it's a connection
    Connection* pConn = dynamic_cast<Connection*>(pComp);

    if (pConn != NULL)
    {
        // === EDITING A CONNECTION ===

        // STEP 1: Edit Label
        pOut->PrintMsg("Edit Connection - Enter new label (or press ESC to skip):");
        newLabel = pIn->GetSrting(pOut);

        if (newLabel != "")
        {
            pConn->SetLabel(newLabel);
            pOut->PrintMsg("Label updated.");
        }

        // STEP 2: Change Source Pin (Output Pin)
        pOut->PrintMsg("Change SOURCE pin? Click new SOURCE component (or click anywhere else to skip)");

        int srcX, srcY;
        pIn->GetPointClicked(srcX, srcY);

        Component* newSrcComp = pManager->GetComponentAt(srcX, srcY);

        if (newSrcComp != NULL && newSrcComp != pConn)
        {
            // Check if it's NOT a connection
            Connection* testConn = dynamic_cast<Connection*>(newSrcComp);
            if (testConn != NULL)
            {
                pOut->PrintMsg("Error: Cannot connect from a connection!");
            }
            else
            {
                // Get output pin from new source
                OutputPin* newSrcPin = newSrcComp->GetOutputPin();

                if (newSrcPin == nullptr)
                {
                    pOut->PrintMsg("Error: Selected component has no output pin!");
                }
                else
                {
                    // Disconnect from old source
                    OutputPin* oldSrcPin = pConn->getSourcePin();
                    if (oldSrcPin)
                    {
                        oldSrcPin->RemoveConnection(pConn);
                    }

                    // Connect to new source
                    pConn->setSourcePin(newSrcPin);
                    newSrcPin->ConnectTo(pConn);

                    pOut->PrintMsg("Source pin changed successfully!");
                }
            }
        }

        // STEP 3: Change Destination Pin (Input Pin)
        pOut->PrintMsg("Change DESTINATION pin? Click new DESTINATION component (or click anywhere else to skip)");

        int dstX, dstY;
        pIn->GetPointClicked(dstX, dstY);

        Component* newDstComp = pManager->GetComponentAt(dstX, dstY);

        if (newDstComp != NULL && newDstComp != pConn)
        {
            // Check if it's NOT a connection
            Connection* testConn = dynamic_cast<Connection*>(newDstComp);
            if (testConn != NULL)
            {
                pOut->PrintMsg("Error: Cannot connect to another connection!");
            }
            else
            {
                // Find a free input pin on the new destination
                InputPin* newDstPin = nullptr;
                int pinCount = newDstComp->GetInputPinCount();

                for (int i = 0; i < pinCount; i++)
                {
                    InputPin* pin = newDstComp->GetInputPin(i);
                    if (pin && pin->getConnection() == nullptr)
                    {
                        newDstPin = pin;
                        break;
                    }
                }

                if (newDstPin == nullptr)
                {
                    pOut->PrintMsg("Error: No free input pins on the selected component");
                }
                else
                {
                    // Disconnect from old destination
                    InputPin* oldDstPin = pConn->getDestPin();
                    if (oldDstPin)
                    {
                        oldDstPin->setConnection(nullptr);
                    }

                    // Connect to new destination
                    pConn->setDestPin(newDstPin);
                    newDstPin->setConnection(pConn);

                    pOut->PrintMsg("Destination pin changed successfully!");
                }
            }
        }

        // Redraw to show changes
        pOut->ClearDrawingArea();
        pManager->UpdateInterface();
    }
    else
    {
        // === EDITING A REGULAR COMPONENT ===
        pOut->PrintMsg("Enter new label (or press ESC to cancel):");
        newLabel = pIn->GetSrting(pOut);

        if (newLabel != "")
        {
            pComp->SetLabel(newLabel);
            pOut->PrintMsg("Label updated successfully");

            pOut->ClearDrawingArea();
            pManager->UpdateInterface();
        }
        else
        {
            pOut->PrintMsg("Edit cancelled");
        }
    }
}

void EditLabel::Undo()
{
}

void EditLabel::Redo()
{
}