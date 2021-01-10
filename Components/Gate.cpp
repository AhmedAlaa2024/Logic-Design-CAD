#include "Gate.h"
#include <fstream>
#include <iostream>
using namespace std;
//Gate Constructor
//Parameters:
//r_Inputs: no. of gate's input pins
//r_FanOut: Fan out of the gate's output pin
Gate::Gate(int r_Inputs, int r_FanOut)
{

	is_selected = false;
	m_OutputPin = new OutputPin(r_FanOut);
	//Allocate number of input pins (equals r_Inputs)
	m_InputPins = new InputPin[r_Inputs];
	m_Inputs = r_Inputs;	//set no. of inputs of that gate
	//Associate all input pins to this gate
	for (int i = 0; i < m_Inputs; i++)
		m_InputPins[i].setComponent(this);
	/////////Rufaidah
	m_OutputPin->setComponent(this);
	////////////

	comp_type = COMP_TYPES::COMP_GATE; /*This statement to overwrite the type of gate
						   on comp_type protected datatype to be able to use it
						   for identifying the suitable action
						   when the user select the arbitary component. */
}

OutputPin* Gate::getOutputPin() const
{
	return m_OutputPin;
}

InputPin* const Gate::getInputPin() const
{
	return m_InputPins;
}

void Gate::save(ofstream*& fptr)
{
	string name;
	switch (get_comp_type())
	{
	case COMP_TYPES::COMP_SWITCH:
		name = "SWTCH";
		break;
	case COMP_TYPES::COMP_LED:
		name = "LED";
		break;
	case COMP_TYPES::AND_2:
		name = "AND2";
		break;
	case COMP_TYPES::AND_3:
		name = "AND3";
		break;
	case COMP_TYPES::Buff_:
		name = "Buff";
		break;
	case COMP_TYPES::INV_:
		name = "Inv";
		break;
	case COMP_TYPES::NAND_2:
		name = "NAND2";
		break;
	case COMP_TYPES::NOR_2:
		name = "NOR2";
		break;
	case COMP_TYPES::NOR_3:
		name = "NOR3";
		break;
	case COMP_TYPES::OR_2:
		name = "OR2";
		break;
	case COMP_TYPES::XNOR_2:
		name = "XNOR2";
		break;
	case COMP_TYPES::XOR_2:
		name = "XOR2";
		break;
	case COMP_TYPES::XOR_3:
		name = "XOR3";
		break;
	}
	*fptr << name << '\t';
	Component::save(fptr);
}

//void Gate::load(ifstream*&, )
//{
//	else if (CompType == "AND2")
//	comp_type = COMP_TYPES::AND_2;
//	else if (CompType == "AND3")
//	comp_type = COMP_TYPES::AND_3;
//	else if (CompType == "Buff")
//	comp_type = COMP_TYPES::Buff_;
//	else if (CompType == "Inv")
//	comp_type = COMP_TYPES::INV_;
//	else if (CompType == "NAND2")
//	comp_type = COMP_TYPES::NAND_2;
//	else if (CompType == "NOR2")
//	comp_type = COMP_TYPES::NOR_2;
//	else if (CompType == "NOR3")
//	comp_type = COMP_TYPES::NOR_3;
//	else if (CompType == "OR2")
//	comp_type = COMP_TYPES::OR_2;
//	else if (CompType == "XNOR2")
//	comp_type = COMP_TYPES::XNOR_2;
//	else if (CompType == "XOR2")
//	comp_type = COMP_TYPES::XOR_2;
//	else if (CompType == "XOR3")
//	comp_type = COMP_TYPES::XOR_3;
//}

void Gate::set_comp_type(COMP_TYPES ct)
{
	comp_type = ct;
}

bool Gate::is_connected(InputPin& in)
{
	for (int i = 0; i < m_Inputs; ++i)
	{
		if (in.getComponent() == this)
			return true;
	}



	return false;
}


Gate::~Gate()
{
	delete m_OutputPin;
}

COMP_TYPES Gate::get_comp_type() const
{
	return comp_type;
}

//================DOAA==============
int Gate::getNoOfInputpins()
{
	return m_Inputs;
}
