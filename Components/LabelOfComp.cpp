#include "LabelOfComp.h"

	// ============================== Ahmed Alaa edited here ==============================

LabelOfComp::LabelOfComp(const GraphicsInfo& r_GfxInfo): pOut(nullptr), r_GfxInfo(r_GfxInfo), label("")
{
}

void LabelOfComp::Draw(Output* pOut)
{
	this->pOut = pOut;
	pOut->DrawTextbox(label, r_GfxInfo);
}

void LabelOfComp::set_label(string label)
{
	this->label = label;
}

string LabelOfComp::get_label()
{
	return label;
}

LabelOfComp::~LabelOfComp()
{
	pOut->ClearLabelArea(r_GfxInfo, label.size());
}

	// ==================================== Ahmed Alaa ====================================