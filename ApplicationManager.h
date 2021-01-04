

#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include <fstream>

#include "Defs.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include "Actions\Action.h"
#include "Components\Component.h"
#include "Actions/AddANDgate2.h"
#include "Actions/AddANDgate2.h"
#include "Actions/Select.h"
#include "Actions/SwitchToDesign.h"
#include "Actions/SwitchToSimulation.h"
#include "Actions/Add.h"
#include "Actions/Label.h"
#include "Actions/Connect.h"


#include "Actions/Exit.h"
#include "Actions/Save.h"
#include "Actions/Load.h"

//Main class that manages everything in the application.
class ApplicationManager
{
private:
	int CompCount;		//Actual number of Components
	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)
	// ============================== Ahmed Alaa edited here ==============================
	Component* lastSelectedComponent; // Pointer to the last component has been selected
	// ==================================== Ahmed Alaa ====================================
	// 
	Output* OutputInterface; //pointer to the Output Clase Interface
	Input* InputInterface; //pointer to the Input Class Interface

	COMP_TYPES Clipboard;

public:
	ApplicationManager(); //constructor

	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();
	ActionType AddGate();

	//Creates an action and executes it
	void ExecuteAction(ActionType);

	void UpdateInterface();	//Redraws all the drawing window

	void set_clipboard();
	// ============================== Ahmed ATA edited here ==============================
	COMP_TYPES get_clipboard() const;

	
	//Gets a pointer to Input / Output Object
	Output* GetOutput();
	Input* GetInput();

	// ============================== Ahmed Alaa edited here ==============================
	void SetLastSelectedComponent(Component*); // Set the last component has been selected
	Component* GetLastSelectedComponent(); // Get the last component has been selected
	// ==================================== Ahmed Alaa ====================================

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);
	Component* const* getComponents(int &count) const; //don't ask me about the type :(
	void save(ofstream*&);
													   //destructor
	~ApplicationManager();

	//===========================DOAA MAGDY============================
	int getCompCount();
};

#endif