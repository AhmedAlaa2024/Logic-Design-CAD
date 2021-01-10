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
	

	//Clear Status Bar
	pOut->ClearStatusBar();

	//Print Action Message
	pOut->PrintMsg("connect two gates: Choose the destination gate");



	//Wait for User Input
	pIn->GetPointClicked(Cx2, Cy2);

	b = pManager->PressOn_WhiteSpace(Cx2, Cy2);
	if (b == true)
		return;
	

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
	//SrcComp->set_is_selected(true);
	//pManager->ExecuteAction(SELECT);
	/*
	COMP_TYPES comptype1;
	Component* SrcComp = NULL;
	int target1 = pManager->which_component(comptype1, SrcComp);
	*/
	OutputPin* out = SrcComp->getOutputPin();


	//=======================//

	GraphicsInfo GInfo; //Gfx info to be used to construct the connection

	//=======================//
	InputPin* in;
	
	/*
	COMP_TYPES type;
	Component* DistComp = NULL;
	int target2 = pManager->which_component(type);
	*/

	Component* DistComp = pManager->CheckInsideArea(Cx2, Cy2);
	//SrcComp->set_is_selected(false);
	//pManager->ExecuteAction(SELECT);

	//DistComp->set_is_selected(true);

	in = DistComp->getInputPin(); //array of inout pins

	//COMP_TYPES type = DistComp->get_comp_type();

	//DistComp->getm_GfxInfo(a1, b1, a2, b2);

	bool g = pManager->Check_gates_to_connect(SrcComp, DistComp);
	if (g == false)
		return;

	InputPin* selected_pin;
	//bool i = pManager->Check_pins_to_connect(DistComp, in, GInfo,selected_pin);





	//=======================================================================

	//bool ApplicationManager::Check_pins_to_connect(Component * distComp, InputPin * inPin, GraphicsInfo & GInfo, InputPin * &selected_pin)
	//{
		int no_input_pins = DistComp->getNoOfInputpins();
		int j;
		for (j = 0; j < no_input_pins; j++)
		{
			bool isConnected = in[j].get_is_connected();
			if (isConnected == false)
			{
				selected_pin = &in[j];
				in[j].set_is_connected(true);
				
				COMP_TYPES type = DistComp->get_comp_type();
				//int a1, b1, a2, b2;
				DistComp->getm_GfxInfo(a1, b1, a2, b2);

				switch (type)
				{
				case COMP_TYPES::COMP_LED:
				{
					GInfo.x2 = a1 + 23;
					GInfo.y2 = (b1 + (b2 - b1) / 2) + 26;
					break;
				}
				case COMP_TYPES::AND_2:
					if (j == 0)
					{
						GInfo.x2 = a1;
						GInfo.y2 = b1 + 15 + 1;

					}
					else if (j == 1)
					{
						GInfo.x2 = a1;
						GInfo.y2 = b2 - 14 - 2;
					}
					break;
				case COMP_TYPES::AND_3:
					if (j == 0)
					{
						GInfo.x2 = a1;
						GInfo.y2 = b1 + 16;

					}
					else if (j == 1)
					{
						GInfo.x2 = a1;
						GInfo.y2 = b1 + (b2 - b1) / 2;

					}
					else if (j == 2)
					{
						GInfo.x2 = a1;
						GInfo.y2 = b2 - 16;

					}
					break;
				case COMP_TYPES::INV_:
					GInfo.x2 = a1;
					GInfo.y2 = b1 + (b2 - b1) / 2;
					break;
				case COMP_TYPES::NAND_2:
					if (j == 0)
					{
						GInfo.x2 = a1;
						GInfo.y2 = b1 + 15;
					}
					else if (j == 1)
					{
						GInfo.x2 = a1;
						GInfo.y2 = b2 - 14 + 3;
					}
					break;
				case COMP_TYPES::NOR_2:
					if (j == 0)
					{
						GInfo.x2 = a1;
						GInfo.y2 = b1 + 15 + 7;
					}
					else if (j == 1)
					{
						GInfo.x2 = a1;
						GInfo.y2 = b2 - 14 - 4;
					}
					break;
				case COMP_TYPES::NOR_3:
					if (j == 0)
					{
						GInfo.x2 = a1 + 11;
						GInfo.y2 = b1 + 16 + 1;

					}
					else if (j == 1)
					{
						GInfo.x2 = a1 + 11;
						GInfo.y2 = b1 + (b2 - b1) / 2 + 1;
					}
					else if (j == 2)
					{
						GInfo.x2 = a1 + 11;
						GInfo.y2 = b2 - 16 + 1;
					}
					break;
				case COMP_TYPES::Buff_:
					GInfo.x2 = a1;
					GInfo.y2 = b1 + (b2 - b1) / 2;
					break;
				case COMP_TYPES::OR_2:
					if (j == 0)
					{
						GInfo.x2 = a1 + 8;
						GInfo.y2 = b1 + 15 - 7;
					}
					else if (j == 1)
					{
						GInfo.x2 = a1 + 8;
						GInfo.y2 = b2 - 14 + 3;
					}
					break;
				case COMP_TYPES::XNOR_2:
					if (j == 0)
					{
						GInfo.x2 = a1;
						GInfo.y2 = b1 + 15 + 5;
					}
					else if (j == 1)
					{
						GInfo.x2 = a1;
						GInfo.y2 = b2 - 14 - 5;
					}
					break;
				case COMP_TYPES::XOR_2:
					if (j == 0)
					{
						GInfo.x2 = a1;
						GInfo.y2 = b1 + 15;
					}
					else if (j == 1)
					{
						GInfo.x2 = a1;
						GInfo.y2 = b2 - 14;
					}
					break;
				case COMP_TYPES::XOR_3:
					if (j == 0)
					{
						GInfo.x2 = a1;
						GInfo.y2 = b1 + 16;
					}
					else if (j == 1)
					{
						GInfo.x2 = a1;
						GInfo.y2 = b1 + (b2 - b1) / 2;
					}
					else if (j == 2)
					{
						GInfo.x2 = a1;
						GInfo.y2 = b2 - 16;
					}
					break;
				default:
					break;
				}
				/// <summary>
				/// ///////////Rufaiah
				/// </summary>
				InputPinNum = j + 1;
				break;

			}

			if (j == no_input_pins - 1 && isConnected == true)
			{
				pOut->PrintMsg("Error: All input pins of this component are already connected");
				return;
			}

		}

			//======================================================



//	if (i == false)
		//return;
	

	SrcComp->getm_GfxInfo(x1, y1, x2, y2);
	//pManager->getGInfoOfComp(x1, y1, x2, y2, i);

	GInfo.x1 = x2;
	GInfo.y1 = y1 + (y2 - y1) / 2;


	

	Connection* pA = new Connection(GInfo, out, selected_pin);
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

///////////////////Rufaidah
int Connect::getInputPinNum()
{
	return InputPinNum;
}
////////////////////////