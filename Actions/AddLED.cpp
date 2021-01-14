#include "AddLED.h"
#include "..\ApplicationManager.h"

AddLED::AddLED(ApplicationManager* pApp) :Action(pApp), Cx(0), Cy(0)
{
}

AddLED::~AddLED(void)
{
}

void AddLED::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("LED: Click to add the LED");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddLED::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	Output* pOut = pManager->GetOutput();

	//check validation of the Drawing Area
	bool is_valid = Action::if_valid_Area_led(Cx, Cy);
	if (!is_valid)
	{
		pOut->PrintMsg("Error: Invalid Area");
		return;
	}

	//Calculate the rectangle Corners
	int Len = UI.Gate_Height;
	int Wdth = UI.Gate_Width;

	GraphicsInfo GInfo; //Gfx info to be used to construct the LED

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	LED* pA = new LED(GInfo, LED_FANOUT);
	pManager->AddComponent(pA);
}

void AddLED::Undo()
{}

void AddLED::Redo()
{}

