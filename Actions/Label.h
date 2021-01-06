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

	void ReadActionParameters(); // I don't need it as there is no parameters for Label action
	void Execute();
	void Undo();
	void Redo();
	// ==================================== Ahmed Alaa ====================================
};

#endif