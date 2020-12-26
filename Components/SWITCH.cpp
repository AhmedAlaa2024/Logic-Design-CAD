#include "SWITCH.h"

SWITCH::SWITCH(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(0, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void SWITCH::Operate()
{

	//still needs modification
	m_OutputPin->setStatus(is_on);


}


// Function Draw
// Draws 2-input AND gate
void SWITCH::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawSWITCH(m_GfxInfo, is_on);
}

//returns status of outputpin
int SWITCH::GetOutPinStatus()
{
	return m_OutputPin->getStatus();
}


//returns status of Inputpin #n
int SWITCH::GetInputPinStatus(int n)
{
	return -1;
}

//Set status of a switch ot HIGH or LOW
void SWITCH::set_state(STATUS s)
{
	is_on = s;
}
