#ifndef SELECT_H
#define SELECT_H

#include "Action.h"
#include "..\\Components\\Gate.h"
#include "..\\GUI\Input.h"
#include "..\\ApplicationManager.h"

class Select : public Action
{
public:
	Select();
	Component* const* what_object(COMP_TYPES&); // return 1 -> Gate, 2 -> SWITCH, 3 -> LED, 4 -> WIRE
};

#endif