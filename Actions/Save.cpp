#include "Save.h"

#include <fstream>
#include <iostream>
using namespace std;

Save::Save(ApplicationManager* pApp)
	:Action(pApp)
{
}

Save::~Save()
{
}

void Save::ReadActionParameters()
{
}

void Save::Execute()
{
	output.open("output.txt", ios::out);
	pManager->save(&output);
	output.close();
}

void Save::Undo()
{
}

void Save::Redo()
{
}
