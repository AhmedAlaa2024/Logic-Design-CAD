#ifndef _EXIT_H
#define _EXIT_H

#include "Action.h"
#include "..\ApplicationManager.h"
#include <fstream>
#include <iostream>
using namespace std;

class Exit : public Action
{
	Action* Actp;
	Output* outp;
	Input* inp;
	ifstream* lastSaved;
	ifstream *Current;
	ofstream* current;
public:
	Exit(ApplicationManager* pApp, Output*, Input*);
	
	//Execute action (code depends on action type)
	virtual void Execute();

	bool ReadActionParameters(int i);

	virtual void ReadActionParameters();
	virtual void Undo();
	virtual void Redo();

	virtual ~Exit(void);
};

#endif