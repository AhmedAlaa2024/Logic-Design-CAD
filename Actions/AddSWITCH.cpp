#include "AddSWITCH.h"
#include "..\ApplicationManager.h"

AddSWITCH::AddSWITCH(ApplicationManager* pApp) :Action(pApp)
{
}

AddSWITCH::~AddSWITCH(void)
{
}

void AddSWITCH::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("SWITCH: Click to add the SWITCH");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddSWITCH::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	//Calculate the rectangle Corners
	int Len = UI.Gate_Height;
	int Wdth = UI.Gate_Width;

	GraphicsInfo GInfo; //Gfx info to be used to construct the SWITCH

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
    SWITCH* pA = new SWITCH(GInfo, SWITCH_FANOUT);
	pManager->AddComponent(pA);
	id++;
}
int AddSWITCH::getId()
{
	return id;
}

void AddSWITCH::Undo()
{}

void AddSWITCH::Redo()
{}

