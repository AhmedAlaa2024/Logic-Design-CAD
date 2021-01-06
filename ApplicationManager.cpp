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
bool ApplicationManager::CheckInsideArea(int i, int Cx, int Cy)
{
	bool d = CompList[i]->InsideArea(Cx, Cy);
	return d;
}

COMP_TYPES ApplicationManager::CompType(int i)
{
	
	COMP_TYPES type;
	type = CompList[i]->get_comp_type();
	return type;
}

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
/*
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