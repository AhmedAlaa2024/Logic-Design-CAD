#include "Save.h"

#include <fstream>
#include <iostream>
using namespace std;

Save::Save(ApplicationManager* pApp, string name, Output* optr)
	:Action(pApp)
{
	this->optr = optr;
	output = new ofstream(name+ ".txt", ios::out);
}

Save::~Save()
{
	delete output;
	output = 0;
}

void Save::ReadActionParameters()
{
}

void Save::Execute()
{
	pManager->save(output);
	output->close();
	optr->PrintMsg("Saved successfully!");
	
}

void Save::Undo()
{
}

void Save::Redo()
{
}
