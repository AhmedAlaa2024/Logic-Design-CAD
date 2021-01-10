#include "InputPin.h"

InputPin::InputPin()
{
	pComp = NULL;
	is_connected = false;
}

void InputPin::setComponent(Component *pCmp)
{
	this->pComp = pCmp;

	is_connected = false;
}

Component* InputPin::getComponent() const
{
	return pComp;
}


//==============DOAA==========
bool InputPin::get_is_connected()
{
	return is_connected;
}


void InputPin::set_is_connected(bool test)
{
	is_connected = test;
}

//=============DOAA===========