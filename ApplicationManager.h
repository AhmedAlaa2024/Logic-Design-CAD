
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
#include "Actions/Edit.h"
#include "Actions/Delete.h"
#include "Actions/Clear.h"
#include "Actions/Connect.h"
#include "Actions/Exit.h"
#include "Actions/Save.h"
#include "Actions/Load.h"
#include "Components/LED.h"
#include "Components/SWITCH.h"

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
	Output* OutputInterface; //pointer to the Output Class Interface
	Input* InputInterface; //pointer to the Input Class Interface
	
	ActionType Clipboard;

	void shift_to_end(int i); //utility function

	
public:
	ApplicationManager(); //constructor

	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();
	ActionType AddGate();
	//Creates an action and executes it
	void ExecuteAction(ActionType);
	void Execute_Add_Gate_action(ActionType a);

	void UpdateInterface();	//Redraws all the drawing window

	bool set_clipboard();
	// ============================== Ahmed ATA edited here ==============================
	ActionType get_clipboard() const;


	//to start and end the simulation
	SWITCH** get_switches(int& num) const;
	LED** get_connected_leds(int &num )const;

	//Gets a pointer to Input / Output Object
	Output* GetOutput();
	Input* GetInput();

	// ============================== Ahmed Alaa edited here ==============================
	void SetLastSelectedComponent(int = -1); // Set the last component has been selected
	Component* GetLastSelectedComponent(); // Get the last component has been selected
	int which_component(COMP_TYPES&); // return the ID of the component
	void DeselectComponentExcept(int = -1); // If the user clicked on blank space, all components should be deselected.
	void SelectComponent(int = -1); // To set is_selected for the target = true
	void DeleteComponent(); // To delete the last component has been selected
	void DeleteAll(); // To delete all the component
	// ==================================== Ahmed Alaa ====================================

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);

	Component* get_comp_at(int index) const;
	Component** get_CompList(int &n);


	bool validate_circuit() const;

	
	int save(ofstream*&);
	void load(ifstream*&);
			
										   
	//destructor
	~ApplicationManager();

	
	
};

#endif