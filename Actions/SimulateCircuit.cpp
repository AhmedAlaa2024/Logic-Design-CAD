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
	//Component* const* CompList = pManager->getComponents(CompNum);
	int no_conn_to_next = 0;
	InputPin* next_in_pins[100]; //array of pointers to the next input pins in each stage
	

	int sw_no = 0;
	SWITCH** SWs = pManager->get_switches(sw_no);

	int j = 0;
	//letting the switches operate ang getting the input pins of the next
	for (int i = 0; i < sw_no; ++i) // for each switch
	{
		SWs[i]->Operate();
		int no_conns;

		Connection** Conns = SWs[i]->getOutputPin()->get_connections(no_conns);

		no_conn_to_next += no_conns;

		//each connection has an end (Input pin)

		for (int i = 0; i < no_conns; ++i) //operate ang get the pins on the connections
		{
			
			Conns[i]->Operate();
			next_in_pins[j++] = Conns[i]->getDestPin();

		}
	}

	

	//now i have all the input pins in next_in_pins and their number no_conn_to_next


	while (true) {
		j = 0; // to reuse it
		int num = no_conn_to_next; //saving the number of conns before setting it to zero
		no_conn_to_next = 0;
		for (int i = 0; i < num; ++i)
		{

			Component* current_comp = next_in_pins[i]->getComponent();
			current_comp->Operate();

			//check if its a led
			if (current_comp->GetOutPinStatus() == -1)
				return;


			int no_conns;

			Connection** Conns = current_comp->getOutputPin()->get_connections(no_conns);

			no_conn_to_next += no_conns;

			//each connection has an end (Input pin)

			for (int i = 0; i < no_conns; ++i) //operate ang get the pins on the connections
			{

				Conns[i]->Operate();
				next_in_pins[j++] = Conns[i]->getDestPin();

			}


		}


	}
	/*
	//operate the switches









	for (int i = 0; i < CompNum; ++i)
	{

		if (CompList[i]->GetInputPinStatus(0) == -1)
		{
			CompList[i]->Operate(); //switches is done working
			const OutputPin* switch_pin = (OutputPin*)CompList[i]->getOutputPin();

			auto Conns = switch_pin->get_connections(no_conn_to_next);

			next_in_pins = new InputPin* [no_conn_to_next];

			for (int i = 0; i < no_conn_to_next; ++i)
			{
				Conns[i]->Operate();
				next_in_pins[j++] = Conns[i]->getDestPin();

			}

		}

	}
	j = 0;
	while (true)
	{
		Component* pc;


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
		if (pc->GetOutPinStatus() == -1)
			break;
	}

	*/


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