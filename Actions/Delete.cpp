#include "Delete.h"
// ============================== Ahmed Alaa edited here ==============================

Delete::Delete(ApplicationManager* pApp) : Action(pApp)
{
	Execute();
}

void Delete::ReadActionParameters()
{
}

void Delete::Execute()
{
	pManager->DeleteComponent(); // To delete the last selected component
}

void Delete::Undo()
{
}

void Delete::Redo()
{
}
// ==================================== Ahmed Alaa ====================================