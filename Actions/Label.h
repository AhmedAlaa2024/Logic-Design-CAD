#ifndef LABEL_H
#define LABEL_H

#include "Action.h"
// ============================== Ahmed Alaa edited here ==============================
#include "..\\ApplicationManager.h"
#include "..\\Components\Component.h"
// ==================================== Ahmed Alaa ====================================

#include <iostream>

using namespace std;

class Label : public Action
{
	// ============================== Ahmed Alaa edited here ==============================
private:
	Component* component;
public:
	Label(ApplicationManager*, Component*);
	string SetLabel();
	string GetLabel();
	void DisplayLabel();

	void ReadActionParameters();
	void Execute();
	void Undo();
	void Redo();
	// ==================================== Ahmed Alaa ====================================
};

#endif