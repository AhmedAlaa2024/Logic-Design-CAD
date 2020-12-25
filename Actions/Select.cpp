#include "Select.h"


COMP_TYPES Select::what_object(int x, int y)
{
	pManager->GetInput()->GetPointClicked(x, y); // To get the x, y coordinates of point clicked
	int numOfComonents = 0;
	Component* const* compList = pManager->getComponents(numOfComonents);
	for (int i = 0; i < numOfComonents; i++) {
		int x1 = compList[i]->getGraphicsInfo().x1;
		int y1 = compList[i]->getGraphicsInfo().y1;
		int x2 = compList[i]->getGraphicsInfo().x2;
		int y2 = compList[i]->getGraphicsInfo().y2;

		if (x1 <= x && x <= x2 && y1 <= y && y <= y2){
			compList[i]->set_is_selected(true);
			return compList[i]->get_comp_type();
		}
	}

	return 0;
}
