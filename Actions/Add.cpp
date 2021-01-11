#include "Add.h"
#include "..\ApplicationManager.h"
#include "AddANDgate2.h"
#include "AddANDgate3.h"
#include "AddBUFFER.h"
#include "AddINVgate.h"
#include "AddLED.h"
#include "AddNAND2gate.h"
#include "AddNOR2gate.h"
#include "AddNORgate3.h"
#include "AddORgate2.h"
#include "AddSWITCH.h"
#include "AddXNORgate2.h"
#include "AddXORgate2.h"
#include "AddXORgate3.h"
#include "Connect.h"


Add::Add(ApplicationManager* pApp) :Action(pApp)
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

	//Wait for User Input
	//pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	//pOut->ClearStatusBar();

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
{}

void Add::Redo()
{}


