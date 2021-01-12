#include "Action.h"
#include "Load.h"
#include <fstream>
#include <iostream>
using namespace std;

Load::Load(ApplicationManager* pApp)
	:Action(pApp)
{
	optr = pManager->GetOutput();
	iptr = pManager->GetInput();
	input = new ifstream;
}


void Load::ReadActionParameters()
{

	name = iptr->GetFileName(optr, 2);

}

void Load::Execute()
{
	ReadActionParameters();
	if (name == "")
		return;
	input->open(name + ".txt", ios::in);
	if (input->is_open())
	{
		pManager->load(input);
		if (input->eof())
			input->close();
	}
	else
		optr->PrintMsg("Error: file not found!");
}

void Load::Undo()
{
}

void Load::Redo()
{
}

Load::~Load()
{
	delete input;
	input = NULL;
}
