#include "AddANDgate2.h"
#include "..\ApplicationManager.h"

AddANDgate2::AddANDgate2(ApplicationManager *pApp):Action(pApp), Cx(0), Cy(0)
{
}

AddANDgate2::~AddANDgate2(void)
{
}

void AddANDgate2::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Input AND Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();
	
}

void AddANDgate2::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	Output* pOut = pManager->GetOutput();

	//check validation of the Drawing Area
	bool is_valid = Action::if_valid_Area(Cx, Cy);
	if (!is_valid)
	{
		pOut->PrintMsg("Error: Invalid Area");
		return;
	}
	
	//Calculate the rectangle Corners
	int Len = UI.Gate_Height;
	int Wdth = UI.Gate_Width;
	
	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
	
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	AND2 *pA=new AND2(GInfo, FANOUT);
	pManager->AddComponent(pA);
}

void AddANDgate2::Undo()
{}

void AddANDgate2::Redo()
{}

