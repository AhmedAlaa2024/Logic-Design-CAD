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


void Connect::ReadActionParameters(int &a, int &b, bool& checkIfSourceIsLED)
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	noOfComp = pManager->getCompCount();

	//Print Action Message
	pOut->PrintMsg("connect two gates: Choose the source gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx1, Cy1);

	checkIfSourceIsLED = false;
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

	//Clear Status Bar
	pOut->ClearStatusBar();

	//Print Action Message
	pOut->PrintMsg("connect two gates: Choose the destination gate");



	//Wait for User Input
	pIn->GetPointClicked(Cx2, Cy2);

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


	//Clear Status Bar
	pOut->ClearStatusBar();


}



void Connect::Execute()
{
	//Get the two Gates wanted to be connected
	Output* pOut = pManager->GetOutput();

	int a, b;
	bool IfLED;
	ReadActionParameters(a, b, IfLED);

	if (a == 0 || b == 0 || IfLED == true)
	{
		return;
	}

	OutputPin* out;
	noOfComp = pManager->getCompCount();

	int i;
	for (i = 0; i < noOfComp; i++)
	{
		bool d = pManager->CheckInsideArea(i, Cx1, Cy1);
		if (d)
		{
			COMP_TYPES type = pManager->CompType(i);
			if (type == COMP_TYPES::COMP_LED)
			{
				pOut->PrintMsg("Error: the led has no output pin");
				return;

			}
			out = pManager->getOutputPinOfComp(i);
			break;
		}

	}
	

	InputPin* in;

	//=======================//
	GraphicsInfo GInfo; //Gfx info to be used to construct the connection

	//=======================//


	int k;
	for (k = 0; k < noOfComp; k++)
	{
		bool d = pManager->CheckInsideArea(k, Cx2, Cy2);
		//bool d = cmp[k]->InsideArea(Cx2, Cy2);
		if (d)
		{
			bool c = pManager->CheckWheatherSrcIsTheDist(i, k);
			if (c == true)
			{
				pOut->PrintMsg("Error: You have already chosen this gate as a source gate. You can not connect a gate to itself");
				return;
			}
			COMP_TYPES type = pManager->CompType(k);
			if (type == COMP_TYPES::COMP_SWITCH)
			{

				pOut->PrintMsg("Error: the switch has no input pins");
				return;

			}

			//we now have the component //ready to check the input pins
			in = pManager->getInputPinOfComp(k);
			


			int const no_input_pins = pManager->getNoOfInputpinsOfComp(k);
			


			for (int j = 0; j < no_input_pins; j++)
			{
				bool isConnected = in[j].get_is_connected();
				if (isConnected == false)
				{
					in[j].set_is_connected(true);
					switch (type)
					{
						/*
					case COMP_TYPES::COMP_GENERAL:
						break;
					case COMP_TYPES::COMP_GATE:
						break;
					case COMP_TYPES::COMP_SWITCH:
						break;
						*/
					case COMP_TYPES::COMP_LED:
					{
						pManager->getGInfoOfComp(a1, b1, a2, b2, k);
						GInfo.x2 = a1 + 23;
						GInfo.y2 = (b1 + (b2 - b1) / 2) + 26;
						break;
					}
					//case COMP_TYPES::COMP_CONN:
						//break;
					case COMP_TYPES::AND_2:
						if (j == 0)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							GInfo.x2 = a1;
							GInfo.y2 = b1 + 15 + 1;

						}
						else if (j == 1)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							GInfo.x2 = a1;
							GInfo.y2 = b2 - 14 - 2;
						}
						break;
					case COMP_TYPES::AND_3:
						if (j == 0)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							GInfo.x2 = a1;
							GInfo.y2 = b1 + 16;

						}
						else if (j == 1)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							GInfo.x2 = a1;
							GInfo.y2 = b1 + (b2 - b1) / 2;

						}
						else if (j == 2)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							GInfo.x2 = a1;
							GInfo.y2 = b2 - 16;

						}
						break;
					case COMP_TYPES::INV_:
						pManager->getGInfoOfComp(a1, b1, a2, b2, k);
						GInfo.x2 = a1;
						GInfo.y2 = b1 + (b2 - b1) / 2;
						break;
					case COMP_TYPES::NAND_2:
						if (j == 0)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							GInfo.x2 = a1;
							GInfo.y2 = b1 + 15;

						}
						else if (j == 1)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							GInfo.x2 = a1;
							GInfo.y2 = b2 - 14 + 3;
						}
						break;
					case COMP_TYPES::NOR_2:
						if (j == 0)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							GInfo.x2 = a1 ;
							GInfo.y2 = b1 + 15 + 7;

						}
						else if (j == 1)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							GInfo.x2 = a1;
							GInfo.y2 = b2 - 14 - 4;
						}
						break;
					case COMP_TYPES::NOR_3:
						if (j == 0)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							GInfo.x2 = a1 + 11;
							GInfo.y2 = b1 + 16 + 1;

						}
						else if (j == 1)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							GInfo.x2 = a1 + 11;
							GInfo.y2 = b1 + (b2 - b1) / 2 + 1;

						}
						else if (j == 2)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							GInfo.x2 = a1 + 11;
							GInfo.y2 = b2 - 16 + 1;

						}
						break;
					case COMP_TYPES::Buff_:
						pManager->getGInfoOfComp(a1, b1, a2, b2, k);
						GInfo.x2 = a1;
						GInfo.y2 = b1 + (b2 - b1) / 2;
						break;
					case COMP_TYPES::OR_2:
						if (j == 0)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							GInfo.x2 = a1 + 8;
							GInfo.y2 = b1 + 15 -7;

						}
						else if (j == 1)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							GInfo.x2 = a1 + 8;
							GInfo.y2 = b2 - 14 + 3 ;
						}
						break;
					case COMP_TYPES::XNOR_2:
						if (j == 0)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							GInfo.x2 = a1;
							GInfo.y2 = b1 + 15 + 5;

						}
						else if (j == 1)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							GInfo.x2 = a1;
							GInfo.y2 = b2 - 14 - 5;
						}
						break;
					case COMP_TYPES::XOR_2:
						if (j == 0)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							GInfo.x2 = a1;
							GInfo.y2 = b1 + 15;

						}
						else if (j == 1)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							GInfo.x2 = a1;
							GInfo.y2 = b2 - 14;
						}
						break;
					case COMP_TYPES::XOR_3:
						if (j == 0)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							GInfo.x2 = a1;
							GInfo.y2 = b1 + 16;

						}
						else if (j == 1)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							GInfo.x2 = a1;
							GInfo.y2 = b1 + (b2 - b1) / 2;

						}
						else if (j == 2)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							GInfo.x2 = a1;
							GInfo.y2 = b2 - 16;

						}
						break;
					default:
						break;
					}


					/*
					if (no_input_pins == 2)
					{
						if (j == 0)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							//cmp[k]->getm_GfxInfo(a1, b1, a2, b2);
							GInfo.x2 = a1;
							GInfo.y2 = b1+15;

						}
						else if (j == 1)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							//cmp[k]->getm_GfxInfo(a1, b1, a2, b2);
							GInfo.x2 = a1;
							GInfo.y2 = b2-14;
						}
					}
					else if (no_input_pins == 3)
					{
						if (j == 0)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							//cmp[k]->getm_GfxInfo(a1, b1, a2, b2);
							GInfo.x2 = a1;
							GInfo.y2 = b1 + 16;

						}
						else if (j == 1)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							//cmp[k]->getm_GfxInfo(a1, b1, a2, b2);
							GInfo.x2 = a1;
							GInfo.y2 = b1 + (b2 - b1) / 2;

						}
						else if (j == 2)
						{
							pManager->getGInfoOfComp(a1, b1, a2, b2, k);
							//cmp[k]->getm_GfxInfo(a1, b1, a2, b2);
							GInfo.x2 = a1;
							GInfo.y2 = b2 - 16;

						}


					}
					*/
					//===================================================================================//
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
					input = &in[j];
					in[j].set_is_connected(true);

					
					//============================================================================//
					LED* led = dynamic_cast<LED*>(cmp[k]);
					Buff* buffer = dynamic_cast<Buff*>(cmp[k]);
					INV* inverter = dynamic_cast<INV*>(cmp[k]);
					if (led != NULL || buffer != NULL || inverter != NULL)
					{
						cmp[k]->getm_GfxInfo(a1, b1, a2, b2);
						GInfo.x2 = a1;
						GInfo.y2 = b1 + (b2 - b1) / 2;
					}
					else if (no_input_pins == 2)
					{
						if (j == 0)
						{
							cmp[k]->getm_GfxInfo(a1, b1, a2, b2);
							GInfo.x2 = a1;
							GInfo.y2 = b1+15;

						}
						else if (j == 1)
						{
							cmp[k]->getm_GfxInfo(a1, b1, a2, b2);
							GInfo.x2 = a1;
							GInfo.y2 = b2-14;
						}
					}
					else if (no_input_pins == 3)
					{
						if (j == 0)
						{
							cmp[k]->getm_GfxInfo(a1, b1, a2, b2);
							GInfo.x2 = a1;
							GInfo.y2 = b1 + 16;

						}
						else if (j == 1)
						{
							cmp[k]->getm_GfxInfo(a1, b1, a2, b2);
							GInfo.x2 = a1;
							GInfo.y2 = b1 + (b2 - b1) / 2;

						}
						else if (j == 2)
						{
							cmp[k]->getm_GfxInfo(a1, b1, a2, b2);
							GInfo.x2 = a1;
							GInfo.y2 = b2 - 16;

						}


					}
					
					//===================================================================================//
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
	*/

	
	

	pManager->getGInfoOfComp(x1, y1, x2, y2, i);

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