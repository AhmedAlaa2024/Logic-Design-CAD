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
	int no_conn_to_next = 0;
	InputPin** next_in_pins;
	InputPin** next_out_pins;
	int j = 0;

	//operate the switches
	for (int i = 0; i < CompNum; ++i)
	{

		if (CompList[i]->GetInputPinStatus(0) == -1)
		{
			CompList[i]->Operate(); //switches is done working
			const OutputPin* switch_pin = (OutputPin*)CompList[i]->getOutputPin();
			
			auto Conns= switch_pin->get_connections(no_conn_to_next);

			next_in_pins = new InputPin * [no_conn_to_next];
			
			for (int i = 0; i < no_conn_to_next; ++i)
			{
				Conns[i]->Operate();
				next_in_pins[j++] = Conns[i]->getDestPin();
				
			}
			
		}

	}

	while (true)
	{
		Component* pc = next_in_pins[0]->getComponent();


		for (int i = 0; i < no_conn_to_next; ++i)
		{
			 pc = next_in_pins[i]->getComponent();
			pc->Operate();
			auto Conns = pc->getOutputPin()->get_connections(no_conn_to_next);

			delete[] next_in_pins;
			next_in_pins = new InputPin * [no_conn_to_next];

			for (int i = 0; i < no_conn_to_next; ++i)
			{
				Conns[i]->Operate();
				next_in_pins[j++] = Conns[i]->getDestPin();

			}

		}
		if(pc->GetOutPinStatus() == -1)
			break;
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