#include "AddConnection.h"
#include "ApplicationManager.h"
#include "Components\Connection.h"
#include "Components\OutputPin.h"
#include "Components\InputPin.h"

AddConnection::AddConnection(ApplicationManager* pApp) : Action(pApp)
{
    SrcPin = nullptr;
    DstPin = nullptr;
    pConn = nullptr;
}

AddConnection::~AddConnection()
{
}

void AddConnection::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();
    int x, y;

    // Step 1: Get SOURCE component
    pOut->PrintMsg("Connection: Click on the SOURCE component (with output pin)");
    pIn->GetPointClicked(x, y);

    Component* srcComp = pManager->GetComponentAt(x, y);
    if (!srcComp)
    {
        pOut->PrintMsg("Error: No component at this position");
        return;
    }

    SrcPin = srcComp->GetOutputPin();
    if (!SrcPin)
    {
        pOut->PrintMsg("Error: Component has no output pin");
        return;
    }

    // Step 2: Get DESTINATION component
    pOut->PrintMsg("Connection: Click on the DESTINATION component (with input pin)");
    pIn->GetPointClicked(x, y);

    Component* dstComp = pManager->GetComponentAt(x, y);
    if (!dstComp)
    {
        pOut->PrintMsg("Error: No component at this position");
        SrcPin = nullptr;
        return;
    }

    // Find free input pin using the component's reported input-pin count
    DstPin = nullptr;
    int pinCount = dstComp->GetInputPinCount();
    bool found = false;
    if (pinCount > 0)
    {
        for (int i = 0; i < pinCount; ++i)
        {
            InputPin* pin = dstComp->GetInputPin(i);
            if (pin && pin->getConnection() == nullptr)
            {
                DstPin = pin;
                found = true;
                break;
            }
        }
    }

    if (!found)
    {
        // fallback: probe until GetInputPin returns nullptr
        for (int i = 0; ; ++i)
        {
            InputPin* pin = dstComp->GetInputPin(i);
            if (!pin)
                break;
            if (pin->getConnection() == nullptr)
            {
                DstPin = pin;
                found = true;
                break;
            }
        }
    }

    if (!DstPin)
    {
        pOut->PrintMsg("Error: No free input pins");
        SrcPin = nullptr;
        return;
    }

    pOut->ClearStatusBar();
}


void AddConnection::Execute()
{
    ReadActionParameters();

    if (SrcPin && DstPin)
    {
        GInfo.x1 = SrcPin->getX();
        GInfo.y1 = SrcPin->getY();
        GInfo.x2 = DstPin->getX();
        GInfo.y2 = DstPin->getY();

        pConn = new Connection(GInfo, SrcPin, DstPin);

        SrcPin->ConnectTo(pConn);
        DstPin->setConnection(pConn);

        pManager->AddComponent(pConn);

        Output* pOut = pManager->GetOutput();
        pOut->PrintMsg("Connection created successfully!");

        // Update interface to show connection
        pManager->UpdateInterface();
    }
}

void AddConnection::Undo()
{
}

void AddConnection::Redo()
{
}