#ifndef LOAD_H
#define LOAD_H

#include "Action.h"
#include "..\ApplicationManager.h"
#include <fstream>
#include <iostream>
using namespace std;

class Load : public Action
{
	ifstream* input;
	Output* optr;
	Input* iptr;
	string name;
public:
	Load(ApplicationManager* pApp);


	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();

	virtual ~Load();
};

#endif