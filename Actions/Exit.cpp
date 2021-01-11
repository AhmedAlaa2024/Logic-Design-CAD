#include "Exit.h"
#include "..\ApplicationManager.h"
#include <iostream>
using namespace std;
Exit::Exit(ApplicationManager* pApp, Output* outp, Input* inp) :Action(pApp)
{
	this->outp = outp;
	this->inp = inp;
	lastSaved = new ifstream("LastSavedCircuit.txt");
	current = new ofstream("TempforExit.txt");
}

void Exit::Execute()
{
	bool isSaved = ReadActionParameters(1);
	current->close();
	current->open("TempforExit.txt", ios::trunc);
	if (current->is_open())
	{
		current->close();
	}
	lastSaved->close();
	if (isSaved)
		return;
	string name = inp->getfilename(outp, 1);
	if(name != "")
		Actp = new Save(pManager, name, outp);
	current->open("LastSavedCircuit.txt", ios::trunc);
	if (current->is_open())
	{
		current->close();
	}
}

bool Exit::ReadActionParameters(int i)
{
	string ffile, sfile;
	int fflag, sflag, flag;
	if (current->is_open() && lastSaved->is_open())
	{
		if(pManager)
		flag = pManager->save(current);
		if (flag == -1)
			Current = new ifstream("TempforExit.txt");
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

