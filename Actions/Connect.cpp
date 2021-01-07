#include "Connect.h"
#include "..\ApplicationManager.h"

#include "..\Components\Connection.h"
#include "..\Components\LED.h"
#include "..\Components\SWITCH.h"
#include "..\Components\AND2.h"
#include "..\Components\AND3.h"
#include "..\Components\NOR2.h"
#include "..\Components\NOR3.h"
#include "..\Components\XOR2.h"
#include "..\Components\XOR3.h"
#include "..\Components\OR2.h"
#include "..\Components\NAND2.h"
#include "..\Components\XNOR2.h"
#include "..\Components\Buff.h"
#include "..\Components\INV.h"
#include <typeinfo>
#include <iostream>
using namespace std;

Connect::Connect(ApplicationManager* pApp) :Action(pApp)
{

}


void Connect::ReadActionParameters(bool &a, bool &b, bool& checkIfSourceIsLED)
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//noOfComp = pManager->getCompCount();

	//Print Action Message
	pOut->PrintMsg("connect two gates: Choose the source gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx1, Cy1);

	a = pManager->PressOn_WhiteSpace(Cx1, Cy1);
	if (a == true)
		return;

	checkIfSourceIsLED = pManager->checkIfSourceIsLED(Cx1, Cy1);
	if (checkIfSourceIsLED == true)
		return;
	/*
	for (int i = 0; i < noOfComp; i++)
	{
		bool d = pManager->CheckInsideArea(i, Cx1, Cy1);
		if (d)
		{
			COMP_TYPES type = pManager->CompType(i);
			if (type == COMP_TYPES::COMP_LED)
			{
				pOut->PrintMsg("Error: the led has no output pin");
				checkIfSourceIsLED = true;
				return;

			}
		}
	}
	*/
	
	/*
	int count_check_s = 0;
	for (int i = 0; i < noOfComp; i++)
	{
		bool d = pManager->CheckInsideArea(i, Cx1, Cy1);
		if (d == true)
		{
			count_check_s ++;
		}
	}



	a = count_check_s;
	if (count_check_s == 0)
	{
		pOut->PrintMsg("Error: You can not choose a white space. You have to choose a gate");
		return;
	}
	*/

	//Clear Status Bar
	pOut->ClearStatusBar();

	//Print Action Message
	pOut->PrintMsg("connect two gates: Choose the destination gate");



	//Wait for User Input
	pIn->GetPointClicked(Cx2, Cy2);

	b = pManager->PressOn_WhiteSpace(Cx2, Cy2);
	if (b == true)
		return;
	/*
	int count_check_d = 0;
	for (int i = 0; i < noOfComp; i++)
	{
		bool d = pManager->CheckInsideArea(i, Cx2, Cy2);
		if (d == true)
		{
			count_check_d++;
		}
	}
	b = count_check_d;
	if (count_check_d == 0)
	{
		pOut->PrintMsg("Error: You can not choose a white space. You have to choose a gate");
		return;
	}
	*/

	//Clear Status Bar
	pOut->ClearStatusBar();


}



void Connect::Execute()
{
	//Get the two Gates wanted to be connected
	Output* pOut = pManager->GetOutput();

	bool a, b;
	bool IfLED;
	ReadActionParameters(a, b, IfLED);

	if (a == true || b == true || IfLED == true)
	{
		return;
	}

	Component* SrcComp = pManager->CheckInsideArea(Cx1, Cy1);
	OutputPin* out = SrcComp->getOutputPin();


	//=======================//

	GraphicsInfo GInfo; //Gfx info to be used to construct the connection

	//=======================//
	InputPin* in;
	
	Component* DistComp = pManager->CheckInsideArea(Cx2, Cy2);

	in = DistComp->getInputPin();

	//COMP_TYPES type = DistComp->get_comp_type();

	//DistComp->getm_GfxInfo(a1, b1, a2, b2);

	bool g = pManager->Check_gates_to_connect(SrcComp, DistComp);
	if (g == false)
		return;

	
	bool i = pManager->Check_pins_to_connect(DistComp, in, GInfo);
	if (i == false)
		return;
	

	SrcComp->getm_GfxInfo(x1, y1, x2, y2);
	//pManager->getGInfoOfComp(x1, y1, x2, y2, i);

	GInfo.x1 = x2;
	GInfo.y1 = y1 + (y2 - y1) / 2;


	

	Connection* pA = new Connection(GInfo, out, in);
	out->ConnectTo(pA);

	//pA->Draw(pOut);
	pManager->AddComponent(pA);

}

Connect::~Connect(void)
{

}


void Connect::Undo()
{

}

void Connect::Redo()
{

}