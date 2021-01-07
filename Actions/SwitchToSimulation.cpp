#include "SwitchToSimulation.h"

#include "SimulateCircuit.h"
#include "..\ApplicationManager.h"

SwitchToSimulation::SwitchToSimulation(ApplicationManager* pApp) :Action(pApp)
{
}

SwitchToSimulation::~SwitchToSimulation()
{
}


void SwitchToSimulation::Execute()
{
	UI.AppMode = SIMULATION;
	Action* pAct = new SimulateCircuit(pManager);
	pAct->Execute();
	delete pAct;

	Output* pOut = pManager->GetOutput();

	
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

