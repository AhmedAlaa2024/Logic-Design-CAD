#include "SimulateCircuit.h"


#include "../Components/Component.h"
#include "../Components/Connection.h"
#include "../GUI/Output.h"

SimulateCircuit::SimulateCircuit(ApplicationManager* pApp) :Action(pApp)
{






}




void SimulateCircuit::Execute()
{

	Output* pOut = pManager->GetOutput();
	int CompNum;
	Component* const* CompList = pManager->getComponents(CompNum);

	//operate the switches
	for (int i = 0; i < CompNum; ++i)
	{
		if (CompList[i]->GetInputPinStatus(0) == -1)
		{
			CompList[i]->Operate(); //switches is done working
			const OutputPin* switch_pin = (OutputPin*)CompList[i]->getOutputPin();
			int no_conns;
			auto Conns= switch_pin->get_connections(no_conns);

			for (int i = 0; i < no_conns; ++i)
			{
				Conns[i]->Operate();


				
			}
			


		}

	}






}

void SimulateCircuit::ReadActionParameters()
{

}

void SimulateCircuit::Undo()
{}

void SimulateCircuit::Redo()
{}

SimulateCircuit::~SimulateCircuit()
{
}