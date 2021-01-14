#include "Label.h"

    // ============================== Ahmed Alaa edited here ==============================

Label::Label(ApplicationManager* pApp, LabelOfComp* label) : Action(pApp), label(label)
{
    r_GfxInfo = pManager->GetLastSelectedComponent()->getGraphicsInfo();
}

/*
//-----Rufaidah (I need this constructor)
Label::Label(ApplicationManager* pApp, Component* comp, int f) : Action(pApp), component(comp)
{
    DisplayLabel(); // To display the label above the component.
}
*/


void Label::SetLabel()
{
    pManager->GetOutput()->PrintMsg("Please, Enter the label: ");
    label->set_label(pManager->GetInput()->GetString(pManager->GetOutput())); // To make an input object to get the string from the user
}

string Label::GetLabel()
{
    return label->get_label(); // To get the label from m_Label in the selected component
}

void Label::ReadActionParameters()
{
    SetLabel();
}

void Label::Execute()
{
    if (label == NULL)
    {
        label = new LabelOfComp(r_GfxInfo);
        ReadActionParameters();
    }
    else
        pManager->GetOutput()->PrintMsg("There is already existing label for the selected component!");
    
}

void Label::Undo()
{
}

void Label::Redo()
{
}

    // ==================================== Ahmed Alaa ====================================