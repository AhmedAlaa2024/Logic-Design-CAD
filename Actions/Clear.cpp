	// ============================== Ahmed Alaa edited here ==============================
#include "Clear.h"

Clear::Clear(ApplicationManager* pApp) : Action(pApp)
{
}

void Clear::ReadActionParameters()
{
}

void Clear::Execute()
{
	pManager->DeleteAll();
}

void Clear::Undo()
{
}

void Clear::Redo()
{
}
	// ==================================== Ahmed Alaa ====================================