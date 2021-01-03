#ifndef DELETE_H
#define DELETE_H

#include "Action.h"
// ============================== Ahmed Alaa edited here ==============================
#include "..\\ApplicationManager.h"
#include "..\\Components\Component.h"
// ==================================== Ahmed Alaa ====================================

class Delete : public Action
{
	// ============================== Ahmed Alaa edited here ==============================
private:
	Component* component;
public:
	Delete(ApplicationManager* pApp, Component*);

	void ReadActionParameters();
	void Execute();
	void Undo();
	void Redo();
	// ==================================== Ahmed Alaa ====================================
};

#endif