#include "CreateTruthTable.h"
#include "..\ApplicationManager.h"

#include <iostream>
using namespace std;

CreateTruthTable::CreateTruthTable(ApplicationManager* pApp) :Action(pApp)
{
	current_comb_ = 0;
	inputs = pManager->get_switches(num_of_inputs);
	binary_current_comb_ = new int[num_of_inputs];//array of 0 and 1 to save to combinations

	for (int i = 0; i < num_of_inputs; ++i)
	{
		binary_current_comb_[i] = 0; //first combination is 0 0 0 0 0 0 0 0...
	}



	outputs = pManager->get_connected_leds(num_of_outputs);

	//number of rows = 2^n where n is the num of inputs
	no_rows = pow(2, num_of_inputs);


	truth_table = new int* [no_rows];
	for (int i = 0; i < no_rows; ++i)
	{

		truth_table[i] = new int[num_of_inputs + num_of_outputs];

	}


}



void CreateTruthTable::ReadActionParameters()
{
}


void CreateTruthTable::increase_current_combination()
{
	int n = ++current_comb_;

	//then convert that number to binary and save it in 
	int i = 0;
	if (n <= no_rows - 1) {
		while (n > 0)
		{
			binary_current_comb_[i++] = n % 2;
			n /= 2;

		}
	}
	

}



void CreateTruthTable::Execute()
{

	for (int i = 0; i < no_rows; ++i)
	{
		//first put the inputs into the switches
		for (int j = 0; j < num_of_inputs; ++j)
		{
			//put it in the Truth Table
			truth_table[i][j] = binary_current_comb_[j];

			//then set the Status of all inputs to it
			STATUS s = binary_current_comb_[j] ? HIGH : LOW;
			inputs[j]->set_state(s);

		}


		pManager->ExecuteAction(SIMULATE);

		//now get the output
		for (int j = 0; j < num_of_outputs; ++j)
		{
			truth_table[i][j + num_of_inputs] = int(outputs[j]->get_is_High());
			outputs[j]->set_is_reached(false);
		}


		//now increase the combination
		if (i != no_rows - 1)
			increase_current_combination();

	}


	//TODO: to be deleted
	cout << "input:---------------:output:" << endl;
	for (int i = 0; i < no_rows; ++i)
	{
		for (int j = 0; j < num_of_outputs + num_of_inputs; ++j)
		{
			cout << truth_table[i][j] << "\t";
		}
		cout << endl;
	}





	//after finishing ,just set all switches to LOW
	for (int j = 0; j < num_of_inputs; ++j)
	{

		inputs[j]->set_state(HIGH);

	}


}




void CreateTruthTable::Undo()
{}

void CreateTruthTable::Redo()
{}


CreateTruthTable::~CreateTruthTable(void)
{
	delete[] binary_current_comb_;
	for (int i = 0; i < no_rows; ++i)
	{
		delete[] truth_table[i];
	}

	delete[] truth_table;

}
