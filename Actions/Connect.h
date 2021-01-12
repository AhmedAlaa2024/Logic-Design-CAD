#ifndef CONNTEC_H
#define CONNTEC_H

#include "../Components/Component.h"

#include "Action.h"

class Connect : public Action
{
	////////////Rufaidah
	int InputPinNum;
	///////////////////////////////
	bool isLoaded;

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
	//int getInputPinNum();
	void setDisPinGInfo(COMP_TYPES, int, const GraphicsInfo&, GraphicsInfo&);
	void setSrcPinGInfo(const GraphicsInfo& gate, GraphicsInfo& GInfo);
};

#endif