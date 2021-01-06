#include "SwitchToSimulation.h"
#include "..\ApplicationManager.h"

SwitchToSimulation::SwitchToSimulation(ApplicationManager* pApp) :Action(pApp)
{
}

SwitchToSimulation::~SwitchToSimulation()
{
}


void SwitchToSimulation::Execute()
{

	Output* pOut = pManager->GetOutput();
	//TODO add action simulation
	int num;
	auto comps = pManager->getComponents(num);
	for (int i = 0; i < num; ++i)
	{
		comps[i]->set_is_selected(false);
	}
	pManager->SetLastSelectedComponent(-1);

	


	pOut->ClearWindow();
	pOut->CreateSimulationToolBar();
}

void SwitchToSimulation::ReadActionParameters()
{

}

void SwitchToSimulation::Undo()
{}

void SwitchToSimulation::Redo()
{}

