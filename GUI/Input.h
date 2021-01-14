#pragma once

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "UI_Info.h"

class Output;
class Input		//The application manager should have a pointer to this class
{
private:
	window *pWind;	//Pointer to the Graphics Window
	int last_x, last_y;
public:
	Input(window*);
	void GetPointClicked(int &, int &);	//Get coordinate where user clicks
	string GetString(Output*, string = "") const ;		//Returns a string entered by the user

	ActionType GetUserAction(); //Reads the user click and maps it to an action
	ActionType AddGate() const;   //Reads the user click and maps it to an action

	void GetLastClicked(int&, int&);
	string GetFileName(Output* pOut, int = 0) const;

	~Input();
};
