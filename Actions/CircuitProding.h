#ifndef _CircuitProding_H
#define _CircuitProding_H

#include "action.h"
class Connection;

class CircuitProding : public Action
{

public:
	CircuitProding(ApplicationManager* pApp);
	virtual ~CircuitProding();


	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void ReadActionParameters();
	virtual void Undo();
	virtual void Redo();


};

#endif