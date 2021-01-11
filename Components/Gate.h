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
	
	virtual void save(fstream*&);
	//virtual void load(ifstream*&);
	virtual void set_comp_type(COMP_TYPES);

	virtual bool is_connected(InputPin&) ;
	
	virtual InputPin* const getInputPin() const;
	//////Rufaidah
	virtual InputPin* GetInpuPin(int i) const;
	~Gate();
	

	//==============DOAA=========
	virtual int getNoOfInputpins();

};

#endif
