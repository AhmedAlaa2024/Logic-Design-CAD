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
	
	void ReadActionParameters(); // To get the clicked point's coordinates
	void Execute(); // No need but I write it to avoid making the select as abstract class.
	void Undo(); // No need but I write it to avoid making the select as abstract class.
	void Redo();// No need but I write it to avoid making the select as abstract class.
	~Select();
};

#endif