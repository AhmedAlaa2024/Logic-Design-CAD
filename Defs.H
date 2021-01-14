#ifndef CONST_H
#define CONST_H

//This header file contains some defenitions to be used all over the application

//All possible actions
enum ActionType 
{
	ADD_Gate,
	ADD_AND_GATE_2,		//Add 2-input AND gate
	ADD_OR_GATE_2,		//Add 2-input OR gate
	ADD_Buff,			//Add 1-input Buffer gate
	ADD_INV,			//Add 1-input Inverter gate
	ADD_NAND_GATE_2,	//Add 2-input NAND gate
	ADD_NOR_GATE_2,		//Add 2-input NOR gate
	ADD_XOR_GATE_2,		//Add 2-input XOR gate
	ADD_XNOR_GATE_2,	//Add 2-input XNOR gate
	ADD_AND_GATE_3,		//Add 3-input AND gate
	ADD_OR_GATE_3,		//Add 3-input NOR gate
	ADD_NAND_GATE_3,		//Add 3-input AND gate
	ADD_NOR_GATE_3,		//Add 3-input NOR gate
	ADD_XOR_GATE_3,		//Add 3-input XOR gate
	ADD_XNOR_GATE_3,		//Add 3-input XOR gate
	ADD_Switch,			//Add Switch
	ADD_LED,			//Add LED
	ADD_CONNECTION,		//Add Wire Connection

	ADD_Label,			//Add Label to a Component, a Connection
	EDIT_Label,			//Edit Label of a Component, a Connection

	Organize,
	Clear_all,
	Create_TruthTable,	//Create Truth Table of the Circuit

	Change_Switch,		//Change Switch Status in Simulation Mode

	SELECT,		//Select a Component, a Connection
	DEL,		//Delete a Component, a Connection
	MOVE,		//Move a Component, a Connection

	SAVE,		//Save the whole Circuit to a file
	LOAD,		//Load a Circuit from a file

	UNDO,		//Undo the last Action preformed
	REDO,		//Redo the last Action canceled

	DSN_MODE,	//Switch to Design mode
	SIM_MODE,	//Switch to Simulatiom mode
	SIMULATE,
	PROGING,
	EXIT,		//Exit the application
	COPY_,
	CUT_,
	PASTE_,
	STATUS_BAR,		//A click on the status bar
	DSN_TOOL,	//A click on an empty place in the design tool bar
	SIM_TOOL, 	//A click on an empty place in the simulation tool bar
	GATE_TOOL   //A click on an empty place in the gates bar
};

enum CopyCutPaste_mode
{
	COPY,
	CUT,
	PASTE

};



//Possible Status for the pin
enum STATUS
{
	LOW,
	HIGH
};

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};


enum DsgnMenuItem //The items of the design menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ADD_GATE,
	SIM_ICON,
	ADD_LABEL,
	EDIT_LABEL,
	WIRE,
	ORGANIZE_SCREEN,
	CLEAR,
	LOAD_ICON,
	SAVE_ICON,

	ITM_EXIT,		//Exit item
	//TODO: Add more items names here
	ITM_DSN_CNT,		//no. of design menu items ==> This should be the last line in this enum
};
enum { MaxCompCount = 200 };	//Max no of Components	
enum DesignTools {
	AND_2IN,
	OR_2IN,
	BUF,
	NOT,
	NAND_2IN,
	NOR_2IN,
	XOR_2IN,
	XNOR_2IN,
	AND_3IN,
	NOR_3IN,
	XOR_3IN,
	LED1,
	SWITCH1,
	GATES_CNT
};
	// ============================== Ahmed Alaa edited here ==============================
enum DsgnMenuItem2 {
	ITM_UNDO,
	ITM_REDO,
	COPY_ICON,
	CUT_ICON,
	PASTE_ICON,
	DELETE_ICON,
	ITM_DSN2_CNT	//no. of design menu items ==> This should be the last line in this enum
};
	// ==================================== Ahmed Alaa ====================================
enum SimMenuItem //The items of the simulation menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	ITM_DSN,	//Simulate menu item
	ITM_PRODING,
	// ITM_TRUTH,	//Truth table menu item
	// Add_Label,
	// Edit_label,
	ITM_CHANGE_SWITCH,
	ITM_LOAD,
	ITM_SAVE,
	SIM_EXIT,
	//TODO:Add more items names here

	ITM_SIM_CNT		//no. of simulation menu items ==> This should be the last line in this enum

};

//Maximum number of input pins that can be connected to any output pin
#define MAX_CONNS 20

//assume fan out is 5 for now it can be read from the user or can be predefined as const
enum FANOUT
{
	FANOUT = 10,	//Default fan out of 2-input AND gate
	
	SWITCH_FANOUT = 10,
	LED_FANOUT = 0
};

enum class COMP_TYPES
{
	COMP_GENERAL,
	COMP_GATE,
	COMP_SWITCH,
	COMP_LED,
	COMP_CONN,
	AND_2,
	AND_3,
	INV_,
	NAND_2,
	NOR_2,
	NOR_3,
	Buff_,
	OR_2,
	XNOR_2,
	XOR_2,
	XOR_3,
	LABEL
};

//A structure to contain drawing parameters for each component
//Each component occupies a rectangluar area so it needs 2 points to represent that area
//this structure can be extended if desired
struct GraphicsInfo
{
	int x1,y1, x2, y2;
};

#ifndef NULL
#define NULL 0
#endif

#endif
