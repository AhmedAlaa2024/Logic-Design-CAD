#include "Connection.h"

Connection::Connection(const GraphicsInfo &r_GfxInfo, OutputPin *pSrcPin,InputPin *pDstPin):Component(r_GfxInfo)
	
{

	is_selected = false;
	SrcPin = pSrcPin;
	DstPin = pDstPin;
	is_on = LOW;
	comp_type = COMP_TYPES::COMP_CONN; /*This statement to overwrite the type of gate
						   on comp_type protected datatype to be able to use it
						   for identifying the suitable action
						   when the user select the arbitary component. */
}
void Connection::setSourcePin(OutputPin *pSrcPin)
{	SrcPin = pSrcPin;	}

OutputPin* Connection::getSourcePin() const
{	return SrcPin;	}


void Connection::setDestPin(InputPin *pDstPin)
{	DstPin = pDstPin;	}

InputPin* Connection::getDestPin() const
{	return DstPin;	}


void Connection::Operate()
{
	//Status of connection destination pin = status of connection source pin
	DstPin->setStatus(SrcPin->getStatus());
	is_on = SrcPin->getStatus();
}

void Connection::Draw(Output* pOut)
{
	pOut->DrawConnection(m_GfxInfo, is_selected,is_on);
}

int Connection::GetOutPinStatus()	//returns status of outputpin if LED, return -1
{
	return DstPin->getStatus();
}


int Connection::GetInputPinStatus(int n)	//returns status of Inputpin # n if SWITCH, return -1
{
	return SrcPin->getStatus();	//n is ignored as connection has only one input pin (src pin)	
}

void Connection::setInputPinStatus(int n, STATUS s)
{
	SrcPin->setStatus(s);
}

COMP_TYPES Connection::get_comp_type() const
{
	return comp_type;
}

void Connection::save(ofstream* fptr)
{

}
