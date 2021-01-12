#ifndef _ADD_XNOR_GATE2_H
#define _ADD_XNOR_GATE2_H

#include "Action.h"
#include "..\Components\XNOR2.h"

class AddXNORgate2 :
    public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
public:
	AddXNORgate2(ApplicationManager* pApp);
	virtual ~AddXNORgate2(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif