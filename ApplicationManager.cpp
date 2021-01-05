#include "ApplicationManager.h"
#include "Components/Connection.h"

#include <iostream>

#include "Actions/Connect.h"
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

//======================================Doaa
/*
int ApplicationManager::getCompCount()
{
	return CompCount;
}
*/


ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;

}