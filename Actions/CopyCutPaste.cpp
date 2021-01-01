#include "CopyCutPaste.h"
#include "..\ApplicationManager.h"

CopyCutPaste::CopyCutPaste(ApplicationManager* pApp, int mode) :Action(pApp), MODE(mode)
{
}

CopyCutPaste::~CopyCutPaste(void)
{
}

void CopyCutPaste::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();


	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void CopyCutPaste::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	//Calculate the rectangle Corners
	int Len = UI.Gate_Height;
	int Wdth = UI.Gate_Width;

	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate

	AND2* pA = new AND2(GInfo, FANOUT);
	pManager->AddComponent(pA);
	
}

void CopyCutPaste::cut()
{
}

void CopyCutPaste::copy()
{
}

void CopyCutPaste::paste()
{
}


void CopyCutPaste::Undo()
{}

void CopyCutPaste::Redo()
{}

