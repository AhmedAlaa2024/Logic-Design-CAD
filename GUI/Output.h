#pragma once
#include "..\Defs.h"
#include "Input.h"
#include "..\\Components\\Component.h"

class Output	//The application manager should have a pointer to this class
{
private:
	window* pWind;	//Pointer to the Graphics Window
public:
	Output(); // Performs the Window Initialization
	Input* CreateInput() const; //creates a pointer to the Input object
	void ChangeTitle(string Title) const;

	void CreateDesignToolBar() const;
	void CreateDesignToolBarComponent() const;
	//Tool bar of the design mode
	void CreateSimulationToolBar() const;//Tool bar of the simulation mode
	void CreateStatusBar() const;	//Create Status bar

	void ClearStatusBar() const;		//Clears the status bar
	void ClearDrawingArea() const;	//Clears the drawing area
	void ClearWindow() const;

	window* CreateWind(int wd, int h, int x, int y) const; //Creates user interface window
	void destroyWind() const;

	// ============================== Ahmed Alaa edited here ==============================
	void DrawTextbox(string, Component*); // To draw a textbox
	void ClearComponentArea(GraphicsInfo);
	void Clear_Connection_DrawingArea(GraphicsInfo r_GfxInfo) const;
	// To draw a white rectangle above the deleted component
	void ClearLabelArea(GraphicsInfo, int = 0); // To draw a white rectangle above the deleted component's label
	// ==================================== Ahmed Alaa ====================================

	// Draws 2-input AND gate

	///TODO: Make similar functions for drawing all other gates, switch, and LED, .. etc
	void DrawBuff(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawINV(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawAND2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawNAND2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawNOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawXOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawAND3(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawNOR3(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawOR3(GraphicsInfo r_GfxInfo, bool selected) const;
	void DrawXOR3(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawLED(GraphicsInfo r_GfxInfo, bool is_high = false, bool selected = false) const;
	void DrawSWITCH(GraphicsInfo r_GfxInfo, bool is_on = false, bool selected = false) const;



	MODE getAppMode();



	// Draws Connection
	void DrawConnection(GraphicsInfo r_GfxInfo, bool selected = false, bool is_high = false) const;

	void PrintMsg(string msg) const;	//Print a message on Status bar


	~Output();
};
