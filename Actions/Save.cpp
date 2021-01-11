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
		output = new ofstream(name + ".txt");
	lastSave = new ofstream;
}

void Save::ReadActionParameters()
{
}

void Save::Execute()
{
	if (output->is_open())
	{
		int flag = pManager->save(output);
		if (flag == -1)
		{

			lastSave->open("LastSavedCircuit.txt");
			if (lastSave->is_open())
			{
				Temp = new ifstream(name + ".txt");
				if (Temp->is_open())
				{
					getline(*Temp, temp, '-');
					temp += "-1";
					Temp->close();
				}
			}
			*lastSave << temp.c_str();
			optr->PrintMsg("Saved successfully!");
		}
		else
			optr->PrintMsg("Failed to save!");
	}
	output->close();
	lastSave->close();
}

void Save::Undo()
{
}

void Save::Redo()
{
}

Save::~Save()
{
	if (output)
	{
		delete output;
		output = 0;
	}
	if (lastSave)
	{
		delete lastSave;
		lastSave = 0;
	}
	if (Temp)
	{
		delete Temp;
		Temp = 0;
	}
	
}