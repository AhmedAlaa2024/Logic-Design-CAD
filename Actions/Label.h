#ifndef LABEL_H
#define LABEL_H

#include "Action.h"
// ============================== Ahmed Alaa edited here ==============================
#include "..\\ApplicationManager.h"
#include "..\\Components\\Component.h"
#include "..\\Components\\LabelOfComp.h"
// ==================================== Ahmed Alaa ====================================

#include <iostream>

using namespace std;

class Label : public Action
{
	// ============================== Ahmed Alaa edited here ==============================
private:
	LabelOfComp*  label;
	GraphicsInfo r_GfxInfo;
public:
	Label(ApplicationManager*, LabelOfComp*);
	// Label(ApplicationManager* pApp, Component* comp, int f);
	void SetLabel();
	string GetLabel();

	void ReadActionParameters(); // I don't need it as there is no parameters for Label action
	void Execute();
	void Undo();
	void Redo();
	// ==================================== Ahmed Alaa ====================================
};

#endif