#include "Exit.h"
#include "..\ApplicationManager.h"
#include <iostream>
using namespace std;
Exit::Exit(ApplicationManager* pApp) :Action(pApp)
{
	outp = pManager->GetOutput();
	inp = pManager->GetInput();
	lastSaved = new ifstream("ForExitAction/LastSavedCircuit.txt");
	current = new ofstream("ForExitAction/TempforExit.txt");
	Current = NULL;
	Actp = NULL;
}

void Exit::Execute()
{
	bool isSaved = ReadActionParameters(1);
	current->close();
	current->open("ForExitAction/TempforExit.txt", ios::trunc);
	if (current->is_open())
	{
		current->close();
	}
	lastSaved->close();
	if (isSaved)
		return;
	Actp = new Save(pManager, 1);
	if (Actp)
		Actp->Execute();
	current->open("ForExitAction/LastSavedCircuit.txt", ios::trunc);
	if (current->is_open())
	{
		current->close();
	}
}

bool Exit::ReadActionParameters(int i)
{
	string ffile, sfile;
	int fflag, sflag, iflag = 0;
	if (current->is_open() && lastSaved->is_open())
	{
		if(pManager)
			iflag = pManager->save(current);
		if (iflag == -1)
			Current = new ifstream("ForExitAction/TempforExit.txt");
		getline(*lastSaved, ffile, '-');
		ffile += "-1";
		getline(*Current, sfile, '-');
		sfile += "-1";

		Current->close();
		if (ffile == sfile)
		{
			return true;
		}
	}
	return false;
}

void Exit::ReadActionParameters()
{
}

void Exit::Undo()
{}

void Exit::Redo()
{}

Exit::~Exit(void)
{
	if (lastSaved)
	{
		delete lastSaved;
		lastSaved = 0;
	}
	if (current)
	{
		delete current;
		current = 0;
	}
	if (Current)
	{
		delete Current;
		Current = 0;
	}
}

