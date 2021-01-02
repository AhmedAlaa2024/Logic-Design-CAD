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


void Connect::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("connect two gates: Choose the source gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx1, Cy1);

	//Clear Status Bar
	pOut->ClearStatusBar();

	//Print Action Message
	pOut->PrintMsg("connect two gates: Choose the destination gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx2, Cy2);


	//Clear Status Bar
	pOut->ClearStatusBar();


}


void Connect::Execute()
{
	//Get the two Gates wanted to be connected
	Output* pOut = pManager->GetOutput();

	cmp = pManager->getComponents(noOfComp);

	ReadActionParameters();

	OutputPin* out;

	int i;
	for (i = 0; i < noOfComp; i++)
	{
		bool d = cmp[i]->InsideArea(Cx1, Cy1);
		//LED* L = dynamic_cast<LED*>(cmp[i]);

		if (d)
		{
			LED* L = dynamic_cast<LED*>(cmp[i]);
			if (L != NULL)
			{
				pOut->PrintMsg("the led has no output pin, please chose another component");
				return;

			}
			out = cmp[i]->getOutputPin();
			break;
		}
	}

	InputPin* in;
	InputPin input;

	int k;
	for (k = 0; k < noOfComp; k++)
	{
		bool d = cmp[k]->InsideArea(Cx2, Cy2);
		if (d)
		{
			SWITCH* sw = dynamic_cast<SWITCH*>(cmp[k]);
			if (sw != NULL)
			{
				
				pOut->PrintMsg("the switch has no input pins, please chose another component");
				return;

			}

			//we now have the component //ready to check the input pins
			in = cmp[k]->getInputPin();
			int const no_input_pins = cmp[k]->getNoOfInputpins();


			for (int j = 0; j < no_input_pins; j++)
			{
				bool isConnected = in[j].get_is_connected();
				if (isConnected == false)
				{
					input = in[j];
					in->set_is_connected(true);
					break;
				}
				if (j == no_input_pins - 1 && isConnected == true)
				{
					Output* pOut = pManager->GetOutput();
					pOut->PrintMsg("Error: All input pins of this component are already connected");
					return;

				}
			}

			break;
		}
	}
	/*
		for (int i = 0; i < noOfComp; i++)
		{
			delete in[i];
		}
		delete[]in;
		*/

		//if()


	GraphicsInfo GInfo; //Gfx info to be used to construct the connection
	//src component
	cmp[i]->getm_GfxInfo(x1, y1, x2, y2);



	
	//AND2* and = dynamic_cast<AND2*>(cmp[k]);


	/*
	const char* type = typeid(*cmp[k]).name();

	if(strcmp(type, "Buff") == true || strcmp(type, "INV2") == true)
	{

	}

	else if (strcmp(type, "AND2") == true || strcmp(type, "OR2") == true || strcmp(type, "NAND2") == true || strcmp(type, "NOR2") == true || strcmp(type, "XOR2") == true || strcmp(type, "XNOR2") == true)
	{

	}
	else if (strcmp(type, "AND3") == true || strcmp(type, "NOR3") == true || strcmp(type, "XOR2") == true)
	{

	}

	*/


	cmp[k]->getm_GfxInfo(a1, b1, a2, b2);

	GInfo.x1 = x2;
	GInfo.y1 = y1 + (y2 - y1) / 2;


	GInfo.x2 = a1;
	GInfo.y2 =b1 ;

	
	Connection* pA = new Connection(GInfo, out, &input);
	pA->Draw(pOut);
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