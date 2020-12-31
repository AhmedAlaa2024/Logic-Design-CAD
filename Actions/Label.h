#ifndef LABEL_H
#define LABEL_H

#include "Action.h"
#include "..\\ApplicationManager.h"
#include "..\\Components\Component.h"

#include <iostream>

using namespace std;

class Label : public Action
{
private:
	string label;
	GraphicsInfo r_GfxInfo;
public:
	Label();
	void SetLabel(string&);
	string GetLabel();
	void DisplayLabel(Component*);
};

#endif