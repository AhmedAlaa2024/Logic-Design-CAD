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
#include <sstream>

#include "Actions/Connect.h"

//==============DOAA===========
#include "Actions/AddANDgate3.h"
#include "Actions/AddBUFFER.h"
#include "Actions/AddINVgate.h"
#include "Actions/AddLED.h"
#include "Actions/AddNAND2gate.h"
#include "Actions/AddNOR2gate.h"
#include "Actions/AddNORgate3.h"
#include "Actions/AddORgate2.h"
#include "Actions/AddSWITCH.h"
#include "Actions/AddXNORgate2.h"
#include "Actions/AddXORgate2.h"
#include "Actions/AddXORgate3.h"
#include "Actions/CircuitProding.h"
#include "Actions/CopyCutPaste.h"
#include "Actions/CreateTruthTable.h"
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
	CompCount--;

	for (int i = 0; i < CompCount; ++i)
	{
		if (CompList[i]->get_id() > i)
			CompList[i]->set_id(CompList[i]->get_id() - 1);
	}

}



void ApplicationManager::DeleteComponent()
{
	if (lastSelectedComponent != nullptr) {

		for (int i = 0; i < CompCount; i++) // To iterate on all of the existing components
		{

			if (lastSelectedComponent == CompList[i]) // To make the following codes on the lastSelectedComponent 
			{
				// The delete of the pointer to the input and output pins of the selected component is the responsibilty of the desturctor of the class Gate

				if (lastSelectedComponent->get_comp_type() == COMP_TYPES::COMP_CONN)
				{


					Connection* conn = (Connection*)lastSelectedComponent; // To make a pointer to the last selected component and make down casting to it
					GetOutput()->Clear_Connection_DrawingArea(conn->getGraphicsInfo()); // To redraw a white lines above the connections
					conn->getDestPin()->set_is_connected(false); // To make a notation to simulation that the DestPin is not selected anymore
					int index = lastSelectedComponent->get_id();
					conn->getSourcePin()->decrease_m_Conn(index); // To decrease the m_Conn by 1
					delete CompList[index]; // To deallocte the connection as a component from CompList
					CompList[index] = NULL; // To make the deleted connection points to NULL.
					shift_to_end(index); // To shift the deleted component to the end of the array to prevent any using for it
					if (i > index)
						i--; //i is shifted
					break;

				}

				GetOutput()->ClearComponentArea(lastSelectedComponent->getGraphicsInfo()); // To draw a white rectangle above the component
				GetOutput()->ClearLabelArea(lastSelectedComponent->getGraphicsInfo(), (lastSelectedComponent->get_m_Label()).size()); // To write a null string with the same lenth of the old label
				int no_conns;


				// first the output pin
				OutputPin* out_pin = lastSelectedComponent->getOutputPin();
				if (out_pin) {
					Connection** conns = out_pin->get_connections(no_conns);

					for (int j = 0; j < no_conns; ++j)
					{
						Connection* conn = conns[j];
						if (conn)
						{
							conn->getDestPin()->set_is_connected(false); // To make a notation to simulation that the DestPin is not selected anymore
							GetOutput()->Clear_Connection_DrawingArea(conn->getGraphicsInfo()); // To redraw a white lines above the connections


							int index = conn->get_id();
							out_pin->decrease_m_Conn(index); // To decrease the number of connnections by 1
							delete CompList[index]; // To deallocte the connection as a component from CompList
							CompList[index] = NULL; // To make the deleted connection points to NULL.
							shift_to_end(index); // To shift the deleted component to the end of the array to prevent any using for it

							if (i > index)
								i--; //i is shifted}

						}
					}

				}


				// then delete the input pins
				int no_input_pins = lastSelectedComponent->getNoOfInputpins(); // To get the number of input pins of the last selected component


				InputPin* input_pin = lastSelectedComponent->getInputPin();
				if (input_pin) {
					for (int i = 0; i < no_input_pins; ++i)
					{

						Connection* conn = input_pin[i].get_connection();

						if (conn) {
							GetOutput()->Clear_Connection_DrawingArea(conn->getGraphicsInfo());
							conn->getDestPin()->set_is_connected(false); // To make a notation to simulation that the DestPin is not selected anymore
							int index = conn->get_id();
							conn->getSourcePin()->decrease_m_Conn(index); // To decrease the number of connnections by 1

							delete CompList[index]; // To deallocte the connection as a component from CompList
							CompList[index] = NULL; // To make the deleted connection points to NULL.
							shift_to_end(index); // To shift the deleted component to the end of the array to prevent any using for it
							if (i > index)
								i--; //i is shifted
						}
					}
				}
				delete CompList[i]; // To delete the pointer that pointing to the seleted component
				CompList[i] = NULL; // To make the pointer point to a null pointer

				shift_to_end(i); // To shift the deleted component to the end of the array to prevent any using for it


				lastSelectedComponent = NULL;
				break;

			}
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
	}
	CompCount = 0;
	lastSelectedComponent = NULL;
}

ApplicationManager::ApplicationManager() : lastSelectedComponent(NULL)
{
	CompCount = 0;
	Clipboard = ADD_Gate;
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

Component* ApplicationManager::get_comp_at(int index) const
{
	return CompList[index];
}

bool ApplicationManager::validate_circuit() const
{
	for (int i = 0; i < CompCount; ++i)
	{
		Component* pComp = CompList[i];
		COMP_TYPES type = pComp->get_comp_type();
		if (type == COMP_TYPES::COMP_CONN)
			continue;
		if (type == COMP_TYPES::COMP_LED) //if its a led //check for input only
		{
			if (pComp->GetInpuPin(0)->get_is_connected() == false)
			{
				return false;
			}
			continue;

		}

		//if its a switch //check for output pin only
		if (type == COMP_TYPES::COMP_SWITCH) //if its a led //check for input only
		{
			if (pComp->getOutputPin()->get_is_connected() == false)
			{
				return false;
			}
			continue;

		}

		//now its just a gate

		if (pComp->getOutputPin()->get_is_connected() == false)
		{
			return false;
		}

		for (int i = 0; i < pComp->getNoOfInputpins(); ++i)
		{
			if (pComp->GetInpuPin(i)->get_is_connected() == false)
			{
				return false;
			}
		}



	}

	return true;
}


int ApplicationManager::save(ofstream*& fptr)
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
	return -1;
}
void ApplicationManager::load(ifstream*& iptr)
{
	DeleteAll();
	Label* Actp = NULL;
	Connect* CActp = NULL;
	int NonConnCount;
	string CompType;
	Component* Cptr = NULL;
	Component* Cptr2 = NULL;
	Component* Cptr1 = NULL;
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
	{
		Cptr = NULL;
		Cptr2 = NULL;
		int connCount;
		int fID, sID, PinNo;
		string s, sflag;
		stringstream Read;
		getline(*iptr, s, '-');
		*iptr >> sflag;
		Read << s;
		connCount = count(s.begin(), s.end(), '\n') - 1;
		for (int i = 0; i < connCount; i++)
		{
			CActp = new Connect(this);
			Read >> fID >> sID >> PinNo;
			PinNo--;
			for (int j = 0; j < CompCount; j++)
			{
				if (CompList[j])
				{
					if (CompList[j]->get_id() == fID)
					{
						Cptr = CompList[j];
						break;
					}
				}
			}
			for (int j = 0; j < CompCount; j++)
			{
				if (CompList[j])
				{
					if (CompList[j]->get_id() == sID)
					{
						Cptr2 = CompList[j];
						break;
					}
				}
			}
			CActp->setDisPinGInfo(Cptr2->get_comp_type(), PinNo, Cptr2->getGraphicsInfo(), GfxInfo);
			CActp->setSrcPinGInfo(Cptr->getGraphicsInfo(), GfxInfo);
			InputPin* Inp = Cptr2->GetInpuPin(PinNo);
			if (Inp)
			{
				Inp->set_is_connected(true);
				Cptr1 = new Connection(GfxInfo, Cptr->getOutputPin(), Inp);
				Connection* ConnPtr = (Connection*)Cptr1;
				(Cptr->getOutputPin())->ConnectTo(ConnPtr);
				Inp->ConnectTo(ConnPtr);
				AddComponent(Cptr1);
			}
		}
		if (CActp)
		{
			delete CActp;
			CActp = NULL;
		}
	}
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->get_comp_type() != COMP_TYPES::COMP_CONN && CompList[i]->get_m_Label() != "")
		{
			Actp = new Label(this, CompList[i], 0);
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
	case EDIT_Label:
		pAct = new Edit(this, lastSelectedComponent);
		break;
	case Clear_all:
		pAct = new Clear(this);
		break;
	case DEL:
		pAct = new Delete(this);
		break;
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
	case PRODING:
		pAct = new CircuitProding(this);
		break;
	case CREATE_TRUTH_TABLE:
		pAct = new CreateTruthTable(this);
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
		pAct = new Save(this);
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

void ApplicationManager::Execute_Add_Gate_action(ActionType a)
{
	Action* pAct = NULL;

	switch (a)
	{
	case ADD_AND_GATE_2:
		pAct = new AddANDgate2(this);
		break;
	case ADD_OR_GATE_2:
		pAct = new AddORgate2(this);
		break;
	case ADD_Buff:
		pAct = new AddBUFFER(this);
		break;
	case ADD_INV:
		pAct = new AddINVgate(this);
		break;
	case ADD_NAND_GATE_2:
		pAct = new AddNANDgate2(this);
		break;
	case ADD_NOR_GATE_2:
		pAct = new AddNORgate2(this);
		break;
	case ADD_XOR_GATE_2:
		pAct = new AddXORgate2(this);
		break;
	case ADD_XNOR_GATE_2:
		pAct = new AddXNORgate2(this);
		break;
	case ADD_AND_GATE_3:
		pAct = new AddANDgate3(this);
		break;
	case ADD_NOR_GATE_3:
		pAct = new AddNORgate3(this);
		break;
	case ADD_XOR_GATE_3:
		pAct = new AddXORgate3(this);
		break;
		//case ADD_XNOR_GATE_3:		
	case ADD_Switch:
		pAct = new AddSWITCH(this);
		break;
	case ADD_LED:
		pAct = new AddLED(this);
		break;
	}
	if (pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
		OutputInterface->ClearWindow();

	}

}

////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{

	for (int i = 0; i < CompCount; i++)
		if (CompList[i] != NULL)
		{
			CompList[i]->Draw(OutputInterface);
			if (CompList[i]->get_m_Label() != "")
				Label(this, CompList[i]).Execute();
		}

}

bool ApplicationManager::set_clipboard()
{
	if (lastSelectedComponent) {
		COMP_TYPES a = lastSelectedComponent->get_comp_type();

		switch (a)
		{
		case COMP_TYPES::COMP_SWITCH:
			Clipboard = ADD_Switch;
			break;


		case COMP_TYPES::COMP_LED:
			Clipboard = ADD_LED;
			break;

		case COMP_TYPES::AND_2:
			Clipboard = ADD_AND_GATE_2;
			break;


		case COMP_TYPES::AND_3:
			Clipboard = ADD_AND_GATE_3;

			break;

		case COMP_TYPES::INV_:
			Clipboard = ADD_INV;
			break;

		case COMP_TYPES::NAND_2:
			Clipboard = ADD_NAND_GATE_2;
			break;

		case COMP_TYPES::NOR_2:
			Clipboard = ADD_NOR_GATE_2;
			break;

		case COMP_TYPES::NOR_3:
			Clipboard = ADD_NOR_GATE_3;
			break;

		case COMP_TYPES::Buff_:
			Clipboard = ADD_Buff;
			break;

		case COMP_TYPES::OR_2:
			Clipboard = ADD_OR_GATE_2;
			break;

		case COMP_TYPES::XNOR_2:
			Clipboard = ADD_XNOR_GATE_2;
			break;

		case COMP_TYPES::XOR_2:
			Clipboard = ADD_XOR_GATE_2;

			break;

		case COMP_TYPES::XOR_3:
			Clipboard = ADD_XOR_GATE_3;
			break;


		default:
			OutputInterface->PrintMsg("Please select only a Gate...");
			return false;




		}
	}
	else {
		OutputInterface->PrintMsg("Please select a component...");
		return false;
	}
	return true;
}



ActionType ApplicationManager::get_clipboard() const
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





ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;

}