#ifndef DELETE_H
#define DELETE_H

#include "Action.h"
	// ============================== Ahmed Alaa edited here ==============================
#include "..\\ApplicationManager.h"

class Delete : public Action
{
public:
	Delete(ApplicationManager* pApp);

	void ReadActionParameters();
	void Execute();
	void Undo();
	void Redo();
};
	// ==================================== Ahmed Alaa ====================================
#endif