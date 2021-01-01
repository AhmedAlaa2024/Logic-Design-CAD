#ifndef SELECT_H
#define SELECT_H

#include "Action.h"
#include "..\\Components\\Gate.h"
#include "..\\GUI\Input.h"
#include "..\\ApplicationManager.h"

class Select : public Action
{
private:
	int x, y;
public:
	Select(ApplicationManager* pApp);
	int which_component(COMP_TYPES&); // return 1 -> Gate, 2 -> SWITCH, 3 -> LED, 4 -> WIRE
	void DeselectExcept(int = -1); // If the user clicked on blank space, all components should be deselected.
	void ReadActionParameters(); // No need but I write it to avoid making the select as abstract class.
	void Execute(); // No need but I write it to avoid making the select as abstract class.
	void Undo(); // No need but I write it to avoid making the select as abstract class.
	void Redo();// No need but I write it to avoid making the select as abstract class.
};

#endif