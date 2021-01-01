#ifndef SAVE_H
#define SAVE_H

#include "Action.h"
#include "..\ApplicationManager.h"
#include <fstream>
#include <iostream>
using namespace std;

class Save : public Action
{
	ofstream* output;
public:
	Save(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();

	virtual ~Save();
};

#endif