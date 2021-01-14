#include "CreateTruthTable.h"
#include "..\ApplicationManager.h"

#include <iostream>
using namespace std;

CreateTruthTable::CreateTruthTable(ApplicationManager* pApp) :Action(pApp)
{
	fout = NULL;
	pWind = NULL;
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
	no_cols = num_of_inputs + num_of_outputs;
	WinWidth = 50 + (no_cols + 1) * UI.TableIconWidth + (no_cols + 2);
	WinHeight = 50 + (no_rows + 1) * UI.TableIconHeight + (no_rows + 2);

	truth_table = new int* [no_rows];
	for (int i = 0; i < no_rows; ++i)
	{

		truth_table[i] = new int[no_cols];

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

	///displaying the table
	if (num_of_inputs > 5)
		SaveTable();
	else
	{
		OpenWindow();
		PrintTableBorders();
		PrintTable();
	}

	//after finishing ,just set all switches to LOW
	for (int j = 0; j < num_of_inputs; ++j)
	{

		inputs[j]->set_state(HIGH);

	}

	

	pWind->WaitMouseClick(x, y);
}

void CreateTruthTable::OpenWindow()
{
	pWind = new window(WinWidth, WinHeight, 300, 200);
	pWind->ChangeTitle("Truth table");
}

void CreateTruthTable::PrintTableBorders()
{
	///for horizontal lines.
	pWind->SetPen(BLUE, 1);
	for (int i = 0; i <= no_rows + 1; i++)
		pWind->DrawLine(20, 20 + UI.TableIconHeight * i, 20 + (no_cols + 1) * UI.TableIconWidth, 20 + UI.TableIconHeight * i);
	///for vertical lines.
	for (int i = 0; i <= no_cols + 1; i++)
		pWind->DrawLine(20 + UI.TableIconWidth * i, 20, 20 + UI.TableIconWidth * i, 20 + (no_rows + 1) * UI.TableIconHeight);
}

void CreateTruthTable::PrintTable()
{
	int firstx = 20 + UI.TableIconWidth * 0.5;
	int firsty = 20 + UI.TableIconHeight * 0.5;
	for (int i = 0; i < no_rows; i++)
	{
		for (int j = 0; j < no_cols; j++)
		{
			pWind->DrawString(firstx + UI.TableIconWidth * j, firsty + UI.TableIconHeight * i,to_string(truth_table[i][j]));
		}
	}
}

void CreateTruthTable::SaveTable()
{
	fout = new ofstream("TruthTable.txt");
	if (fout->is_open())
	{
		for (int i = 0; i < no_rows; i++)
		{
			for (int j = 0; j < no_cols; j++)
			{
				*fout << truth_table[i][j] << '\t';
			}
			*fout << endl;
		}
		fout->close();
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
	if (fout)
		delete fout;
	delete pWind;
}
