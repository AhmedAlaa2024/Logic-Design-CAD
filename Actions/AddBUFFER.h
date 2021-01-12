#ifndef _ADD_BUFFER_H
#define _ADD_BUFFER_H

#include "Action.h"
#include "..\Components\Buff.h"

class AddBUFFER :
	public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
public:
	AddBUFFER(ApplicationManager* pApp);
	virtual ~AddBUFFER(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();
	
	virtual void Undo();
	virtual void Redo();


};

#endif