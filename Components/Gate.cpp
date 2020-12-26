#include "Gate.h"

//Gate Constructor
//Parameters:
//r_Inputs: no. of gate's input pins
//r_FanOut: Fan out of the gate's output pin
Gate::Gate(int r_Inputs, int r_FanOut):m_OutputPin(r_FanOut)
{
	//Allocate number of input pins (equals r_Inputs)
	m_InputPins = new InputPin[r_Inputs];
	m_Inputs = r_Inputs;	//set no. of inputs of that gate
	//Associate all input pins to this gate
	for(int i=0; i<m_Inputs; i++)
		m_InputPins[i].setComponent(this);

	comp_type = COMP_TYPES::COMP_GATE; /*This statement to overwrite the type of gate
						   on comp_type protected datatype to be able to use it
						   for identifying the suitable action
						   when the user select the arbitary component. */
}

COMP_TYPES Gate::get_comp_type()
{
	return comp_type;
}
