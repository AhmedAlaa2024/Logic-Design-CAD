#include "NOR3.h"

NOR3::NOR3(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(3, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void NOR3::Operate()
{
	//(A + B + C)'
	for (int i = 0; i < 3; ++i)
	{
		if (m_InputPins[i].getStatus() == HIGH)
		{
			m_OutputPin->setStatus(LOW);
			return;
		}

	}
	m_OutputPin->setStatus(HIGH);
}


// Function Draw
// Draws 2-input AND gate
void NOR3::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawNOR3(m_GfxInfo, is_selected);
}

//returns status of outputpin
int NOR3::GetOutPinStatus()	
{
	return m_OutputPin->getStatus();
}


//returns status of Inputpin #n
int NOR3::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void NOR3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}
