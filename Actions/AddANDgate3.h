#ifndef _ADD_AND_GATE3_H
#define _ADD_AND_GATE3_H

#include "Action.h"
#include "..\Components\AND3.h"

class AddANDgate3 :
    public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
public:
	AddANDgate3(ApplicationManager* pApp);
	virtual ~AddANDgate3(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif