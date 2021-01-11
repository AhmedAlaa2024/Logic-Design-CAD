#include "Action.h"
#include "Load.h"
#include <fstream>
#include <iostream>
using namespace std;

Load::Load(ApplicationManager* pApp)
	:Action(pApp)
{
	input = new ifstream;
}

void Load::ReadActionParameters()
{
}

void Load::Execute()
{
	input->open("InputFile.txt", ios::in);
	if (input->is_open())
	{
		pManager->load(input);
		if (input->eof())
			input->close();
	}
	
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
