#ifndef SELECT_H
#define SELECT_H

#include "Action.h"
#include "..\\Components\\Gate.h"
#include "..\\GUI\Input.h"
#include "..\\ApplicationManager.h"

class Select : public Action
{
private:
	bool select = 0;
public:
	COMP_TYPES what_object(int, int); // return 0 -> Gate, 1 -> SWITCH, 2 -> LED, 3 -> WIRE
};

#endif