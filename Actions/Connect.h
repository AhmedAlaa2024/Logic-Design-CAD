#ifndef CONNTEC_H
#define CONNTEC_H

#include "../Components/Component.h"

#include "Action.h"

class Connect : public Action
{
	int noOfComp;
	int id;
	int Cx1, Cy1, Cx2, Cy2;	//2 Center points of the two gates
	int x1, y1, x2, y2;	//Two corners of the rectangluar area of the source gate
	int a1, b1, a2, b2;//Two corners of the rectangluar area of the destination gate


public:
	Connect(ApplicationManager* pApp);
	virtual ~Connect(void);

	//Reads parameters required for action to execute
	void ReadActionParameters(bool& a, bool& b, bool& checkIfSourceIsLED, int num_of_call);
	virtual void ReadActionParameters() {};


	//Execute action (code depends on action type)
	virtual void Execute() ;

	//To undo this action (code depends on action type)
	virtual void Undo() ;

	//To redo this action (code depends on action type)
	virtual void Redo();

	////////////////Rufaidah
	void setDisPinGInfo(COMP_TYPES, int, const GraphicsInfo&, GraphicsInfo&);
	void setSrcPinGInfo(const GraphicsInfo& gate, GraphicsInfo& GInfo);
};

#endif