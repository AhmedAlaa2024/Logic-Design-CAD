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
		if (lastSelectedComponent != NULL)
			if (lastSelectedComponent->get_m_Label() == "") // To make sure that there is not an existing label
				pAct = new Label(this, lastSelectedComponent);
			else
				this->GetOutput()->PrintMsg("There is already a label.");
		else
			this->GetOutput()->PrintMsg("Please, Select an component before adding a label.");
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

void ApplicationManager::SetLastSelectedComponent(Component* component)
{
	lastSelectedComponent = component;
}

Component* ApplicationManager::GetLastSelectedComponent()
{
	return lastSelectedComponent;
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