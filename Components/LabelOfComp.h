#ifndef _LABELOFCOMP_H
#define _LABELOFCOMP_H


	// ============================== Ahmed Alaa edited here ==============================
#include "Component.h"

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
#endif // !_LABELOFCOMP_H
	// ==================================== Ahmed Alaa ====================================