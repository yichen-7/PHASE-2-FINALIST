#include "Probe.h"
#include "ApplicationManager.h"
#include "Components\Component.h"
#include "Components\Connection.h"
#include "Components\Gate.h"
#include "LED.h"
#include "SWITCH.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include <sstream>

ProbeCircuit::ProbeCircuit(ApplicationManager* pApp) : Action(pApp)
{
}

ProbeCircuit::~ProbeCircuit()
{
}

void ProbeCircuit::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("Circuit Probe: Click on any component or connection to inspect its value");

	// Get click position
	pIn->GetPointClicked(Cx, Cy);
}

void ProbeCircuit::Execute()
{
	ReadActionParameters();

	// Find component at clicked position
	Component* pComp = pManager->GetComponentAt(Cx, Cy);

	Output* pOut = pManager->GetOutput();

	if (pComp == NULL)
	{
		pOut->PrintMsg("No component at this position");
		return;
	}

	// Build the probe message
	string message = "";
	string label = pComp->GetLabel();
	string componentType = "";

	// Check what type of component it is
	Connection* conn = dynamic_cast<Connection*>(pComp);
	if (conn != NULL)
	{
		// It's a connection
		componentType = "Connection";
		int status = conn->GetOutPinStatus();

		if (label != "")
			message = "Connection '" + label + "': ";
		else
			message = "Connection: ";

		if (status == HIGH)
			message += "HIGH (1)";
		else if (status == LOW)
			message += "LOW (0)";
		else
			message += "UNDEFINED";
	}
	else
	{
		// Check if it's a switch
		SWITCH* sw = dynamic_cast<SWITCH*>(pComp);
		if (sw != NULL)
		{
			componentType = "Switch";
			int status = sw->GetOutPinStatus();

			if (label != "")
				message = "Switch '" + label + "' Output: ";
			else
				message = "Switch Output: ";

			if (status == HIGH)
				message += "HIGH (1) - ON";
			else
				message += "LOW (0) - OFF";
		}
		else
		{
			// Check if it's an LED
			LED* led = dynamic_cast<LED*>(pComp);
			if (led != NULL)
			{
				componentType = "LED";
				int status = led->GetInputPinStatus(1);

				if (label != "")
					message = "LED '" + label + "' Input: ";
				else
					message = "LED Input: ";

				if (status == HIGH)
					message += "HIGH (1) - LIT";
				else if (status == LOW)
					message += "LOW (0) - OFF";
				else
					message += "UNDEFINED";
			}
			else
			{
				// It's a gate
				Gate* gate = dynamic_cast<Gate*>(pComp);
				if (gate != NULL)
				{
					// Determine gate type from label or just say "Gate"
					componentType = "Gate";

					if (label != "")
						message = "Gate '" + label + "': ";
					else
						message = "Gate: ";

					// Show all input pins
					int inputCount = gate->GetInputPinCount();
					message += "Inputs(";
					for (int i = 0; i < inputCount; i++)
					{
						int status = gate->GetInputPinStatus(i + 1);
						if (status == HIGH)
							message += "1";
						else if (status == LOW)
							message += "0";
						else
							message += "?";

						if (i < inputCount - 1)
							message += ",";
					}
					message += ") -> Output: ";

					// Show output pin
					int outStatus = gate->GetOutPinStatus();
					if (outStatus == HIGH)
						message += "HIGH (1)";
					else if (outStatus == LOW)
						message += "LOW (0)";
					else
						message += "UNDEFINED";
				}
			}
		}
	}

	// Display the probe message
	if (message != "")
		pOut->PrintMsg(message);
	else
		pOut->PrintMsg("Cannot probe this component");
}

void ProbeCircuit::Undo()
{
	// Cannot undo probing
}

void ProbeCircuit::Redo()
{
	// Cannot redo probing
}