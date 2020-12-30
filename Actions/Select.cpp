#include "Select.h"


Select::Select(): Action(pManager)
{
	ReadActionParameters(); // To get the clicked coordinates

	COMP_TYPES comp_type;
	int target = which_component(comp_type); // To get the index of the target component.

	if (target == -1) // To check if the user clicked on a blank space
		Deselect();
	else
	{
		int numOfComonents = 0;
		Component* const* compList = pManager->getComponents(numOfComonents); // To get a copy of the all components in the screen
		GraphicsInfo r_GfxInfo = compList[target]->getGraphicsInfo(); // To get the x1, y1, x2, y2 of the clicked component

		switch (comp_type) // I used switch case because the behaviour will be different from Gate, Switch and Led.
		{
		case COMP_TYPES::COMP_GATE:
			compList[target]->Draw(pManager->GetOutput()); // It will override a new image indicate that the gate is selected
			break;
		case COMP_TYPES::COMP_SWITCH:
			pManager->GetOutput()->DrawSWITCH(r_GfxInfo, false, true); // It will override a new image indicate that the switch is selected
			break;
		case COMP_TYPES::COMP_LED:
			pManager->GetOutput()->DrawLED(r_GfxInfo, false, true); // It will override a new image indicate that the led is selected
			break;
		case COMP_TYPES::COMP_CONN:
			pManager->GetOutput()->DrawConnection(r_GfxInfo, true); // It will override a new image indicate that the conection is selected
			break;
		default:
			break;
		}
	}
}

int Select::which_component(COMP_TYPES& comptype)
{
	int numOfComonents = 0, target = -1; // The default value of target is -1
	Component* const* compList = pManager->getComponents(numOfComonents); // To get a copy of the all components in the screen
	comptype = COMP_TYPES::COMP_GENERAL; // The default value of the component clicked is COMP_GENERAL
	for (int i = 0; i < numOfComonents; i++) { // We should loop on all of the components of compList to determine which component is selected
		int x1 = compList[i]->getGraphicsInfo().x1;
		int y1 = compList[i]->getGraphicsInfo().y1;
		int x2 = compList[i]->getGraphicsInfo().x2;
		int y2 = compList[i]->getGraphicsInfo().y2;

		// I compare the clicked coordinates with the coordinates of each component.

		if (x1 <= x && x <= x2 && y1 <= y && y <= y2) {
			compList[i]->set_is_selected(true); // Set the is_select data member to true.
			comptype = compList[i]->get_comp_type();
			target = i;
			break;
		}
	}

	

	return target;
}

void Select::Deselect()
{
	int numOfComonents = 0;
	Component* const* compList = pManager->getComponents(numOfComonents);
	// Deselect all the components on the screen
	for (int i = 0; i < numOfComonents; i++)
		compList[i]->set_is_selected(false);
}

void Select::ReadActionParameters()
{
	pManager->GetInput()->GetPointClicked(x, y); // To get the x, y coordinates of point clicked
}

void Select::Execute()
{
}

void Select::Undo()
{
}

void Select::Redo()
{
}
