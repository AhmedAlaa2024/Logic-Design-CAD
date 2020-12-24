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

