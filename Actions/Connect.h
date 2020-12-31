#ifndef CONNTEC_H
#define CONNTEC_H

#include "../Components/Component.h"

#include "Action.h"

class Connect : public Action
{
	int noOfComp;
	Component** cmp;
	int id;
	int Cx1, Cy1, Cx2, Cy2;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
public:
	Connect(ApplicationManager* pApp, Component** c, int n);
	virtual ~Connect(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute() ;

	//To undo this action (code depends on action type)
	virtual void Undo() ;

	//To redo this action (code depends on action type)
	virtual void Redo();

};

#endif