#ifndef _ADD_LED_H
#define _ADD_LED_H

#include "Action.h"
#include "..\Components\LED.h"

class AddLED :
    public Action
{
private:
	//Parameters for rectangular area to be occupied by the led
	int Cx, Cy;	//Center point of the led
public:
	AddLED(ApplicationManager* pApp);
	virtual ~AddLED(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

};

#endif