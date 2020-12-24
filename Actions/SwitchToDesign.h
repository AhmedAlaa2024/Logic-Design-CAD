#ifndef _SwitchToDesign_H
#define _SwitchToDesign_H

#include "action.h"


class SwitchToDesign : public Action
{

public:
	SwitchToDesign(ApplicationManager* pApp);
	virtual ~SwitchToDesign();


	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void ReadActionParameters();
	virtual void Undo();
	virtual void Redo();


};

#endif