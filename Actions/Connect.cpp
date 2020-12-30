#include "Connect.h"
#include "..\ApplicationManager.h"
#include "..\Components\LED.h"
#include "..\Components\SWITCH.h"

Connect::Connect(ApplicationManager* pApp, Component**c, int n):Action(pApp)
{
	cmp = c;
	noOfComp = n;
}


void Connect::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("connect two gates: Click on the gate of the source(output) pin");

	//Wait for User Input
	pIn->GetPointClicked(Cx1, Cy1);

	//Clear Status Bar
	pOut->ClearStatusBar();

	//Print Action Message
	pOut->PrintMsg("connect two gates: Click on the gate of the destination(input) pin");

	//Wait for User Input
	pIn->GetPointClicked(Cx2, Cy2);


	//Clear Status Bar
	pOut->ClearStatusBar();


}


void Connect::Execute()
{
	//Get the two Gates wanted to be connected 
	ReadActionParameters();

	const OutputPin* out;

	int i;
	for (i = 0; i < noOfComp; i++)
	{
		bool d = cmp[i]->InsideArea(Cx1, Cy1);
		//LED* L = dynamic_cast<LED*>(cmp[i]);

		if (d == true)
		{
			LED* L = dynamic_cast<LED*>(cmp[i]);
			if (L != NULL)
			{
				Output* pOut = pManager->GetOutput();
				pOut->PrintMsg("the led has no outputpin, please chose another component");
				return;

			}
			out = cmp[i]->getOutputPin();
			break;
		}
	}

	 InputPin** in;
	 InputPin* input;

	 int k;
	for (k = 0; k < noOfComp; k++)
	{
		bool d = cmp[k]->InsideArea(Cx2, Cy2);
		if (d == true)
		{
			SWITCH* sw = dynamic_cast<SWITCH*>(cmp[k]);
			if (sw != NULL)
			{
				Output* pOut = pManager->GetOutput();
				pOut->PrintMsg("the switch has no inputpin, please chose another component");
				return;
			}

			in[i] = cmp[k]->getInputPin();
			int no_inputpins = cmp[k]->getNoOfInputpins();
			for(int j = 0; j < no_inputpins; j++)
			{
				bool isConnected = in[j]->get_is_connected();
				if (isConnected == false)
				{
					input = in[j];
					in[j]->set_is_connected(true);
					break;
				}
			}

			break;
		}
	}

	//if()


	GraphicsInfo GInfo; //Gfx info to be used to construct the connection

	cmp[i]->getm_GfxInfo(x1, y1, x2, y2);



	GInfo.x1 = x2;
	//GInfo.x2 = ;
	GInfo.y1 = y1 + (y2-y1)/2;
	//GInfo.y2 = ;
	
	//Connection* pA = new Connection(GInfo, out, input );
	//pManager->AddComponent(pA);

}

Connect::~Connect(void)
{

}


void Connect::Undo()
{

}

void Connect::Redo()
{

}