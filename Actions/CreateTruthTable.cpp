#include "CreateTruthTable.h"
#include "..\ApplicationManager.h"
#include <string>
#include <iostream>
using namespace std;

CreateTruthTable::CreateTruthTable(ApplicationManager* pApp) :Action(pApp)
{
	fout = NULL;
	pWind = NULL;
	current_comb_ = 0;
	exitWid = 50;
	exitHei = 22;
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
	WinWidth = 20 + (no_cols + 1) * UI.TableIconWidth + exitWid + 20;
	WinHeight = 40 + (no_rows + 1) * UI.TableIconHeight;

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
	else if (!no_cols)
		pManager->GetOutput()->PrintMsg("Truth table is empty!");
	else
	{
		DisplayTable();
		ExitWin();
	}
	//after finishing ,just set all switches to LOW
	for (int j = 0; j < num_of_inputs; ++j)
	{

		inputs[j]->set_state(HIGH);

	}
}

void CreateTruthTable::OpenWindow()
{
	pWind = new window(WinWidth, WinHeight, 0, -5);

	pWind->DrawRectangle(0, 0, WinWidth, WinHeight);
	pWind->ChangeTitle("Truth table");
}

void CreateTruthTable::PrintTableBorders()
{
	
	///for horizontal lines.
	pWind->SetPen(BLACK, 1);
	for (int i = 0; i <= no_rows + 1; i++)
		pWind->DrawLine(10, 10 + UI.TableIconHeight * i, 10 + (no_cols) * UI.TableIconWidth, 10 + UI.TableIconHeight * i);
	///for vertical lines.
	for (int i = 0; i <= no_cols; i++)
		pWind->DrawLine(10 + UI.TableIconWidth * i, 10, 10 + UI.TableIconWidth * i, 10 + (no_rows + 1) * UI.TableIconHeight);
	pWind->DrawLine(WinWidth - exitWid - 20, 8, WinWidth - 20, 8);
	pWind->DrawLine(WinWidth - exitWid - 20, 8 + exitHei, WinWidth - 20, 8 + exitHei);
	pWind->DrawLine(WinWidth - exitWid - 20, 8, WinWidth - exitWid - 20, 8 + exitHei);
	pWind->DrawLine(WinWidth - 20, 8, WinWidth - 20, 8 + exitHei);

	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(WinWidth - exitWid - 18, 10, "Exit");
}

void CreateTruthTable::PrintTable()
{
	pWind->SetFont(15, BOLD, BY_NAME, "Arial");
	pWind->SetPen(DARKGOLDENROD);
	int firstx = 10 + UI.TableIconWidth * 0.25;
	int firsty = 10 + UI.TableIconHeight * 0.25;
	string name = "";

	for (int i = 0; i < num_of_inputs; i++)
	{
		if (inputs[i]->get_m_Label() != "")
		{
			if (inputs[i]->get_m_Label().length() > 5)
				pWind->DrawString(firstx + UI.TableIconWidth * i, firsty, (inputs[i]->get_m_Label()).substr(0, 5) + ".");
			else
				pWind->DrawString(firstx + UI.TableIconWidth * i, firsty, inputs[i]->get_m_Label());
		}
		else
		{
			name = "In: " + to_string(i + 1);
			
			pWind->DrawString(firstx + UI.TableIconWidth * i, firsty, name);
		}
	}
	for (int i = num_of_inputs; i < no_cols; i++)
	{
		if (outputs[i - num_of_inputs]->get_m_Label() != "")
		{
			if (outputs[i - num_of_inputs]->get_m_Label().length() > 5)
				pWind->DrawString(firstx + UI.TableIconWidth * i, firsty, outputs[i - num_of_inputs]->get_m_Label().substr(0, 5) + ".");
			else
				pWind->DrawString(firstx + UI.TableIconWidth * i, firsty, outputs[i - num_of_inputs]->get_m_Label());
		}
		else
		{
			name = "Out: " + to_string(i - num_of_inputs + 1);
			pWind->DrawString(firstx + UI.TableIconWidth * i, firsty, name);
		}
	}

	firstx = 10 + UI.TableIconWidth * 0.25;
	firsty = 10 + UI.TableIconHeight * 1.25;
	for (int i = 0; i < no_rows; i++)
	{
		for (int j = 0; j < no_cols; j++)
		{
			pWind->DrawString(firstx + UI.TableIconWidth * j, firsty + UI.TableIconHeight * i,to_string(truth_table[i][j]));
		}
	}
}

void CreateTruthTable::ExitWin()
{
	do
	{
		pWind->WaitMouseClick(x, y);
	} while (!(x >= WinWidth - exitWid - 20 && x <= WinWidth - 20 && y <= 8 + exitHei && y >= 8));
	pWind->SetWaitClose(false);
	delete pWind;
	pWind = 0;
}

void CreateTruthTable::SaveTable()
{
	fout = new ofstream("TruthTable.txt");
	if (fout->is_open())
	{
		for (int i = 0; i < num_of_inputs; i++)
		{
			if (inputs[i]->get_m_Label() != "")
			{
				if (inputs[i]->get_m_Label().length() > 5)
					*fout << ((inputs[i]->get_m_Label()).substr(0, 5) + ".") << '\t';
				else
					*fout << ((inputs[i]->get_m_Label())) << '\t';
			}
			else
				*fout << "In: " << (i + 1) << '\t';
		}
		for (int i = num_of_inputs; i < no_cols; i++)
		{
			if (outputs[i - num_of_inputs]->get_m_Label() != "")
			{
				if (outputs[i - num_of_inputs]->get_m_Label().length() > 5)
					*fout << ((outputs[i - num_of_inputs]->get_m_Label()).substr(0, 5) + ".") << '\t';
				else

					*fout << ((outputs[i - num_of_inputs]->get_m_Label())) << '\t';
			}
			else
				*fout << "In: " << (i - num_of_inputs + 1) << '\t';
		}
		*fout << endl;
		for (int i = 0; i < no_rows; i++)
		{
			for (int j = 0; j < no_cols; j++)
			{
				*fout << truth_table[i][j] << '\t';
			}
			*fout << endl;
		}
		fout->close();
		if (!(fout->is_open()))
			pManager->GetOutput()->PrintMsg("Table saved in \"TruthTable.txt\"");
	}

}

void CreateTruthTable::DisplayTable()
{
	OpenWindow();
	PrintTableBorders();
	PrintTable();
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
}
