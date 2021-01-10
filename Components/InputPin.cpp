#include "InputPin.h"

#include "Component.h"

InputPin::InputPin()
{
	pComp = NULL;
	is_connected = false;
}

void InputPin::setComponent(Component *pCmp)
{
	this->pComp = pCmp;
	set_m_index(pComp->get_place());
	is_connected = false;
}

Component* InputPin::getComponent() const
{
	return pComp;
}

void InputPin::set_m_index(int i)
{
	m_index = i;
}

int InputPin::get_m_index() const
{
	return m_index;
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