#include "step_Simulation.h"


#include "../Components/Component.h"
#include "../Components/Connection.h"
#include "../GUI/Output.h"

step_Simulation::step_Simulation(ApplicationManager* pApp) :Action(pApp)
{
}




void step_Simulation::Execute()
{

	Output* pOut = pManager->GetOutput();

	int no_conn_to_next = 0;
	InputPin* next_in_pins[100]; //array of pointers to the next input pins in each stage


	int sw_no = 0;
	SWITCH** SWs = pManager->get_switches(sw_no);

	if (SWs == NULL)
	{
		pOut->PrintMsg("Error: There is NO Switches");
		return;
	}


	int j = 0;

	//letting the switches operate and getting the input pins of the next
	for (int i = 0; i < sw_no; ++i) // for each switch
	{
		SWs[i]->Operate();
		int no_conns;

		Connection** Conns = SWs[i]->getOutputPin()->get_connections(no_conns);

		no_conn_to_next += no_conns;

		//each connection has an end (Input pin)

		for (int i = 0; i < no_conns; ++i) //operate and get the pins on the connections
		{

			Conns[i]->Operate();
			next_in_pins[j++] = Conns[i]->getDestPin();

		}
	}



	//now i have all the input pins in next_in_pins and their number no_conn_to_next

	int no_leds;
	LED** leds = pManager->get_connected_leds(no_leds);

	if (leds == NULL)
	{
		pOut->PrintMsg("Error: There is NO LEDS");
		return;
	}

	for (int i = 0; i < no_leds; ++i)
	{
		leds[i]->set_is_reached(false);
	}


	while (true) {
		j = 0; // to reuse it
		int num = no_conn_to_next; //saving the number of conns before setting it to zero
		no_conn_to_next = 0;
		InputPin* last_in[100]; //to store the next input pins and give it to next_in_pins after looping
		for (int i = 0; i < num; ++i)
		{

			Component* current_comp = next_in_pins[i]->getComponent();
			if (current_comp)
				current_comp->Operate();
			else
				continue;


			//check if its a led then check if all leds are reached to stop the simulation
			if (current_comp->GetOutPinStatus() == -1)
			{
				//condition to stop
				bool stop = true;
				for (int i = 0; i < no_leds; ++i)
				{
					if (leds[i]->get_is_reached() == false)
						stop = false;
				}
				if (stop)
					return;

				continue;
			}



			int no_conns;

			Connection** Conns = current_comp->getOutputPin()->get_connections(no_conns);

			no_conn_to_next += no_conns;

			//each connection has an end (Input pin)

			for (int i = 0; i < no_conns; ++i) //operate and get the pins on the connections
			{

				Conns[i]->Operate();
				last_in[j++] = Conns[i]->getDestPin();

			}


		}

		for (int i = 0; i < no_conn_to_next; ++i)
		{
			next_in_pins[i] = last_in[i];
		}

	}



}

void step_Simulation::ReadActionParameters()
{

}

void step_Simulation::Undo()
{}

void step_Simulation::Redo()
{}

step_Simulation::~step_Simulation()
{
}