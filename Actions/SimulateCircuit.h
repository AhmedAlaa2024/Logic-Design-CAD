#ifndef _SimulateCircuit_H
#define _SimulateCircuit_H

#include "action.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
//#include "..\Components\LED.h"
//#include "..\Components\SWITCH.cpp"
//#include "..\Components\Connection.h"

class SimulateCircuit : public Action
{

public:
	SimulateCircuit(ApplicationManager* pApp);
	virtual ~SimulateCircuit();


	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void ReadActionParameters();
	virtual void Undo();
	virtual void Redo();


};

#endif