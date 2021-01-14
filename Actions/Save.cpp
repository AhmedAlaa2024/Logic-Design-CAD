#include "Save.h"

#include <fstream>
#include <iostream>
using namespace std;

Save::Save(ApplicationManager* pApp, int flag)
	:Action(pApp)
{
	this->name = name;
	this->flag = flag;
	optr = pManager->GetOutput();
	iptr = pManager->GetInput();
	output = NULL;
	Temp = NULL;
	lastSave = NULL;
}

void Save::ReadActionParameters()
{
	if (flag)
		name = iptr->GetFileName(optr, 1);
	else
		name = iptr->GetFileName(optr);

}

void Save::Execute()
{
	ReadActionParameters();
	if (name == "")
		return;
	output = new ofstream("SavedCircuits/" + name + ".txt");
	lastSave = new ofstream;
	if (output->is_open())
	{
		int flag = pManager->save(output);
		if (flag == -1)
		{

			lastSave->open("ForExitAction/LastSavedCircuit.txt");
			if (lastSave->is_open())
			{
				Temp = new ifstream("SavedCircuits/" + name + ".txt");
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