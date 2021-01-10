#include "ApplicationManager.h"
#include "Components/Connection.h"
#include "Components/Gate.h"
#include "Components/AND2.h"
#include "Components/AND3.h"
#include "Components/INV.h"
#include "Components/NOR2.h"
#include "Components/SWITCH.h"
#include "Components/LED.h"
#include "Components/Buff.h"
#include "Components/NAND2.h"
#include "Components/NOR3.h"
#include "Components/OR2.h"
#include "Components/XNOR2.h"
#include "Components/XOR2.h"
#include "Components/XOR3.h"


#include <iostream>

#include "Actions/Connect.h"

//==============DOAA===========
#include "Actions/CopyCutPaste.h"
#include "Actions/SimulateCircuit.h"
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



void ApplicationManager::shift_to_end(int i)
{
	for (int j = i; j < CompCount - 1; j++) // To shift the components in compList to avoid leting a blank component
		swap(CompList[j], CompList[j + 1]);

}



void ApplicationManager::DeleteComponent()
{
	
	if (lastSelectedComponent != nullptr)

		for (int i = 0; i < CompCount; i++) // To iterate on all of the existing components
		{


			if (lastSelectedComponent == CompList[i]) // To make the following codes on the lastSelectedComponent 
			{
				// The delete of the pointer to the input and output pins of the selected component is the responsibilty of the desturctor of the class Gate
				GetOutput()->ClearComponentArea(lastSelectedComponent->getGraphicsInfo());
				GetOutput()->ClearLabelArea(lastSelectedComponent->getGraphicsInfo(), (lastSelectedComponent->get_m_Label()).size());
				int no_conns;

				//first the output pin
				auto conns = lastSelectedComponent->getOutputPin()->get_connections(no_conns);

				for (int j = 0; j < no_conns; ++j)
				{
					int index = conns[j]->get_id();
					delete CompList[index];
					CompList[index] = NULL;
					shift_to_end(index);
					CompCount--;
					if (i > index)
						i--; //i is shifted
				}
				delete CompList[i]; // To delete the pointer that pointing to the seleted component
				CompList[i] = NULL; // To make the pointer point to a null pointer
				shift_to_end(i);
				CompCount--;
				lastSelectedComponent = NULL;
				break;
			}
		}
	else
		GetOutput()->PrintMsg("You have to select a certain component before delete!");
}

void ApplicationManager::DeleteAll()
{
	for (int i = 0; i < CompCount; i++) {
		GetOutput()->ClearDrawingArea();
		delete CompList[i]; // To delete the pointer that pointing to the seleted component
		CompList[i] = NULL; // To make the pointer point to a null pointer
		CompCount--;
	}
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
void ApplicationManager::load(ifstream*& iptr)
{
	OutputInterface->ClearDrawingArea();
	Label* Actp = 0;
	int NonConnCount, n;
	string CompType;
	Component* Cptr = NULL;
	GraphicsInfo GfxInfo;
	GfxInfo.x1 = 0;
	GfxInfo.x2 = 0;
	GfxInfo.y1 = 0;
	GfxInfo.y2 = 0;

	*iptr >> NonConnCount;
	for (int i = 0; i < NonConnCount; i++)
	{

		*iptr >> CompType;

		if (CompType == "SWTCH")
			Cptr = new SWITCH(GfxInfo, FANOUT);
		else if (CompType == "LED")
			Cptr = new LED(GfxInfo, FANOUT);
		else if (CompType == "AND2")
			Cptr = new AND2(GfxInfo, FANOUT);
		else if (CompType == "AND3")
			Cptr = new AND3(GfxInfo, FANOUT);
		else if (CompType == "Buff")
			Cptr = new Buff(GfxInfo, FANOUT);
		else if (CompType == "Inv")
			Cptr = new INV(GfxInfo, FANOUT);
		else if (CompType == "NAND2")
			Cptr = new NAND2(GfxInfo, FANOUT);
		else if (CompType == "NOR2")
			Cptr = new NOR2(GfxInfo, FANOUT);
		else if (CompType == "NOR3")
			Cptr = new NOR3(GfxInfo, FANOUT);
		else if (CompType == "OR2")
			Cptr = new OR2(GfxInfo, FANOUT);
		else if (CompType == "XNOR2")
			Cptr = new XNOR2(GfxInfo, FANOUT);
		else if (CompType == "XOR2")
			Cptr = new XOR2(GfxInfo, FANOUT);
		else if (CompType == "XOR3")
			Cptr = new XOR3(GfxInfo, FANOUT);


		if (Cptr)
		{
			AddComponent(Cptr);
			Cptr->load(iptr);
		}
	}
	string fflag;
	*iptr >> fflag;
	if (fflag == "Connections")
		
		do
		{
			*iptr >> n;
		} while (n != -1);
	//here i should read the connections then reach the second flag.
		for (int i = 0; i < CompCount; i++)
		{
			CompList[i]->Draw(OutputInterface);
			if (CompList[i]->get_comp_type() != COMP_TYPES::COMP_CONN && CompList[i]->get_m_Label() != "")
			{
				CompList[i]->Draw(OutputInterface);
				if (CompList[i]->get_comp_type() != COMP_TYPES::COMP_CONN && CompList[i]->get_m_Label() != "")
				{
					Actp = new Label(this, CompList[i], 0);
				}
			}
		}
	if (Actp)
	{
		delete Actp;
		Actp = NULL;
	}
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
	case Clear_all:
		pAct = new Clear(this);
		break;
	case DEL:
		pAct = new Delete(this);
		break;
		// ==================================== Ahmed Alaao ====================================
		//ahmed atta
	case SIMULATE:
		pAct = new SimulateCircuit(this);
		break;
	case CUT_:
		pAct = new CopyCutPaste(this, CUT);
		break;
	case COPY_:
		pAct = new CopyCutPaste(this, COPY);
		break;
	case PASTE_:
		pAct = new CopyCutPaste(this, PASTE);
		break;
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
		pAct = new Save(this, InputInterface->getfilename(OutputInterface), OutputInterface);
		break;
	case LOAD:
		pAct = new Load(this);
		break;
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
		if (CompList[i] != NULL)
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

SWITCH** ApplicationManager::get_switches(int& num) const
{
	num = 0;
	SWITCH** sh = NULL; //the default is null
	for (int i = 0; i < CompCount; ++i)
	{

		if (CompList[i]->GetInputPinStatus(0) == -1)
		{
			num++;
		}
	}
	if (num > 0)
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



LED** ApplicationManager::get_connected_leds(int& num) const
{
	num = 0;
	LED** ld = NULL; //the default is NULL
	for (int i = 0; i < CompCount; ++i)
	{

		if (CompList[i]->GetOutPinStatus() == -1)
		{
			if (CompList[i]->getInputPin()->get_is_connected())
				num++;
		}
	}
	if (num > 0)
		ld = new LED * [num];
	int j = 0;
	for (int i = 0; i < CompCount; ++i)
	{

		if (CompList[i]->GetOutPinStatus() == -1)
		{
			if (CompList[i]->getInputPin()->get_is_connected())
				ld[j++] = (LED*)CompList[i];
		}
	}

	return ld;
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

		//First check if the clicked is a connection
		if (CompList[i]->get_comp_type() == COMP_TYPES::COMP_CONN)
		{
			GraphicsInfo Area;
			//generate area  and check if the click is inside it
			Area.x1 = x1;
			Area.y1 = y1 - 5;
			Area.x2 = x1 + 20;
			Area.y2 = y1 + 5;
			if (Area.x1 <= x && x <= Area.x2 && Area.y1 <= y && y <= Area.y2) {
				CompList[i]->set_is_selected(true); // Set the is_select data member to true.
				comptype = CompList[i]->get_comp_type();
				target = i;
				break;
			}

			//repeat for area 2
			Area.x1 = x1 + 15;
			Area.y1 = y2 - 5;
			Area.x2 = x2;
			Area.y2 = y2 + 5;
			if (Area.x1 <= x && x <= Area.x2 && Area.y1 <= y && y <= Area.y2) {
				CompList[i]->set_is_selected(true); // Set the is_select data member to true.
				comptype = CompList[i]->get_comp_type();
				target = i;
				break;
			}



			if (y1 > y2)
			{
				Area.x1 = x1 + 15;
				Area.y1 = y2 - 5;
				Area.x2 = x1 + 20;
				Area.y2 = y1 + 5;


			}
			else
			{
				Area.x1 = x1 + 15;
				Area.y1 = y1 - 5;
				Area.x2 = x1 + 20;
				Area.y2 = y2 + 5;

			}
			if (Area.x1 <= x && x <= Area.x2 && Area.y1 <= y && y <= Area.y2) {
				CompList[i]->set_is_selected(true); // Set the is_select data member to true.
				comptype = CompList[i]->get_comp_type();
				target = i;
				break;
			}






		}
		else if (x1 <= x && x <= x2 && y1 <= y && y <= y2) {
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


/*
bool ApplicationManager::Check_pins_to_connect(Component* distComp, InputPin* inPin, GraphicsInfo& GInfo, InputPin*& selected_pin)
{
	int no_input_pins = distComp->getNoOfInputpins();
	for (int j = 0; j < no_input_pins; j++)
	{
		bool isConnected = inPin[j].get_is_connected();
		if (isConnected == false)
		{
			selected_pin = &inPin[j];
			inPin[j].set_is_connected(true);
			//break;
			//return true;


			COMP_TYPES type = distComp->get_comp_type();
			int a1, b1, a2, b2;
			distComp->getm_GfxInfo(a1, b1, a2, b2);

			switch (type)
			{
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
	return true;
}
*/


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