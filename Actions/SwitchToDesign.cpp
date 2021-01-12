#include "SwitchToDesign.h"
#include "..\ApplicationManager.h"

SwitchToDesign::SwitchToDesign(ApplicationManager* pApp) :Action(pApp)
{
}

SwitchToDesign::~SwitchToDesign()
{
}


void SwitchToDesign::Execute()
{

	Output* pOut = pManager->GetOutput();
	pManager->DeselectComponentExcept();
	pOut->ClearWindow();
	pOut->CreateDesignToolBar();
	
}

void SwitchToDesign::ReadActionParameters()
{

}

void SwitchToDesign::Undo()
{}

void SwitchToDesign::Redo()
{}

