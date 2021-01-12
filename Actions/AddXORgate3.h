#ifndef _ADD_XOR_GATE3_H
#define _ADD_XOR_GATE3_H

#include "Action.h"
#include "..\Components\XOR3.h"

class AddXORgate3: public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
public:
	AddXORgate3(ApplicationManager* pApp);
	virtual ~AddXORgate3(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif