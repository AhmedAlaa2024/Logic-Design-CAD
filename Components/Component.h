#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "..\Defs.h"
#include "..\GUI\Output.h"

//Base class for classes Gate, Switch, and LED.
class Component
{
private:
	string m_Label;
	int m_Id;
protected:
	GraphicsInfo m_GfxInfo;	//The parameters required to draw a component
	bool is_selected;
	COMP_TYPES comp_type;
public:
	Component(const GraphicsInfo &r_GfxInfo);
	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut) = 0;	//for each component to Draw itself

	virtual int get_id() const;
	virtual void set_id(int id);
	
	virtual int GetOutPinStatus()=0;	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n)=0;	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s)=0;	//set status of Inputpin # n, to be used by connection class.
	virtual const GraphicsInfo getGraphicsInfo();

	virtual bool get_is_selected();
	virtual void set_is_selected(bool);

	virtual COMP_TYPES get_comp_type();
	
	Component();	
	
	//Destructor must be virtual
	virtual ~Component();
};

#endif
