#ifndef CreateTruthTable_H
#define CreateTruthTable_H

#include "Action.h"
#include "../Components/LED.h"
#include "../Components/SWITCH.h"

class CreateTruthTable : public Action
{
private:
	int current_comb_; // the combination //in dec and will be converted to binary
	int* binary_current_comb_;
	void increase_current_combination();

	window* pWind;
	int WinHeight;
	int WinWidth;
	
	int num_of_inputs;
	SWITCH** inputs;
	int num_of_outputs;
	LED** outputs;

	int no_rows;
	int no_cols;
	int** truth_table;
	int x;
	int y;

	ofstream* fout;
	
public:
	CreateTruthTable(ApplicationManager* pApp);
	virtual ~CreateTruthTable(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	void OpenWindow();

	void PrintTableBorders();

	void PrintTable();

	void SaveTable();
	
	virtual void Undo();
	virtual void Redo();
};

#endif