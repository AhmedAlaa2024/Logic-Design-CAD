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


void Connect::ReadActionParameters(bool& a, bool& b, bool& checkIfSourceIsLED, int num_of_call)
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();


	pOut->PrintMsg("connect two gates: Choose the source gate");

	if (num_of_call == 1)
	{
		pIn->GetPointClicked(Cx1, Cy1);

		pManager->ExecuteAction(SELECT);

		Component* p_component = pManager->GetLastSelectedComponent();
		if (!p_component)//check if its Null
		{
			pOut->PrintMsg("You Can't choose a white space.");
			a = true;
			return;
		}

		if (p_component->get_comp_type() == COMP_TYPES::COMP_LED)
		{
			pOut->PrintMsg("LED Can't be the source.");
			checkIfSourceIsLED = true;

			return;

		}

		//Clear Status Bar
		pOut->ClearStatusBar();
	}
	//Print Action Message
	pOut->PrintMsg("connect two gates: Choose the destination gate");




	if (num_of_call == 2)
	{
		pIn->GetPointClicked(Cx2, Cy2);

		pManager->ExecuteAction(SELECT);

		Component* p_component = pManager->GetLastSelectedComponent();
		if (!p_component)//check if its Null
		{
			pOut->PrintMsg("You Can't choose a white space.");
			b = true;
			return;
		}

		if (p_component->get_comp_type() == COMP_TYPES::COMP_SWITCH)
		{
			pOut->PrintMsg("SWITCH Can't be the DEST.");

			return;

		}
		if (checkIfSourceIsLED == true)
		{
			pOut->PrintMsg("LED Can't be the source.");

			return;
		}

		//Clear Status Bar
		pOut->ClearStatusBar();
	}
}


void Connect::Execute()
{
	//Get the two Gates wanted to be connected
	Output* pOut = pManager->GetOutput();

	bool a, b;
	bool IfLED;
	ReadActionParameters(a, b, IfLED, 1);

	if (a == true || b == true || IfLED == true)
	{
		return;
	}
	Component* SrcComp = pManager->GetLastSelectedComponent();

	OutputPin* out = SrcComp->getOutputPin();

	GraphicsInfo GInfo; //Gfx info to be used to construct the connection
	InputPin* in;


	ReadActionParameters(a, b, IfLED, 2);
	if (a == true || b == true || IfLED == true)
	{
		return;
	}
	Component* DistComp = pManager->GetLastSelectedComponent();

	in = DistComp->getInputPin(); //array of inout pins

	bool g = pManager->Check_gates_to_connect(SrcComp, DistComp);
	if (g == false)
		return;

	InputPin* selected_pin;
	//bool i = pManager->Check_pins_to_connect(DistComp, in, GInfo,selected_pin);





	int no_input_pins = DistComp->getNoOfInputpins();
	for (int j = 0; j < no_input_pins; j++)
	{
		bool isConnected = in[j].get_is_connected();
		if (isConnected == false)
		{
			selected_pin = &in[j];
			in[j].set_is_connected(true);
			COMP_TYPES type = DistComp->get_comp_type();
			setDisPinGInfo(type, j, DistComp->getGraphicsInfo(), GInfo);
			break;

		}

		if (j == no_input_pins - 1 && isConnected == true)
		{
			pOut->PrintMsg("Error: All input pins of this component are already connected");
			return;
		}

	}



	setSrcPinGInfo(SrcComp->getGraphicsInfo(), GInfo);



	Connection* pA = new Connection(GInfo, out, selected_pin);
	out->ConnectTo(pA);
	selected_pin->ConnectTo(pA);

	//pA->Draw(pOut);
	pManager->DeselectComponentExcept();
	pManager->AddComponent(pA);

}
void Connect::setDisPinGInfo(COMP_TYPES type, int j, const GraphicsInfo& gate, GraphicsInfo& GInfo)
{
	switch (type)
	{
	case COMP_TYPES::COMP_LED:
	{
		GInfo.x2 = gate.x1 + 23;
		GInfo.y2 = (gate.y1 + (gate.y2 - gate.y1) / 2) + 26;
		break;
	}
	case COMP_TYPES::AND_2:
		if (j == 0)
		{
			GInfo.x2 = gate.x1;
			GInfo.y2 = gate.y1 + 15 + 1;

		}
		else if (j == 1)
		{
			GInfo.x2 = gate.x1;
			GInfo.y2 = gate.y2 - 14 - 2;
		}
		break;
	case COMP_TYPES::AND_3:
		if (j == 0)
		{
			GInfo.x2 = gate.x1;
			GInfo.y2 = gate.y1 + 16;

		}
		else if (j == 1)
		{
			GInfo.x2 = gate.x1;
			GInfo.y2 = gate.y1 + (gate.y2 - gate.y1) / 2;

		}
		else if (j == 2)
		{
			GInfo.x2 = gate.x1;
			GInfo.y2 = gate.y2 - 16;

		}
		break;
	case COMP_TYPES::INV_:
		GInfo.x2 = gate.x1;
		GInfo.y2 = gate.y1 + (gate.y2 - gate.y1) / 2;
		break;
	case COMP_TYPES::NAND_2:
		if (j == 0)
		{
			GInfo.x2 = gate.x1;
			GInfo.y2 = gate.y1 + 15;
		}
		else if (j == 1)
		{
			GInfo.x2 = gate.x1;
			GInfo.y2 = gate.y2 - 14 + 3;
		}
		break;
	case COMP_TYPES::NOR_2:
		if (j == 0)
		{
			GInfo.x2 = gate.x1;
			GInfo.y2 = gate.y1 + 15 + 7;
		}
		else if (j == 1)
		{
			GInfo.x2 = gate.x1;
			GInfo.y2 = gate.y2 - 14 - 4;
		}
		break;
	case COMP_TYPES::NOR_3:
		if (j == 0)
		{
			GInfo.x2 = gate.x1 + 11;
			GInfo.y2 = gate.y1 + 16 + 1;

		}
		else if (j == 1)
		{
			GInfo.x2 = gate.x1 + 11;
			GInfo.y2 = gate.y1 + (gate.y2 - gate.y1) / 2 + 1;
		}
		else if (j == 2)
		{
			GInfo.x2 = gate.x1 + 11;
			GInfo.y2 = gate.y2 - 16 + 1;
		}
		break;
	case COMP_TYPES::Buff_:
		GInfo.x2 = gate.x1;
		GInfo.y2 = gate.y1 + (gate.y2 - gate.y1) / 2;
		break;
	case COMP_TYPES::OR_2:
		if (j == 0)
		{
			GInfo.x2 = gate.x1 + 8;
			GInfo.y2 = gate.y1 + 15 - 7;
		}
		else if (j == 1)
		{
			GInfo.x2 = gate.x1 + 8;
			GInfo.y2 = gate.y2 - 14 + 3;
		}
		break;
	case COMP_TYPES::XNOR_2:
		if (j == 0)
		{
			GInfo.x2 = gate.x1;
			GInfo.y2 = gate.y1 + 15 + 5;
		}
		else if (j == 1)
		{
			GInfo.x2 = gate.x1;
			GInfo.y2 = gate.y2 - 14 - 5;
		}
		break;
	case COMP_TYPES::XOR_2:
		if (j == 0)
		{
			GInfo.x2 = gate.x1;
			GInfo.y2 = gate.y1 + 15;
		}
		else if (j == 1)
		{
			GInfo.x2 = gate.x1;
			GInfo.y2 = gate.y2 - 14;
		}
		break;
	case COMP_TYPES::XOR_3:
		if (j == 0)
		{
			GInfo.x2 = gate.x1;
			GInfo.y2 = gate.y1 + 16;
		}
		else if (j == 1)
		{
			GInfo.x2 = gate.x1;
			GInfo.y2 = gate.y1 + (gate.y2 - gate.y1) / 2;
		}
		else if (j == 2)
		{
			GInfo.x2 = gate.x1;
			GInfo.y2 = gate.y2 - 16;
		}
		break;
	default:
		break;
	}
}
void Connect::setSrcPinGInfo(const GraphicsInfo& gate, GraphicsInfo& GInfo)
{
	GInfo.x1 = gate.x2;
	GInfo.y1 = gate.y1 + (gate.y2 - gate.y1) / 2;
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