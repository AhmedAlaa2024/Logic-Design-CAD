#include "CopyCutPaste.h"


#include "AddANDgate3.h"
#include "AddBUFFER.h"
#include "AddINVgate.h"
#include "AddSWITCH.h"
#include "AddLED.h"
#include "AddNAND2gate.h"
#include "AddNOR2gate.h"
#include "AddNORgate3.h"
#include "AddORgate2.h"
#include "AddSWITCH.h"
#include "AddSWITCH.h"
#include "AddXNORgate2.h"
#include "AddXORgate2.h"
#include "AddXORgate3.h"

#include "..\ApplicationManager.h"

CopyCutPaste::CopyCutPaste(ApplicationManager* pApp, int mode) :Action(pApp), MODE(mode)
{
}

CopyCutPaste::~CopyCutPaste(void)
{
}

void CopyCutPaste::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();


	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void CopyCutPaste::Execute()
{
	if (MODE == COPY)
		copy();
	else if (MODE == CUT)
		cut();
	else
		paste();

}
void CopyCutPaste::copy()
{
	pManager->set_clipboard();
	pManager->DeselectComponentExcept();

}



void CopyCutPaste::cut()
{
	pManager->set_clipboard();
	auto comp = pManager->GetLastSelectedComponent();
	//TODO: DELETE the component
	


}



void CopyCutPaste::paste()
{

	COMP_TYPES a = pManager->get_clipboard();

	Action* pAct = NULL;
	switch (a)
	{
	case COMP_TYPES::COMP_SWITCH:
		pAct = new AddSWITCH(pManager);
		break;

	case COMP_TYPES::COMP_LED:
		pAct = new AddLED(pManager);
		break;

	case COMP_TYPES::AND_2:
		pAct = new AddANDgate2(pManager);
		break;

	case COMP_TYPES::AND_3:
		pAct = new AddANDgate3(pManager);
		break;

	case COMP_TYPES::INV_:
		pAct = new AddINVgate(pManager);
		break;

	case COMP_TYPES::NAND_2:
		pAct = new AddNANDgate2(pManager);
		break;

	case COMP_TYPES::NOR_2:
		pAct = new AddNORgate2(pManager);
		break;

	case COMP_TYPES::NOR_3:
		pAct = new AddNORgate3(pManager);
		break;

	case COMP_TYPES::Buff_:
		pAct = new AddBUFFER(pManager);
		break;

	case COMP_TYPES::OR_2:
		pAct = new AddORgate2(pManager);
		break;

	case COMP_TYPES::XNOR_2:
		pAct = new AddXNORgate2(pManager);
		break;

	case COMP_TYPES::XOR_2:
		pAct = new AddXORgate2(pManager);
		break;

	case COMP_TYPES::XOR_3:
		pAct = new AddXORgate3(pManager);
		break;


	default:
		break;



	}

	if (pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
	
}


void CopyCutPaste::Undo()
{}

void CopyCutPaste::Redo()
{}

