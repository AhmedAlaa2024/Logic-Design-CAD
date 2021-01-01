#ifndef _EXIT_H
#define _EXIT_H

#include "action.h"


class Exit : public Action
{

public:
	Exit(ApplicationManager* pApp);
	
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void ReadActionParameters();
	virtual void Undo();
	virtual void Redo();

	virtual ~Exit(void);
};

#endif