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

void Save::ReadActionParameters()
{
}

void Save::Execute()
{
	int flag = pManager->save(output);
	if (flag == -1)
	{
		output->close();
		optr->PrintMsg("Saved successfully!");
	}
	else
		optr->PrintMsg("Failed to save!");
}

void Save::Undo()
{
}

void Save::Redo()
{
}

Save::~Save()
{
	delete output;
	output = 0;
}