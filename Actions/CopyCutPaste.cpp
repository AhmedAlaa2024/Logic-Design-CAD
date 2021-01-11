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
	pManager->DeleteComponent();
	
	


}



void CopyCutPaste::paste()
{

	ActionType a = pManager->get_clipboard();
	if (a) {
		pManager->Execute_Add_Gate_action(a);
	}
	
}


void CopyCutPaste::Undo()
{}

void CopyCutPaste::Redo()
{}

