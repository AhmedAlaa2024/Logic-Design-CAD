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

	Output* pOut = pManager->GetOutput();

	bool valid = pManager->validate_circuit();
	if (valid) {
		int num;
		pManager->DeselectComponentExcept();
		UI.AppMode = SIMULATION;
		pOut->ClearWindow();
		pOut->CreateSimulationToolBar();
		pManager->ExecuteAction(SIMULATE);
	}
	else
		pOut->PrintMsg("Ciruit is not Valid, please don't leave any pins floating");



	
}

void SwitchToSimulation::ReadActionParameters()
{

}

void SwitchToSimulation::Undo()
{}

void SwitchToSimulation::Redo()
{}

