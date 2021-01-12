#include "Action.h"
#include "Load.h"
#include <fstream>
#include <iostream>
using namespace std;

Load::Load(ApplicationManager* pApp, string name, Output* outp)
	:Action(pApp)
{
	this->name = name;
	this->outp = outp;
	input = new ifstream;
}


void Load::ReadActionParameters()
{
}

void Load::Execute()
{
	input->open(name + ".txt", ios::in);
	if (input->is_open())
	{
		pManager->load(input);
		if (input->eof())
			input->close();
	}
	else
		outp->PrintMsg("Error: file not found!");
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
