	// ============================== Ahmed Alaa edited here ==============================
#ifndef CLEAR_H_
#define CLEAR_H_

#include "Action.h"
#include "..\\ApplicationManager.h"

class Clear :
    public Action
{
public:
	Clear(ApplicationManager* pApp);
	void ReadActionParameters();
	void Execute();
	void Undo();
	void Redo();
};

#endif // !CLEAR_H_
	// ==================================== Ahmed Alaa ====================================