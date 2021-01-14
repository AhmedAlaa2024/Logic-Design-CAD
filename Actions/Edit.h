#ifndef EDIT_H
#define EDIT_H
	// ============================== Ahmed Alaa edited here ==============================

#include "Action.h"
#include "..\\ApplicationManager.h"
#include "..\\Components\Component.h"

class Edit : public Action
{
private:
	LabelOfComp* label;
	GraphicsInfo r_GfxInfo;
public:
	Edit(ApplicationManager*, LabelOfComp*);
	void SetLabel();
	string GetLabel();

	void ReadActionParameters(); // I don't need it as there is no parameters for Label action
	void Execute();
	void Undo();
	void Redo();
};

#endif
	// ==================================== Ahmed Alaa ====================================