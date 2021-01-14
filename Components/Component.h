#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "InputPin.h"
#include "OutputPin.h"
#include "..\Defs.h"
#include "..\GUI\Output.h"
#include "LabelOfComp.h"

//Base class for classes Gate, Switch, and LED.
class Component
{
private:
	static int LastID;
	LabelOfComp* Label;
	int m_Id;
protected:
	GraphicsInfo m_GfxInfo;	//The parameters required to draw a component
	int last_taken_input_pin_place;
	bool is_selected;
	COMP_TYPES comp_type;
public:
	Component(const GraphicsInfo &r_GfxInfo);
	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut) = 0;	//for each component to Draw itself

	int get_place();

	// ============================== Ahmed Alaa edited here ==============================
	virtual void set_Label(LabelOfComp*); // To set the Label for the component
	virtual LabelOfComp* get_Label(); // To get the Label from the component
	// ==================================== Ahmed Alaa ====================================

	virtual int get_id() const;
	virtual void set_id(int id);
	
	virtual int GetOutPinStatus()=0;	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n)=0;	//returns status of Inputpin # n if SWITCH, return -1
	virtual OutputPin* getOutputPin() const = 0;
	virtual InputPin* const getInputPin() const = 0;
	virtual void setInputPinStatus(int n, STATUS s)=0;	//set status of Inputpin # n, to be used by connection class.
	virtual const GraphicsInfo getGraphicsInfo();
	virtual bool get_is_selected();
	virtual void set_is_selected(bool);
	virtual InputPin* GetInpuPin(int i) const;

	virtual void save(ofstream*&);
	virtual void load(ifstream*&);

	
	virtual COMP_TYPES get_comp_type() const;

	
	
	Component();	

	/// Rufaida

	//Destructor must be virtual
	virtual ~Component();


	//=================DOAA MAGDY================
	int getLastID();

	
	virtual int getNoOfInputpins() = 0;

	void getm_GfxInfo(int &x1,int &y1, int &x2,int &y2);
	Component* CreateNewComp(string CompType);
};

#endif
