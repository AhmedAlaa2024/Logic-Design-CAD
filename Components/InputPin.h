#ifndef _INPUTPIN_H
#define _INPUTPIN_H

#include "Pin.h"
class Component; //Forward class declaration

class InputPin: public Pin	//inherited from class Pin
{
	//===========DOAA=========
	bool is_connected;
	//===========DOAA=========

	Component* pComp; //Component at which this pin is associated
public:
	InputPin();
	void setComponent(Component* pCmp);	//sets the component of this input pin
	Component* getComponent() const;	//returns the component of this input pin

	//============DOAA===========
	bool get_is_connected();
	void set_is_connected(bool);
};

#endif