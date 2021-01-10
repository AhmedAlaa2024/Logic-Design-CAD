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


	int num;
	pManager->DeselectComponentExcept();

	pOut->ClearWindow();
	pOut->CreateSimulationToolBar();
	UI.AppMode = SIMULATION;
	pManager->ExecuteAction(SIMULATE);

	
}

void SwitchToSimulation::ReadActionParameters()
{

}

void SwitchToSimulation::Undo()
{}

void SwitchToSimulation::Redo()
{}

