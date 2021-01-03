#include "Delete.h"
	// ============================== Ahmed Alaa edited here ==============================

Delete::Delete(ApplicationManager* pApp, Component* comp): Action(pApp), component(comp)
{
	int numOfComonents = 0;
	Component** compList = pManager->GetandSetComponents(numOfComonents); // To be enable get and edit the all components in the screen
	for (int i = 0; i < numOfComonents; i++) // To iterate on all of the existing components
	{
		if (component->get_id() == compList[i]->get_id()) // To make the following codes on the lastSelectedComponent 
		{
			pManager->GetOutput()->ClearComponentArea(compList[i]->getGraphicsInfo()); // To clear the component from the screen
			// The delete of the pointer to the input and output pins of the selected component is the responsibilty of the desturctor of the class Gate
			delete compList[i]; // To delete the pointer that pointing to the seleted component
			compList = nullptr; // To make the pointer point to a null pointer
			for (int j = i; j < numOfComonents - 1; j++) // To shift the components in compList to avoid leting a blank component
				swap(compList[j], compList[j + 1]);
			pManager->SetCompCount();
		}
	}
}

void Delete::ReadActionParameters()
{
}

void Delete::Execute()
{
}

void Delete::Undo()
{
}

void Delete::Redo()
{
}
	// ==================================== Ahmed Alaa ====================================