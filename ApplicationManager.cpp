#include "ApplicationManager.h"
#include "Components/Connection.h"

#include <iostream>

#include "Actions/Connect.h"

//==============DOAA===========
#include "Components\LED.h"
#include "Components\SWITCH.h"
#include "Components\AND2.h"
#include "Components\AND3.h"
#include "Components\NOR2.h"
#include "Components\NOR3.h"
#include "Components\XOR2.h"
#include "Components\XOR3.h"
#include "Components\OR2.h"
#include "Components\NAND2.h"
#include "Components\XNOR2.h"
#include "Components\Buff.h"
#include "Components\INV.h"

using namespace std;

void ApplicationManager::DeselectComponentExcept(int except)
{
	GetOutput()->PrintMsg(""); // To clear the status bar
	if (except == -1)
		SetLastSelectedComponent(-1); // To clear the component from the lastSelectedComponent in pManager

	// Deselect all the components on the screen
	for (int i = 0; i < CompCount; i++)
	{
		if (i == except)
			continue;
		else
			CompList[i]->set_is_selected(false); // To make a notation that the clicked component is not selected.
	}
}

void ApplicationManager::SelectComponent(int target)
{
	CompList[target]->set_is_selected(true); // To set is_selected for the target = true
}

void ApplicationManager::DeleteComponent()
{
	if (lastSelectedComponent != nullptr)
		for (int i = 0; i < CompCount; i++) // To iterate on all of the existing components
		{
			if (lastSelectedComponent->get_id() == CompList[i]->get_id()) // To make the following codes on the lastSelectedComponent 
			{
				// The delete of the pointer to the input and output pins of the selected component is the responsibilty of the desturctor of the class Gate
				delete CompList[i]; // To delete the pointer that pointing to the seleted component
				CompList[i] = nullptr; // To make the pointer point to a null pointer
				for (int j = i; j < CompCount - 1; j++) // To shift the components in compList to avoid leting a blank component
					swap(CompList[j], CompList[j + 1]);
				CompCount--;
				lastSelectedComponent = nullptr;
				break;
			}
		}
	else
		GetOutput()->PrintMsg("You have to select a certain compnent before delete!");
}

void ApplicationManager::DeleteAll()
{
	for (int i = CompCount; i >= 0; i--) {
		cout << "Drawing White Rectangle..." << endl;
		delete CompList[i]; // To delete the pointer that pointing to the seleted component
		CompList[i] = NULL; // To make the pointer point to a null pointer
		cout << "Deleting..." << endl;
		CompCount--;
	}
	GetOutput()->ClearWindow();
	lastSelectedComponent = NULL;
}

ApplicationManager::ApplicationManager() : lastSelectedComponent(NULL)
{
	CompCount = 0;

	for (int i = 0; i < MaxCompCount; i++)
		CompList[i] = NULL;

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;
}

Component* const* ApplicationManager::getComponents(int& count) const
{
	count = CompCount;
	return CompList;
}
void ApplicationManager::save(ofstream*& fptr)
{
	int NonConnCount = 0; //counter for components that arenot connections
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] != 0 && CompList[i]->get_comp_type() != COMP_TYPES::COMP_CONN)
			NonConnCount++;
	}
	*fptr << NonConnCount << endl;
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] != 0 && CompList[i]->get_comp_type() != COMP_TYPES::COMP_CONN)
			CompList[i]->save(fptr);
	}
	*fptr << "Connections\n";
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] != 0 && CompList[i]->get_comp_type() == COMP_TYPES::COMP_CONN)
			CompList[i]->save(fptr);
	}
	*fptr << "-1";
}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return InputInterface->GetUserAction();
}

ActionType ApplicationManager::AddGate()
{
	return InputInterface->AddGate();
}

////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	switch (ActType)
	{
	case ADD_Gate:
		pAct = new Add(this);
		break;
	case ADD_AND_GATE_2:
		pAct = new AddANDgate2(this);
		break;

	case ADD_CONNECTION:
		//TODO: Create AddConection Action here
		pAct = new Connect(this);
		break;
		// ============================== Ahmed Alaa edited here ==============================
	case SELECT:
		pAct = new Select(this);
		break;

	case ADD_Label:
		pAct = new Label(this, lastSelectedComponent);
		break;
	case DEL:
		pAct = new Delete(this);
		break;
	case Clear_all:
		pAct = new Clear(this);
		break;
		// ==================================== Ahmed Alaa ====================================

	case DSN_MODE:
		pAct = new SwitchToDesign(this);
		break;
	case SIM_MODE:
		pAct = new SwitchToSimulation(this);
		break;
	case EXIT:
		pAct = new Exit(this);
		break;
	case SAVE:
		pAct = new Save(this);
		break;
		/*case LOAD:
			pAct = new Load(this);
			break;*/
	}
	if (pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
	for (int i = 0; i < CompCount; i++)
		CompList[i]->Draw(OutputInterface);

}

void ApplicationManager::set_clipboard()
{
	Clipboard = lastSelectedComponent->get_comp_type();

}



COMP_TYPES ApplicationManager::get_clipboard() const
{
	return Clipboard;
}

SWITCH** ApplicationManager::get_switches(int &num) const
{
	num = 0;
	SWITCH** sh;
	for (int i = 0; i < CompCount; ++i)
	{

		if (CompList[i]->GetInputPinStatus(0) == -1)
		{
			num++;
		}
	}
	sh = new SWITCH * [num];
	int j = 0;
	for (int i = 0; i < CompCount; ++i)
	{

		if (CompList[i]->GetInputPinStatus(0) == -1)
		{
			sh[j++] = (SWITCH*)CompList[i];
		}
	}

	return sh;

}

////////////////////////////////////////////////////////////////////
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}

void ApplicationManager::SetLastSelectedComponent(int target)
{
	if (target == -1)
		lastSelectedComponent = nullptr;
	else
		lastSelectedComponent = CompList[target];
}

Component* ApplicationManager::GetLastSelectedComponent()
{
	return lastSelectedComponent;
}

int ApplicationManager::which_component(COMP_TYPES& comptype)
{
	int x = 0, y = 0;
	GetInput()->GetLastClicked(x, y); // To get the x, y coordinates of point clicked
	int target = -1; // The default value of target is -1
	comptype = COMP_TYPES::COMP_GENERAL; // The default value of the component clicked is COMP_GENERAL
	for (int i = 0; i < CompCount; i++) { // We should loop on all of the components of compList to determine which component is selected
		// To get a copy from the x1, y1, x2, y2 of each component
		int x1 = CompList[i]->getGraphicsInfo().x1;
		int y1 = CompList[i]->getGraphicsInfo().y1;
		int x2 = CompList[i]->getGraphicsInfo().x2;
		int y2 = CompList[i]->getGraphicsInfo().y2;

		// I compare the clicked coordinates with the coordinates of each component.

		if (x1 <= x && x <= x2 && y1 <= y && y <= y2) {
			CompList[i]->set_is_selected(true); // Set the is_select data member to true.
			comptype = CompList[i]->get_comp_type();
			target = i;
			break;
		}
	}



	return target; // The index of the clicked component from the compList
}

////////////////////////////////////////////////////////////////////
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}

////////////////////////////////////////////////////////////////////

//======================================Doaa=======================

int ApplicationManager::getCompCount()
{
	return CompCount;
}




//=========================================DOAA MAGDY=============================================//
bool ApplicationManager::checkIfSourceIsLED(int cx, int cy)
{
	for (int i = 0; i < CompCount; i++)
	{
		bool d = CompList[i]->InsideArea(cx, cy);
		if (d)
		{
			COMP_TYPES type = CompList[i]->get_comp_type();
			if (type == COMP_TYPES::COMP_LED)
			{
				OutputInterface->PrintMsg("Error: the led has no output pin");
				return true;
			}
		}
	}
	return false;
}

bool ApplicationManager::PressOn_WhiteSpace(int cx, int cy)
{
	int count_check_s = 0;
	for (int i = 0; i < CompCount; i++)
	{
		bool d = CompList[i]->InsideArea(cx, cy);
		if (d == true)
		{
			count_check_s++;
		}
	}

	if (count_check_s == 0)
	{
		OutputInterface->PrintMsg("Error: You can not choose a white space. You have to choose a gate");
		return true;
	}
	else
		return false;
}

Component* ApplicationManager::CheckInsideArea(int cx, int cy)
{
	int i;
	for (i = 0; i < CompCount; i++)
	{
		bool d = CompList[i]->InsideArea(cx, cy);
		if (d)
		{
			break;
		}

	}
	return CompList[i];
}

bool ApplicationManager::Check_gates_to_connect(Component* srcComp, Component* distComp)
{
	if (distComp == srcComp)
	{
		OutputInterface->PrintMsg("Error: You have already chosen this gate as a source gate. You can not connect a gate to itself");
		return 0;
	}

	COMP_TYPES type = distComp->get_comp_type();
	if (type == COMP_TYPES::COMP_SWITCH)
	{

		OutputInterface->PrintMsg("Error: the switch has no input pins");
		return 0;

	}

}
bool ApplicationManager::Check_pins_to_connect(Component* distComp, InputPin* inPin, GraphicsInfo& GInfo)
{
	int no_input_pins = distComp->getNoOfInputpins();
	for (int j = 0; j < no_input_pins; j++)
	{
		bool isConnected = inPin[j].get_is_connected();
		if (isConnected == false)
		{
			inPin[j].set_is_connected(true);
			//break;
			//return true;
		

		COMP_TYPES type = distComp->get_comp_type();
		int a1, b1, a2, b2;
		distComp->getm_GfxInfo(a1, b1, a2, b2);

		switch (type)
		{
			/*
		case COMP_TYPES::COMP_GENERAL:
			break;
		case COMP_TYPES::COMP_GATE:
			break;
		case COMP_TYPES::COMP_SWITCH:
			break;
			*/
		case COMP_TYPES::COMP_LED:
		{
			//pManager->getGInfoOfComp(a1, b1, a2, b2, k);
			GInfo.x2 = a1 + 23;
			GInfo.y2 = (b1 + (b2 - b1) / 2) + 26;
			break;
		}
		//case COMP_TYPES::COMP_CONN:
			//break;
		case COMP_TYPES::AND_2:
			if (j == 0)
			{
				GInfo.x2 = a1;
				GInfo.y2 = b1 + 15 + 1;

			}
			else if (j == 1)
			{
				GInfo.x2 = a1;
				GInfo.y2 = b2 - 14 - 2;
			}
			break;
		case COMP_TYPES::AND_3:
			if (j == 0)
			{
				GInfo.x2 = a1;
				GInfo.y2 = b1 + 16;

			}
			else if (j == 1)
			{
				GInfo.x2 = a1;
				GInfo.y2 = b1 + (b2 - b1) / 2;

			}
			else if (j == 2)
			{
				GInfo.x2 = a1;
				GInfo.y2 = b2 - 16;

			}
			break;
		case COMP_TYPES::INV_:
			GInfo.x2 = a1;
			GInfo.y2 = b1 + (b2 - b1) / 2;
			break;
		case COMP_TYPES::NAND_2:
			if (j == 0)
			{
				GInfo.x2 = a1;
				GInfo.y2 = b1 + 15;
			}
			else if (j == 1)
			{
				GInfo.x2 = a1;
				GInfo.y2 = b2 - 14 + 3;
			}
			break;
		case COMP_TYPES::NOR_2:
			if (j == 0)
			{
				GInfo.x2 = a1;
				GInfo.y2 = b1 + 15 + 7;
			}
			else if (j == 1)
			{
				GInfo.x2 = a1;
				GInfo.y2 = b2 - 14 - 4;
			}
			break;
		case COMP_TYPES::NOR_3:
			if (j == 0)
			{
				GInfo.x2 = a1 + 11;
				GInfo.y2 = b1 + 16 + 1;

			}
			else if (j == 1)
			{
				GInfo.x2 = a1 + 11;
				GInfo.y2 = b1 + (b2 - b1) / 2 + 1;
			}
			else if (j == 2)
			{
				GInfo.x2 = a1 + 11;
				GInfo.y2 = b2 - 16 + 1;
			}
			break;
		case COMP_TYPES::Buff_:
			GInfo.x2 = a1;
			GInfo.y2 = b1 + (b2 - b1) / 2;
			break;
		case COMP_TYPES::OR_2:
			if (j == 0)
			{
				GInfo.x2 = a1 + 8;
				GInfo.y2 = b1 + 15 - 7;
			}
			else if (j == 1)
			{
				GInfo.x2 = a1 + 8;
				GInfo.y2 = b2 - 14 + 3;
			}
			break;
		case COMP_TYPES::XNOR_2:
			if (j == 0)
			{
				GInfo.x2 = a1;
				GInfo.y2 = b1 + 15 + 5;
			}
			else if (j == 1)
			{
				GInfo.x2 = a1;
				GInfo.y2 = b2 - 14 - 5;
			}
			break;
		case COMP_TYPES::XOR_2:
			if (j == 0)
			{
				GInfo.x2 = a1;
				GInfo.y2 = b1 + 15;
			}
			else if (j == 1)
			{
				GInfo.x2 = a1;
				GInfo.y2 = b2 - 14;
			}
			break;
		case COMP_TYPES::XOR_3:
			if (j == 0)
			{
				GInfo.x2 = a1;
				GInfo.y2 = b1 + 16;
			}
			else if (j == 1)
			{
				GInfo.x2 = a1;
				GInfo.y2 = b1 + (b2 - b1) / 2;
			}
			else if (j == 2)
			{
				GInfo.x2 = a1;
				GInfo.y2 = b2 - 16;
			}
			break;
		default:
			break;
		}
		break;

	}


		if (j == no_input_pins - 1 && isConnected == true)
		{
			OutputInterface->PrintMsg("Error: All input pins of this component are already connected");
			return false;
		}
		
	}
	return 1;
}



/*
OutputPin* ApplicationManager::getOutputPinOfComp(int i)
{
	OutputPin* o = CompList[i]->getOutputPin();
	return o;
}

InputPin* ApplicationManager::getInputPinOfComp(int k)
{
	InputPin* i = CompList[k]->getInputPin();
	return i;
}

void ApplicationManager::getGInfoOfComp(int& a, int& b, int& c, int& d, int i)
{
	CompList[i]->getm_GfxInfo(a, b, c, d);
}

int const ApplicationManager::getNoOfInputpinsOfComp(int k)
{
	int const a = CompList[k]->getNoOfInputpins();
	return a;
}

bool ApplicationManager::CheckWheatherSrcIsTheDist(int i, int k)
{
	if (CompList[i] == CompList[k])
		return true;
	return false;
}


int ApplicationManager::CheckWhetherLEDorSWITCH(int case1, int currentComp)
{
	if (case1 == 1)
		return CompList[currentComp]->GetOutPinStatus();	//returns status of outputpin if LED, return -1
	else
		return CompList[currentComp]->GetInputPinStatus(1);	//returns status of Inputpin # n if SWITCH, return -1
}
*/
//=========================================DOAA MAGDY=============================================//



ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;

}