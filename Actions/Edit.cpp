#include "Edit.h"

// ============================== Ahmed Alaa edited here ==============================

Edit::Edit(ApplicationManager* pApp, Component* comp) : Action(pApp), component(comp)
{
}

string Edit::SetLabel()
{
    pManager->GetOutput()->PrintMsg(GetLabel());
    return pManager->GetInput()->GetString(pManager->GetOutput(), GetLabel()); // To make an input object to get the string from the user
}

string Edit::GetLabel()
{
    return component->get_m_Label(); // To get the label from m_Label in the selected component
}

void Edit::DisplayLabel()
{
    pManager->GetOutput()->DrawTextbox(GetLabel(), component); // To call the function which responsible for drawing a textbox above the selected component
}

void Edit::ReadActionParameters()
{
}

void Edit::Execute()
{
    if (component != NULL) // To make sure that there is a selected component
        if (component->get_m_Label() == "") // To make sure that there is not an existing label
        {
            pManager->GetOutput()->PrintMsg("Sorry, There is no label to be displayed!");
        }
        else {
            pManager->GetOutput()->ClearLabelArea(component->getGraphicsInfo(), GetLabel().size());
            component->set_m_Label(SetLabel()); // To get the label from the user
            DisplayLabel(); // To display the label above the component.
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