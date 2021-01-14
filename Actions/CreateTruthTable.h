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

	
	int num_of_inputs;
	SWITCH** inputs;
	int num_of_outputs;
	LED** outputs;

	int no_rows;
	int** truth_table;
	
public:
	CreateTruthTable(ApplicationManager* pApp);
	virtual ~CreateTruthTable(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();




	
	virtual void Undo();
	virtual void Redo();
};

#endif