#include "AddBUFFER.h"
#include "..\ApplicationManager.h"

AddBUFFER::AddBUFFER(ApplicationManager* pApp) :Action(pApp), Cx(0), Cy(0)
{
}

AddBUFFER::~AddBUFFER(void)
{
}

void AddBUFFER::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Buffer Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddBUFFER::Execute()
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

	GraphicsInfo GInfo; //Gfx info to be used to construct the Buffer gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	Buff* pA = new Buff(GInfo, FANOUT);
	pManager->AddComponent(pA);
}

void AddBUFFER::Undo()
{}

void AddBUFFER::Redo()
{}

