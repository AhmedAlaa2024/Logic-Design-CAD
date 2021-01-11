#include "Save.h"

#include <fstream>
#include <iostream>
using namespace std;

Save::Save(ApplicationManager* pApp, string name, Output* optr)
	:Action(pApp)
{
	this->name = name;
	this->optr = optr;
	if (name != "")
		output = new fstream(name + ".txt",std::fstream::out);
	lastSave = new ofstream;
	cout << lastSave << endl;
}

void Save::ReadActionParameters()
{
}

void Save::Execute()
{
	int flag = pManager->save(output);
	if (flag == -1)
	{

		lastSave->open("LastSavedCircuit.txt");
		if (lastSave->is_open())
		{
			output->open(name + ".txt", std::fstream::in);
			if (output->is_open())
			{
				getline(*output, temp, '-');
				cout << temp << endl;
			}
		}
		*lastSave << temp;
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