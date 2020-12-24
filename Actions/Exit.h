#ifndef _EXIT_H
#define _EXIT_H

#include "action.h"


class Exit : public Action
{

public:
	Exit(ApplicationManager* pApp);
	virtual ~Exit(void);


	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void ReadActionParameters();
	virtual void Undo();
	virtual void Redo();


};

#endif