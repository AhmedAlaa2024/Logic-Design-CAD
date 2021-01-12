#ifndef _ADD_SWITCH_H
#define _ADD_SWITCH_H

#include "Action.h"
#include "..\Components\SWITCH.h"

class AddSWITCH :
    public Action
{
private:
	//Parameters for rectangular area to be occupied by the switch
	int Cx, Cy;	//Center point of the switch
public:
	AddSWITCH(ApplicationManager* pApp);
	virtual ~AddSWITCH(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif