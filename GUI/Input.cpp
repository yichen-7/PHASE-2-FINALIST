#include "Input.h"
#include "Output.h"

Input::Input(window* pW)
{
    pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int& x, int& y)
{
    pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output* pOut)
{
    ///TO DO: Implement this Function.
    //Read a complete string from the user until the user presses "ENTER".
    //If the user presses "ESCAPE". This function should return an empty string.
    //"BACKSPACE" should be also supported.
    //User should see what he is typing at the status bar.
    string input = "";
    char key;
    pOut->PrintMsg("Enter text:");

    const char ESC = 27;
    const char ENTER = 13;
    const char BACKSPACE = 8;

    while (true)
    {
        pWind->WaitKeyPress(key);

        if (key == ESC) // ESC key
        {
            pOut->PrintMsg("");
            return "";
        }
        else if (key == ENTER) // ENTER key
        {
            return input;
        }
        else if (key == BACKSPACE) // BACKSPACE key
        {
            if (!input.empty())
            {
                input.pop_back();
            }
        }
        else
        {
            input = input + key; // add new character
        }

        pOut->PrintMsg(input);
    }
    return "";
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{
    int x, y;
    pWind->WaitMouseClick(x, y); // get click coords

    // ------------------ DESIGN MODE ------------------
    if (UI.AppMode == DESIGN)
    {
        // Click in toolbar
        if (y >= 620 && y < UI.ToolBarHeight + 620)
        {
            int ClickedItemOrder = x / UI.ToolItemWidth;
            switch (ClickedItemOrder)
            {
                // 1-input gates
            case ITM_BUFF:   return ADD_Buff;
            case ITM_INV:    return ADD_INV;

                // 2-input gates
            case ITM_AND2:   return ADD_AND_GATE_2;
            case ITM_OR2:    return ADD_OR_GATE_2;
            case ITM_NAND2:  return ADD_NAND_GATE_2;
            case ITM_NOR2:   return ADD_NOR_GATE_2;
            case ITM_XOR2:   return ADD_XOR_GATE_2;
            case ITM_XNOR2:  return ADD_XNOR_GATE_2;

                // 3-input gates
            case ITM_AND3:   return ADD_AND_GATE_3;
            case ITM_NOR3:   return ADD_NOR_GATE_3;
            case ITM_XOR3:   return ADD_XOR_GATE_3;

                // IO components
            case ITM_SWITCH: return ADD_Switch;
            case ITM_LED:    return ADD_LED;

                // Exit
            case ITM_EXIT:   return EXIT;

            default:         return DSN_TOOL; // click on empty area of design toolbar
            }
        }

        //Click in action toolbar
        if (y >= 0 && y < UI.ToolBarHeight)
        {
            int ClickedItemOrder = x / UI.ToolItemWidth;
            switch (ClickedItemOrder)
            {
                // 1-input gates
                 //If you want to change the menu items order, change the order here
                case ACT_DELETE:   return DEL;
                case ACT_CONNECTION: return ADD_CONNECTION;
                case ACT_EDIT:  return EDIT_Label;
                case ACT_SIM:   return SIM_MODE;
				case ACT_MOVE:  return MOVE;
				case ACT_SELECT: return SELECT;
				case ACT_COPY:  return COPY;
				case ACT_PASTE: return PASTE;
				case ACT_CUT:   return CUT;
				case ACT_SAVE:  return SAVE;
				case ACT_LOAD:  return LOAD;
               
              


                default:         return ACT_TOOL; // click on empty area of design toolbar
            }
        }


        // Click in drawing area
        if (y >= 0 && y < 80)
            return ACT_TOOL;

     

        // Click in status bar
        return STATUS_BAR;
    }

    // ------------------ SIMULATION MODE ------------------
    else // UI.AppMode == SIMULATION
    {
        // Click in simulation toolbar
        if (y >= 0 && y < UI.ToolBarHeight)
        {
            int ClickedItemOrder = x / UI.ToolItemWidth;
            switch (ClickedItemOrder)
            {
            case ITM_SIM:   return SIM_MODE;         // you can adjust if you want different behavior
            case ITM_TRUTH: return Create_TruthTable;
            case ITM_MENU:  return DSN_MODE;
            case ITM_PROBE: return PROBE;
            default:        return DSN_TOOL;
            }
        }

        // Click in drawing area during simulation: toggle switches
        if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
            return Change_Switch;

        // Click in status bar
        return STATUS_BAR;
    }
}


Input::~Input()
{
}