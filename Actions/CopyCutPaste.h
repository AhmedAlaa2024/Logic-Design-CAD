#pragma once

#include "action.h"
#include "..\Components\AND2.h"
#include "..\Actions/Add.h"
#include "..\Components\Component.h"

enum CopyCutPaste_mode
{
	COPY,
	CUT,
	PASTE
	
};
class CopyCutPaste : public Action
{
private:

	const  int MODE;
	
	int Cx, Cy;	//Center point of the pasted

public:
	// mode = 0 --> copy   mode = 1 --> cut  mode = 2 --> paste
	CopyCutPaste(ApplicationManager* pApp,int mode);
	virtual ~CopyCutPaste(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	void cut();
	void copy();
	void paste();
	

	virtual void Undo();
	virtual void Redo();


};
