#include "Add.h"
#include "..\ApplicationManager.h"


Add::Add(ApplicationManager* pApp) :Action(pApp), Cx(0), Cy(0)
{
}

Add::~Add(void)
{
}


void Add::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();

	//Print Action Message
	pOut->PrintMsg(" Add Component: Choose the component to add");


}

void Add::Execute()
{
	ReadActionParameters();

	Output* pOut = pManager->GetOutput();

	pOut->CreateDesignToolBarComponent();

	//Action* pAct = NULL;
	ActionType a = pManager->AddGate();
	pManager->Execute_Add_Gate_action(a);


}




void Add::Undo()
{}

void Add::Redo()
{}


