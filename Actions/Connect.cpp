#include "Connect.h"
#include "..\ApplicationManager.h"

#include "..\Components\Connection.h"

#include <typeinfo>
#include <iostream>

using namespace std;


Connect::Connect(ApplicationManager* pApp) :Action(pApp)
{

}


void Connect::ReadActionParameters(bool& prev_Execute, bool& if_not_valid_gate, int num_of_call)
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	int Cx = 0;
	int	Cy = 0;
	if_not_valid_gate = false;
	prev_Execute = false;

	if (num_of_call == 1)
	{
		//Print Action Message
		pOut->PrintMsg("connect two gates: Choose the source gate");

		pIn->GetPointClicked(Cx, Cy);

		pManager->ExecuteAction(SELECT);

		Component* p_component = pManager->GetLastSelectedComponent();
		if (!p_component)//check if its Null
		{
			pOut->PrintMsg("You Can't choose a white space.");
			prev_Execute = true;
			return;
		}

		if (p_component->get_comp_type() == COMP_TYPES::COMP_LED)
		{
			pOut->PrintMsg("LED Can't be the Source.");
			if_not_valid_gate = true;
			return;
		}

	}


	if (num_of_call == 2)

	{
		//Print Action Message
		pOut->PrintMsg("connect two gates: Choose the destination gate");

		pIn->GetPointClicked(Cx, Cy);

		pManager->ExecuteAction(SELECT);

		Component* p_component = pManager->GetLastSelectedComponent();

		if (!p_component)//check if its Null
		{
			pOut->PrintMsg("You Can't choose a white space.");
			prev_Execute = true;
			return;
		}

		if (p_component->get_comp_type() == COMP_TYPES::COMP_SWITCH)
		{
			pOut->PrintMsg("SWITCH Can't be the DEST.");
			if_not_valid_gate = true;
			return;

		}
	}

	//Clear Status Bar
	pOut->ClearStatusBar();
}


void Connect::Execute()
{
	//Get the two Gates wanted to be connected
	Output* pOut = pManager->GetOutput();

	bool prevent_Execute;
	bool If_not_valid_to_connect;

	//first call
	ReadActionParameters(prevent_Execute, If_not_valid_to_connect, 1);
	
	if (prevent_Execute == true || If_not_valid_to_connect == true)
	{
		return;
	}

	Component* SrcComp = pManager->GetLastSelectedComponent();

	OutputPin* out = SrcComp->getOutputPin();

	GraphicsInfo GInfo; //Gfx info to be used to construct the connection

	//second call
	ReadActionParameters(prevent_Execute, If_not_valid_to_connect, 2);
	
	if (prevent_Execute == true || If_not_valid_to_connect == true)
	{
		return;
	}
	Component* DistComp = pManager->GetLastSelectedComponent();

	InputPin* in;

	in = DistComp->getInputPin(); //array of inout pins

	if (DistComp == SrcComp)
	{
		pOut->PrintMsg("Error: You have already chosen this gate as a source gate. You can not connect a gate to itself");
		return;
	}

	InputPin* selected_pin = NULL;


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