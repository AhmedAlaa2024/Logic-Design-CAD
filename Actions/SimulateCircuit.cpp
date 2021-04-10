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
	
	int n_com = 0;
	Component** list  = pManager->get_CompList(n_com);

	int sw_no = 0;
	SWITCH** SWs = pManager->get_switches(sw_no);

	if (SWs == NULL)
	{
		pOut->PrintMsg("Error: There is NO Switches");
		return;
	}

	int no_leds;
	LED** leds = pManager->get_connected_leds(no_leds);

	if (leds == NULL)
	{
		pOut->PrintMsg("Error: There is NO LEDS");
		return;
	}

	
	
	int no_iterations = log2(n_com) + 5;


	for (int i = 0; i < no_iterations; ++i)
	{
		for (int i = 0; i < n_com; ++i)
		{
			list[i]->Operate();
			
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