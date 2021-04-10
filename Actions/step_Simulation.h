#ifndef _step_Simulation_H
#define _step_Simulation_H

#include "action.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
//#include "..\Components\LED.h"
//#include "..\Components\SWITCH.cpp"
//#include "..\Components\Connection.h"

class step_Simulation : public Action
{

public:
	step_Simulation(ApplicationManager* pApp);
	virtual ~step_Simulation();


	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void ReadActionParameters();
	virtual void Undo();
	virtual void Redo();


};

#endif