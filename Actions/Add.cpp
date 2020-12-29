#include "Add.h"
#include "..\ApplicationManager.h"
#include "AddANDgate2.h"
#include "AddANDgate3.h"
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
	//pOut->CreateDesignToolBarComponent();
	//ApplicationManager* pApp;
	Action* pAct = NULL;
	ActionType a = pManager->AddGate();
	switch (a)
	{
	    case ADD_AND_GATE_2:
			pAct = new AddANDgate2(pManager);
			break;
		case ADD_OR_GATE_2:	
			pAct = new AddORgate2(pManager);
			break;
		case ADD_Buff:
			//pAct = new AddANDgate2(pManager);
			//break;
		case ADD_INV:	
			pAct = new AddINVgate(pManager);
			break;
		case ADD_NAND_GATE_2:
			pAct = new AddNANDgate2(pManager);
			break;
		case ADD_NOR_GATE_2:
			pAct = new AddNORgate2(pManager);
			break;
		case ADD_XOR_GATE_2:
			pAct = new AddXORgate2(pManager);
			break;
		case ADD_XNOR_GATE_2:
			pAct = new AddXNORgate2(pManager);
			break;
		case ADD_AND_GATE_3:
			pAct = new AddANDgate3(pManager);
			break;
		//case ADD_OR_GATE_3:
			//pAct = new AddORgate3(pManager);
			//break;
		//case ADD_NAND_GATE_3:		
		case ADD_NOR_GATE_3:
			pAct = new AddNORgate3(pManager);
			break;
		case ADD_XOR_GATE_3:
			pAct = new AddXORgate3(pManager);
			break;
		//case ADD_XNOR_GATE_3:		
		case ADD_Switch:
			pAct = new AddSWITCH(pManager);
			break;
		case ADD_LED:
			pAct = new AddLED(pManager);
			break;
		//case ADD_CONNECTION:		
			//pAct = new Connect(pManager);
			//break;
	}
	if (pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
		pOut->ClearWindow();
		
	}



	//Get Center point of the Gate
	//ReadActionParameters();
	//Add* pA = new Add(GInfo, FANOUT);
	//pManager->AddComponent(pA);
	//ActionType a = pManager->GetUserAction();


/*
	//Calculate the rectangle Corners
	int Len = UI.Gate_Height;
	int Wdth = UI.Gate_Width;

	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	AND2* pA = new AND2(GInfo, FANOUT);
	pManager->AddComponent(pA);
	*/
}




void Add::Undo()
{}

void Add::Redo()
{}


