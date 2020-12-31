#include "Label.h"

Label::Label(): Action(pManager)
{
    SetLabel(label);
    
}

void Label::SetLabel(string& label)
{
    label = pManager->GetInput()->GetString(pManager->GetOutput());
}

string Label::GetLabel()
{
    return label;
}

void Label::DisplayLabel(Component* target)
{
    r_GfxInfo = target->getGraphicsInfo();
}
