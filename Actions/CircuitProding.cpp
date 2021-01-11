#include "CircuitProding.h"
#include "..\ApplicationManager.h"
#include "../Components/Connection.h"

CircuitProding::CircuitProding(ApplicationManager* pApp) :Action(pApp)
{
}

CircuitProding::~CircuitProding()
{
}


void CircuitProding::Execute()
{

	pManager->ExecuteAction(SELECT);
	Component* l_selected = pManager->GetLastSelectedComponent();
	Output* pOut = pManager->GetOutput();
	if(l_selected->get_comp_type() == COMP_TYPES::COMP_CONN)
	{
		Connection* conn = (Connection*)l_selected;
		STATUS a =conn->get_is_on();

		if(a)
		{
			pOut->PrintMsg("The Connection is on");
			
		}else
		{
			pOut->PrintMsg("The Connection is off");

		}

		
	}
	if (l_selected->get_comp_type() == COMP_TYPES::COMP_SWITCH)
	{
		SWITCH* sw = (SWITCH*)l_selected;
		STATUS a = sw->get_state();

		if (a)
		{
			pOut->PrintMsg("The Switch is on");

		}
		else
		{
			pOut->PrintMsg("The Switch is off");

		}


	}

	if (l_selected->get_comp_type() == COMP_TYPES::COMP_LED)
	{
		LED* led = (LED*)l_selected;
		STATUS a = led->get_is_High();

		if (a)
		{
			pOut->PrintMsg("The LED is on");

		}
		else
		{
			pOut->PrintMsg("The LED is off");

		}


	}
	

}

void CircuitProding::ReadActionParameters()
{

}

void CircuitProding::Undo()
{}

void CircuitProding::Redo()
{}

