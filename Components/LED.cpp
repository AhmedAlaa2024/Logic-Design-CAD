#include "LED.h"

LED::LED(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(1, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;

	is_high = LOW;
	is_reached = false;
	comp_type = COMP_TYPES::COMP_LED; /*This statement to overwrite the type of gate
						   on comp_type protected datatype to be able to use it
						   for identifying the suitable action
						   when the user select the arbitary component. */
}


void LED::Operate()
{
	is_high = m_InputPins[0].getStatus();
	is_reached = true;
}


// Function Draw
// Draws 2-input AND gate
void LED::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawLED(m_GfxInfo, is_high);
}

//returns status of outputpin
int LED::GetOutPinStatus()
{
	return -1;
}


//returns status of Inputpin #n
int LED::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void LED::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

void LED::set_is_reached(bool v)
{
	is_reached = v;
}

COMP_TYPES LED::get_comp_type() const
{
	return comp_type;
}

bool LED::get_is_reached() const
{
	return is_reached;
}
