#pragma once

	// ============================== Ahmed Alaa edited here ==============================

#include "..//ApplicationManager.h"
class LabelOfComp
{
private:
	Output* pOut;
	const GraphicsInfo& r_GfxInfo;
	string label;
public:
    LabelOfComp(const GraphicsInfo&);
	virtual void Draw(Output* pOut);	//Draws Label textbox
	void set_label(string label); // To set the label
	string get_label(); // To get the label
	~LabelOfComp();
};

	// ==================================== Ahmed Alaa ====================================