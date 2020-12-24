#include "Exit.h"
#include "..\ApplicationManager.h"

Exit::Exit(ApplicationManager* pApp) :Action(pApp)
{
}

Exit::~Exit(void)
{
}


void Exit::Execute()
{
	//wrong
	
	/*Output* pOut = pManager->GetOutput();
	if (pOut) {
		
		pOut->destroyWind();
		pOut = NULL;

	}*/
}

void Exit::ReadActionParameters()
{

}

void Exit::Undo()
{}

void Exit::Redo()
{}

