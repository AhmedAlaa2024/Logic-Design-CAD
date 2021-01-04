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
using namespace std;

ApplicationManager::ApplicationManager(): lastSelectedComponent(NULL)
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
		if(CompList[i] != 0 && CompList[i]->get_comp_type() != COMP_TYPES::COMP_CONN)
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
	int NonConnCount;
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
	//here i should read the connections then reach the second flag.
	for (int i = 0; i < CompCount; i++)
	{
		CompList[i]->Draw(OutputInterface);
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