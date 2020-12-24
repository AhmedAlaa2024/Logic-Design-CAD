#include "AddANDgate3.h"
#include "..\ApplicationManager.h"

AddANDgate3::AddANDgate3(ApplicationManager* pApp) :Action(pApp)
{
}

AddANDgate3::~AddANDgate3(void)
{
}

void AddANDgate3::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("3-Input AND Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddANDgate3::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	//Calculate the rectangle Corners
	int Len = UI.Gate_Height;
	int Wdth = UI.Gate_Width;

	GraphicsInfo GInfo; //Gfx info to be used to construct the AND3 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	AND3* pA = new AND3(GInfo, AND3_FANOUT);
	pManager->AddComponent(pA);
}

void AddANDgate3::Undo()
{}

void AddANDgate3::Redo()
{}

