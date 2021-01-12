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
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg(" Add Component: Click to add the component");


}

void Add::Execute()
{
	Output* pOut = pManager->GetOutput();

	pOut->CreateDesignToolBarComponent();

	Action* pAct = NULL;
	ActionType a = pManager->AddGate();
	pManager->Execute_Add_Gate_action(a);


}




void Add::Undo()
{

	pManager->DeleteComponent(1);
}

void Add::Redo()
{}


