#include "Edit.h"

// ============================== Ahmed Alaa edited here ==============================

Edit::Edit(ApplicationManager* pApp, LabelOfComp* label) : Action(pApp), label(label)
{
	r_GfxInfo = pManager->GetLastSelectedComponent()->getGraphicsInfo();
}

void Edit::SetLabel()
{
	pManager->GetOutput()->PrintMsg(GetLabel());
	label->set_label(pManager->GetInput()->GetString(pManager->GetOutput())); // To make an input object to get the string from the user
}

string Edit::GetLabel()
{
	return label->get_label(); // To get the label from m_Label in the selected component
}


void Edit::ReadActionParameters()
{
	SetLabel();
}

void Edit::Execute()
{
	if (pManager->GetLastSelectedComponent() != NULL) // To make sure that there is a selected component
	{
		if (pManager->GetLastSelectedComponent()->get_comp_type() == COMP_TYPES::COMP_CONN)
		{
			pManager->DeleteComponent();

			pManager->ExecuteAction(ADD_CONNECTION);

			return; // To break the execution
		}
		if (label == NULL) // To make sure that there is not an existing label
		{
			pManager->GetOutput()->PrintMsg("Sorry, This component has not a label to be edited!");
		}
		else {
			delete label;
			label = new LabelOfComp(r_GfxInfo);
			ReadActionParameters(); // To get the label from the user
		}
	}
	else
		pManager->GetOutput()->PrintMsg("Please, Select an component before editing a label.");
}

void Edit::Undo()
{
}

void Edit::Redo()
{
}

// ==================================== Ahmed Alaa ====================================