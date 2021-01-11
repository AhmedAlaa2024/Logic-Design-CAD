#ifndef _LED_H
#define _LED_H

/*
  Class LED
  -----------
  represent the 2-input AND gate
*/

#include "Gate.h"

class LED :public Gate
{
private:
	STATUS is_high;
	bool is_reached;
public:
	LED(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the AND gate
	virtual void Draw(Output* pOut);	//Draws 2-input gate

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	STATUS get_is_High() const;

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	void set_is_reached( bool v);
	
	virtual COMP_TYPES get_comp_type() const;
	bool get_is_reached()const;
};

#endif