#pragma once
#include "component.h"
#include "InputPin.h"
#include "OutputPin.h"

class Connection : public Component
{
	//Component*	SrcCmpnt;	//Connection source component
	//Component*	DstCmpnt;	//Connection Destination component
	//int		DstPin;		//The Input pin to which this connection is linked
	
	OutputPin* SrcPin;	//The Source pin of this connection (an output pin of certain Component)
	InputPin* DstPin;	//The Destination pin of this connection (an input pin of certain Component)

public:
	//Connection(const GraphicsInfo &r_GfxInfo, Component *pS=NULL,Component *pD=NULL, int Pin=0);
	Connection(const GraphicsInfo& r_GfxInfo, OutputPin* pSrcPin, InputPin* pDstPin);

	virtual void Operate();	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut);	//for each component to Draw itself
	STATUS is_on;

	void setSourcePin(OutputPin* pSrcPin);
	void setDestPin(InputPin* pDstPin);
	OutputPin* getSourcePin() const;
	InputPin* getDestPin() const;

	//dummy
	virtual OutputPin* getOutputPin() const { return nullptr; }
	//dummy
	virtual InputPin* const getInputPin() const { return nullptr; }

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.

	virtual COMP_TYPES get_comp_type() const;

	virtual void save(fstream*&);
	virtual void load(ifstream*&);

	//=============DOAA MAGDY===========
	virtual int getNoOfInputpins() { return 0; };



	virtual ~Connection();


};
