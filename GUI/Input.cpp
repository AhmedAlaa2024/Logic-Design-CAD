#include "Input.h"
#include "Output.h"


Input::Input(window* pW) : last_x(0), last_y(0)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int& x, int& y)
{
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	last_x = x;
	last_y = y;
}

string Input::GetString(Output* pOut, string startwith) const
{
	///TODO: Implement this Function
	//Read a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" should be also supported
	//User should see what he is typing at the status bar
	keytype a;
	string s = startwith;
	char c;
	pWind->FlushKeyQueue();

	while (true)
	{
		pWind->FlushMouseQueue();
		a = pWind->WaitKeyPress(c);
		switch (a)
		{

		case 1: // in case a normal key got pressed

			if (c == 8) // backspace
			{
				if (!s.empty()) { // why? 
					s.erase(s.size() - 1);
				}
			}
			else if (c == 13)//enter pressed
			{
				pOut->ClearStatusBar();
				return s;
			}
			else {
				s += c;
			}

			break;
		case 2: //Arrow
			break;
		case 3: //FUNCTION
			break;

		case 4: // Escape pressed
			pOut->ClearStatusBar();
			return "";

		default:
			break;
		}

		pOut->PrintMsg(s);

	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction()
{

	
	int ClickedItemOrder;
	int x = 0, y = 0;
	GetPointClicked(x, y);

	if (UI.AppMode == DESIGN)	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			ClickedItemOrder = (x / UI.ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on


			switch (ClickedItemOrder)
			{
			case ADD_GATE: return ADD_Gate;
			case SIM_ICON: return SIM_MODE;
			case ADD_LABEL: return ADD_Label;
			case EDIT_LABEL: return EDIT_Label;
			case WIRE: return ADD_CONNECTION;
			case ORGANIZE_SCREEN: return Organize;
			case CLEAR: return Clear_all;
			case LOAD_ICON: return LOAD;
			case SAVE_ICON: return SAVE;
			case ITM_EXIT: return EXIT;

			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			if (x >= UI.width - UI.ToolBarHeight - 15)
			{
				ClickedItemOrder = (y / UI.ToolItemWidth) - 1;
				switch (ClickedItemOrder)
				{
				case ITM_UNDO: return UNDO;
				case ITM_REDO: return REDO;
				case COPY_ICON: return COPY_;
				case CUT_ICON: return CUT_;
				case PASTE_ICON:  return PASTE_;
				case DELETE_ICON: return DEL;
				default: return DSN_TOOL;
				}
			}
			return SELECT;	//user want to select/unselect a component
		}



		//[3] User clicks on the status bar
		if (y >= UI.height - UI.StatusBarHeight && y <= UI.height)
		{
			return STATUS_BAR;

		}


		//[4] user press ctrl+c or ctrl+v or ctrl+x











	}
	else	//Application is in Simulation mode
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			ClickedItemOrder = (x / UI.ToolItemWidth);
			switch (ClickedItemOrder)
			{
			case ITM_DSN: return DSN_MODE;
			case ITM_PRODING: return PROGING;
			case ITM_CHANGE_SWITCH: return Change_Switch;
			case ITM_LOAD: return LOAD;
			case ITM_SAVE: return SAVE;
			case SIM_EXIT: return EXIT; //TODO: weird line

			default: return SIM_TOOL;	//A click on empty place in simulation toolbar
			}
		}
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			//TODO

			return SELECT;	//user clicks on drawing area

		}

		//[3] User clicks on the status bar
		return STATUS_BAR;
	}


}
ActionType Input::AddGate() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
	if (UI.AppMode == DESIGN)	//application is in design mode
	{

		//[1] If user clicks on the Toolbar
		if (y >= UI.height - (UI.StatusBarHeight + UI.Gate_Height) && y <= UI.height - UI.StatusBarHeight)
		{

			int GateOrder = (x / UI.Gate_Width);
			switch (GateOrder)
			{
			case AND_2IN: return ADD_AND_GATE_2;
			case OR_2IN: return ADD_OR_GATE_2;
			case BUF: return ADD_Buff;
			case NOT: return ADD_INV;
			case NAND_2IN: return ADD_NAND_GATE_2;
			case NOR_2IN: return ADD_NOR_GATE_2;
			case XOR_2IN: return ADD_XOR_GATE_2;
			case XNOR_2IN: return ADD_XNOR_GATE_2;
			case AND_3IN: return ADD_AND_GATE_3;
			case NOR_3IN: return ADD_NOR_GATE_3;
			case XOR_3IN: return ADD_XOR_GATE_3;
			case LED1: return  ADD_LED;
			case SWITCH1: return  ADD_Switch;
			default: return GATE_TOOL;	//A click on empty place in simulation toolbar
			}
		}

	}
	return EXIT;
}

void Input::GetLastClicked(int& x, int& y)
{
	x = last_x;
	y = last_y;
}

string Input::getfilename(Output* pOut) const
{
	pOut->PrintMsg("Please, enter file name here!");
	return GetString(pOut);
}

Input::~Input()
{
}
