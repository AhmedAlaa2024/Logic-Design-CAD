#include "InputPin.h"

InputPin::InputPin()
{}

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