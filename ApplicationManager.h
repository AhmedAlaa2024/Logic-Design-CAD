

#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include "Actions\Action.h"
#include "Components\Component.h"
#include "Actions/AddANDgate2.h"
#include "Actions/AddANDgate2.h"
#include "Actions/SwitchToDesign.h"
#include "Actions/SwitchToSimulation.h"

#include "Actions/Exit.h"

//Main class that manages everything in the application.
class ApplicationManager
{



private:
	int CompCount;		//Actual number of Components
	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)

	Output* OutputInterface; //pointer to the Output Clase Interface
	Input* InputInterface; //pointer to the Input Class Interface



public:
	ApplicationManager(); //constructor

	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();

	//Creates an action and executes it
	void ExecuteAction(ActionType);

	void UpdateInterface();	//Redraws all the drawing window

	//Gets a pointer to Input / Output Object
	Output* GetOutput();
	Input* GetInput();

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);
	Component* const* getComponents(int &count) const; //don't ask me about the type :(
	//destructor
	~ApplicationManager();
};

#endif