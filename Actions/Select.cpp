#include "Select.h"

#include "SimulateCircuit.h"


Select::Select(ApplicationManager* pApp): Action(pApp), x(0), y(0)
{

}

void Select::ReadActionParameters()
{
	pManager->GetInput()->GetLastClicked(x, y); // To get the x, y coordinates of point clicked
}

void Select::Execute()
{
	ReadActionParameters(); // To get the clicked coordinates

	COMP_TYPES comp_type;
	int target = pManager->which_component(comp_type); // To get the index of the target component.

	if (target == -1) // To check if the user clicked on a blank space
	{
		pManager->DeselectComponentExcept(); // To deselect all the components on the screen
	}
	else
	{
		pManager->DeselectComponentExcept(target); // To deselect all the component except target
		pManager->SelectComponent(target); // To make a notation that the clicked component is selected.
		pManager->SetLastSelectedComponent(target); // To make a pointer to the last selected component
		Component* LastSelectedComponent = pManager->GetLastSelectedComponent();
		GraphicsInfo r_GfxInfo = LastSelectedComponent->getGraphicsInfo();
		switch (comp_type) // I used switch case because the behaviour will be different from Gate, Switch and Led.
		{
		case COMP_TYPES::COMP_GATE:
			LastSelectedComponent->Draw(pManager->GetOutput()); // It will override a new image indicate that the gate is selected
			break;
		case COMP_TYPES::COMP_SWITCH:
		{
			if (UI.AppMode == DESIGN) {
				LastSelectedComponent->set_is_selected(true);

				// It will override a new image indicate that the switch is selected
				break;
			}
			if (dynamic_cast<SWITCH*>(LastSelectedComponent)->get_state())
			{
				dynamic_cast<SWITCH*>(LastSelectedComponent)->set_state(LOW);
			}
			else
			{
				dynamic_cast<SWITCH*>(LastSelectedComponent)->set_state(HIGH);
			}
			Action* pAct = new SimulateCircuit(pManager);
			pAct->Execute();
			delete pAct;
			break;
		}

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

void Select::Undo()
{
}

void Select::Redo()
{
}

Select::~Select()
{
}

// ==================================== Ahmed Alaa ====================================