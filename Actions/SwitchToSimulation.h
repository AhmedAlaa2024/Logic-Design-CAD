#ifndef _SwitchToSimulation_H
#define _SwitchToSimulation_H

#include "action.h"


class SwitchToSimulation : public Action
{

public:
	SwitchToSimulation(ApplicationManager* pApp);
	virtual ~SwitchToSimulation();


	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void ReadActionParameters();
	virtual void Undo();
	virtual void Redo();


};

#endif