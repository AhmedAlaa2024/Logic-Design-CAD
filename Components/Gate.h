#ifndef _GATE_H
#define _GATE_H

/*
  Class Gate
  -----------
  - Base class for all types of gates
  - Each gate has n inputs pins and one output pin
*/


#include "InputPin.h"
#include "OutputPin.h"
#include "Component.h"

class Gate :public Component
{
protected:
	InputPin* m_InputPins;	//Array of input pins of the Gate
	OutputPin* m_OutputPin;	//The Gate output pin
	int m_Inputs;		//No. of input pins of that Gate.
public:
	Gate(int r_Inputs, int r_FanOut);

	COMP_TYPES get_comp_type() const;
	
	OutputPin* getOutputPin() const;
	
	virtual void save(ofstream*&);
	virtual void set_comp_type(COMP_TYPES);
	virtual InputPin* const getInputPin() const;
	~Gate();
	

	//==============DOAA=========
	virtual int getNoOfInputpins();

};

#endif
