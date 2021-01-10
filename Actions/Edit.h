#ifndef EDIT_H
#define EDIT_H
	// ============================== Ahmed Alaa edited here ==============================

#include "Action.h"
#include "..\\ApplicationManager.h"
#include "..\\Components\Component.h"

class Edit : public Action
{
private:
	Component* component;
public:
	Edit(ApplicationManager*, Component*);
	string SetLabel();
	string GetLabel();
	void DisplayLabel();

	void ReadActionParameters(); // I don't need it as there is no parameters for Label action
	void Execute();
	void Undo();
	void Redo();
};

#endif
	// ==================================== Ahmed Alaa ====================================