#include "Select.h"


Select::Select()
{
	COMP_TYPES comp_type;
	Component* const*  target = what_object(comp_type);
}

Component* const* Select::what_object(COMP_TYPES &comptype)
{
	int x = 0, y = 0;
	pManager->GetInput()->GetPointClicked(x, y); // To get the x, y coordinates of point clicked
	int numOfComonents = 0, target = 0;;
	Component* const* compList = pManager->getComponents(numOfComonents);
	comptype = COMP_TYPES::COMP_GENERAL;
	for (int i = 0; i < numOfComonents; i++) {
		int x1 = compList[i]->getGraphicsInfo().x1;
		int y1 = compList[i]->getGraphicsInfo().y1;
		int x2 = compList[i]->getGraphicsInfo().x2;
		int y2 = compList[i]->getGraphicsInfo().y2;

		if (x1 <= x && x <= x2 && y1 <= y && y <= y2){
			compList[i]->set_is_selected(true);
			comptype = compList[i]->get_comp_type();
			target = i;
			break;
		}
	}
	
	
	switch (comptype)
	{
	case COMP_TYPES::COMP_GENERAL:
		for (int i = 0; i < numOfComonents; i++)
			compList[i]->set_is_selected(false);
		break;
	case COMP_TYPES::COMP_GATE:
		compList[target]->Draw(pManager->GetOutput());
		break;
	case COMP_TYPES::COMP_SWITCH:
		compList[target]->Draw(pManager->GetOutput());
		break;
	case COMP_TYPES::COMP_LED:
		compList[target]->Draw(pManager->GetOutput());
		break;
	case COMP_TYPES::COMP_CONN:
		compList[target]->Draw(pManager->GetOutput());
		break;
	default:
		break;
	}

	return &compList[target];
}
