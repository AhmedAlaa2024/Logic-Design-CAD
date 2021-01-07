#include "Label.h"

    // ============================== Ahmed Alaa edited here ==============================

Label::Label(ApplicationManager* pApp, Component* comp) : Action(pApp), component(comp)
{
    Execute();
}

//-----Rufaidah (I need this constructor)
Label::Label(ApplicationManager* pApp, Component* comp, int f) : Action(pApp), component(comp)
{
    DisplayLabel(); // To display the label above the component.
}

string Label::SetLabel()
{
    pManager->GetOutput()->PrintMsg("Please, Enter the label: ");
    return pManager->GetInput()->GetString(pManager->GetOutput()); // To make an input object to get the string from the user
}

string Label::GetLabel()
{
    return component->get_m_Label(); // To get the label from m_Label in the selected component
}

void Label::DisplayLabel()
{
    pManager->GetOutput()->DrawTextbox(GetLabel(), component); // To call the function which responsible for drawing a textbox above the selected component
}

void Label::ReadActionParameters()
{
}

void Label::Execute()
{
    if (component != NULL) // To make sure that there is a selected component
        if (component->get_m_Label() == "") // To make sure that there is not an existing label
        {
            component->set_m_Label(SetLabel()); // To get the label from the user
            DisplayLabel(); // To display the label above the component.
            pManager->SetLastSelectedComponent(-1); // To clear the component from the lastSelectedComponent in pManager
        }
        else {
            DisplayLabel(); // To display the label above the component.
            pManager->SetLastSelectedComponent(-1); // To clear the component from the lastSelectedComponent in pManager
        }
    else
        pManager->GetOutput()->PrintMsg("Please, Select an component before adding a label.");
}

void Label::Undo()
{
}

void Label::Redo()
{
}

    // ==================================== Ahmed Alaa ====================================