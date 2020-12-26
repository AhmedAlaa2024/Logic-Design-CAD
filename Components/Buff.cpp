#include "Buff.h"

Buff::Buff(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(1, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void Buff::Operate()
{

	m_OutputPin->setStatus(m_InputPins[0].getStatus());
	
}


// Function Draw
// Draws 2-input AND gate
void Buff::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawBuff(m_GfxInfo);
}

//returns status of outputpin
int Buff::GetOutPinStatus()	
{
	return m_OutputPin->getStatus();
}


//returns status of Inputpin #n
int Buff::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void Buff::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}
