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
	Output* pOut = pManager->GetOutput();

	pOut->PrintMsg("Please Select a Connection, LED or a Switch to see its state.");

	COMP_TYPES type;
	int x, y;
	pManager->GetInput()->GetPointClicked(x, y);
	int target = pManager->which_component(type);
	Component* l_selected = NULL;


	if (target != -1)
		l_selected = pManager->get_comp_at(target);


	if (l_selected) {
		if (type == COMP_TYPES::COMP_CONN)
		{
			Connection* conn = (Connection*)l_selected;
			STATUS a = conn->get_is_on();

			if (a)
			{
				pOut->PrintMsg("The Connection is on");

			}
			else
			{
				pOut->PrintMsg("The Connection is off");

			}


		}
		if (type == COMP_TYPES::COMP_SWITCH)
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

		if (type == COMP_TYPES::COMP_LED)
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


}

void CircuitProding::ReadActionParameters()
{

}

void CircuitProding::Undo()
{}

void CircuitProding::Redo()
{}

