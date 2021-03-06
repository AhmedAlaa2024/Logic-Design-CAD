#include "Output.h"
#include <iostream>
using namespace std;

Output::Output()
{
	//Initialize user interface parameters

	UI.AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	UI.DrawColor = BLACK;
	UI.SelectColor = BLUE;
	UI.ConnColor =BLUE ;
	UI.on_ConnColor = GREEN;
	UI.selected_connColor = RED;

	UI.MsgColor = BLUE;
	UI.BkGrndColor = WHITE;

	//Create the drawing window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	ChangeTitle("Programming Techniques Project");

	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar

}

Input* Output::CreateInput() const
{
	//Create an Input Object & assign it to the Same Window
	Input* pIn = new Input(pWind);
	return pIn;
}


//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y) const
{
	return new window(wd, h, x, y);
}
void Output::destroyWind() const
{
	delete pWind;

}
//////////////////////////////////////////////////////////////////////////////////
void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.height - UI.StatusBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	// Print the Message
	pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(UI.MsgColor);
	pWind->DrawString(MsgX, UI.height - MsgY, msg);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(MsgX, UI.height - MsgY, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void Output::ClearDrawingArea() const
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width - UI.ToolBarHeight - 18, UI.height - UI.StatusBarHeight);

}



void Output::ClearWindow() const
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	if (UI.AppMode == SIMULATION)
		pWind->DrawRectangle(0, 0, UI.width, UI.height);
	else
		pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width - UI.ToolBarHeight - 18, UI.height - UI.StatusBarHeight);


}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
	UI.AppMode = DESIGN;	//Design Mode

	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];

	MenuItemImages[ADD_GATE] = "images\\DesignMenu\\add.jpg";
	MenuItemImages[SIM_ICON] = "images\\DesignMenu\\start.jpg";
	MenuItemImages[ADD_LABEL] = "images\\DesignMenu\\text.jpg";
	MenuItemImages[EDIT_LABEL] = "images\\DesignMenu\\edit.jpg";
	MenuItemImages[WIRE] = "images\\DesignMenu\\wire.jpg";
	MenuItemImages[CLEAR] = "images\\DesignMenu\\clear.jpg";
	MenuItemImages[LOAD_ICON] = "images\\DesignMenu\\load.jpg";
	MenuItemImages[SAVE_ICON] = "images\\DesignMenu\\save.jpg";
	MenuItemImages[ITM_EXIT] = "images\\DesignMenu\\exit.jpg";

	

	//Draw menu item one image at a time
	for (int i = 0; i < ITM_DSN_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

	string CopyCutPasteDeleteMenu[ITM_DSN2_CNT];
	CopyCutPasteDeleteMenu[ITM_UNDO] = "images\\Menu\\undo.jpg";
	CopyCutPasteDeleteMenu[ITM_REDO] = "images\\Menu\\redo.jpg";
	CopyCutPasteDeleteMenu[COPY_ICON] = "images\\Menu\\copy.jpg";
	CopyCutPasteDeleteMenu[CUT_ICON] = "images\\Menu\\cut.jpg";
	CopyCutPasteDeleteMenu[PASTE_ICON] = "images\\Menu\\paste.jpg";
	CopyCutPasteDeleteMenu[DELETE_ICON] = "images\\Menu\\delete.jpeg";

	for (int i = 0; i < ITM_DSN2_CNT; i++)
		pWind->DrawImage(CopyCutPasteDeleteMenu[i], UI.width - UI.ToolBarHeight - 15, (i + 1) * (UI.ToolItemWidth) + 5, UI.ToolBarHeight, UI.ToolItemWidth);

	pWind->SetPen(RED, 3);
	pWind->DrawLine(UI.width - UI.ToolBarHeight - 18, UI.ToolItemWidth + 5, UI.width - UI.ToolBarHeight - 18, UI.height - UI.StatusBarHeight);

}
void Output::CreateDesignToolBarComponent() const
{

	string DesignTools[GATES_CNT];
	DesignTools[AND_2IN] = "images\\Gates\\Gate_AND2.jpg";
	DesignTools[OR_2IN] = "images\\Gates\\Gate_OR2n.jpg";
	DesignTools[BUF] = "images\\Gates\\Buffer_n.jpg";
	DesignTools[NOT] = "images\\Gates\\Gate_INV.jpg";
	DesignTools[NAND_2IN] = "images\\Gates\\Gate_NAND2.jpg";
	DesignTools[NOR_2IN] = "images\\Gates\\Gate_NOR2.jpg";
	DesignTools[XOR_2IN] = "images\\Gates\\Gate_XOR.jpg";
	DesignTools[XNOR_2IN] = "images\\Gates\\Gate_XNOR2.jpg";
	DesignTools[AND_3IN] = "images\\Gates\\Gate_AND3.jpg";
	DesignTools[NOR_3IN] = "images\\Gates\\Gate_NOR3.jpg";
	DesignTools[XOR_3IN] = "images\\Gates\\Gate_XOR3.jpg";
	DesignTools[LED1] = "images\\Gates\\LED.jpg";
	DesignTools[SWITCH1] = "images\\Gates\\off_switch.jpg";

	for (int i = 0; i < GATES_CNT; i++)
		pWind->DrawImage(DesignTools[i], i * UI.Gate_Width, 650, UI.Gate_Width, UI.Gate_Height);


	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, 650, UI.width, 650);
}




//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void Output::CreateSimulationToolBar() const
{
	UI.AppMode = SIMULATION;	//Simulation Mode

	//TODO: Write code to draw the simualtion toolbar (similar to that of design toolbar drawing)
	string MenuItemImages[ITM_SIM_CNT];

	MenuItemImages[ITM_DSN] = "images\\SimulationMenu\\design.jpg";
	MenuItemImages[ITM_TRUTH] = "images\\SimulationMenu\\table.jpg";
	MenuItemImages[ITM_PRODING] = "images\\SimulationMenu\\prode.jpeg";
	MenuItemImages[SIM_EXIT] = "images\\SimulationMenu\\exit.jpg";


	for (int i = 0; i < ITM_SIM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);

	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

//------Ahmed Ata edited-----//

void Output::DrawBuff(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_Buff_Hi.jpeg";
	else
		GateImage = "Images\\Gates\\Gate_Buff.jpeg";

	//Draw Buff Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by Buff Image Parameter in UI_Info
	//
	//TODO: I need to change those heights and widths
	//
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
}

void Output::DrawINV(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_INV_Hi.jpeg";
	else
		GateImage = "Images\\Gates\\Gate_INV.jpg";

	//Draw INV Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by INV Image Parameter in UI_Info
	//
	//TODO: I need to change those heights and widths
	//
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
}

void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_AND2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_AND2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
}

void Output::DrawOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_OR2_Hi.jpeg";
	else
		GateImage = "Images\\Gates\\Gate_OR2.jpeg";

	
	
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
}
void Output::DrawOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_OR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_OR3.jpg";

	
	
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
}
void Output::DrawNAND2(GraphicsInfo r_GfxInfo, bool selected) const //done
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NAND2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NAND2.jpg";

	
	
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
}

void Output::DrawNOR2(GraphicsInfo r_GfxInfo, bool selected) const //done
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOR2.jpg";

	
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
}

void Output::DrawXOR2(GraphicsInfo r_GfxInfo, bool selected) const //done
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XOR_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
}

void Output::DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected) const // done
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XNOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XNOR2.jpg";

	//Draw XNOR2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by XNOR2 Image Parameter in UI_Info
	
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
}

void Output::DrawAND3(GraphicsInfo r_GfxInfo, bool selected) const // done
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_AND3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_AND3.jpg";

	//Draw AND3 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND3 Image Parameter in UI_Info
	
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
}

void Output::DrawNOR3(GraphicsInfo r_GfxInfo, bool selected) const//done
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOR3.jpg";

	
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
}

void Output::DrawXOR3(GraphicsInfo r_GfxInfo, bool selected) const //done
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XOR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR3.jpg";

	
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width , UI.Gate_Height);
}

void Output::DrawLED(GraphicsInfo r_GfxInfo, bool is_high, bool selected) const //done
{

	
	string GateImage;

	if (UI.AppMode == SIMULATION)
	{
		if (is_high)
		{
			GateImage = "Images\\Gates\\on_LED.jpeg";

		}
		else
		{
			GateImage = "Images\\Gates\\off_LED.jpeg";

		}
	}
	else {
		if (selected)	//use image in the highlighted case
			GateImage = "Images\\Gates\\LED_Hi.jpeg";
		else
			GateImage = "Images\\Gates\\off_LED.jpeg";
	}
	
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
}

void Output::DrawSWITCH(GraphicsInfo r_GfxInfo, bool is_on, bool selected) const //DONE
{
	string GateImage;
	//NOTE: i will manipulate is_on variable in phase 2 ISA

	if (UI.AppMode == SIMULATION)
	{
		if (is_on)
		{
			GateImage = "Images\\Gates\\on_switch.jpeg";

		}
		else
		{
			GateImage = "Images\\Gates\\off_switch.jpg";
		}
	}
	else {
		if (selected)	//use image in the highlighted case
			GateImage = "Images\\Gates\\off_Hi_SWITCH.jpg";
		else
			GateImage = "Images\\Gates\\off_switch.jpg";
	}

	
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
}
MODE Output::getAppMode()
{
	return UI.AppMode;
}


void Output::DrawConnection(GraphicsInfo r_GfxInfo, bool selected, bool is_high) const
{
	
	if (UI.AppMode == SIMULATION)
	{
		if (is_high)
			pWind->SetPen(UI.on_ConnColor, UI.Conn_width);
		else
			pWind->SetPen(UI.ConnColor, UI.Conn_width);
	}
	else
	{
		if(selected)
			pWind->SetPen(UI.selected_connColor, UI.Conn_width);
		else
			pWind->SetPen(UI.ConnColor, UI.Conn_width);

	}


	int const x1_ = r_GfxInfo.x1 + 20;

	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, x1_, r_GfxInfo.y1);
	pWind->DrawLine(x1_, r_GfxInfo.y1, x1_, r_GfxInfo.y2);
	pWind->DrawLine(x1_, r_GfxInfo.y2, r_GfxInfo.x2, r_GfxInfo.y2);


}
	// ============================== Ahmed Alaa edited here ==============================
void Output::DrawTextbox(string msg, Component* component)
{
	// Set the Message offset from the Component
	GraphicsInfo r_GfxInfo = component->getGraphicsInfo(); // To get the x1, y1, x2, y2 from the selected component
	int MsgX = r_GfxInfo.x1 - 15; // To set the x coordinate that the textbox will display on.
	int MsgY = r_GfxInfo.y1 - 15; // To set the y coordinate that the textbox will display on.
	// Print the Message
	pWind->SetFont(15, BOLD | ITALICIZED, BY_NAME, "Arial"); // To format the font settings
	pWind->SetPen(UI.MsgColor); // To format the textbox's string color
	pWind->DrawString(MsgX, MsgY, msg); // To draw the string in the textbox
	
}
void Output::ClearComponentArea(GraphicsInfo r_GfxInfo)
{
	
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x2, r_GfxInfo.y2);
}

void Output::Clear_Connection_DrawingArea(GraphicsInfo r_GfxInfo) const
{
	pWind->SetPen(WHITE, UI.Conn_width);

	int const x1_ = r_GfxInfo.x1 + 20;

	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, x1_, r_GfxInfo.y1);
	pWind->DrawLine(x1_, r_GfxInfo.y1, x1_, r_GfxInfo.y2);
	pWind->DrawLine(x1_, r_GfxInfo.y2, r_GfxInfo.x2, r_GfxInfo.y2);

}
void Output::ClearLabelArea(GraphicsInfo r_GfxInfo, int len)
{
	len *= 10;
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(r_GfxInfo.x1 - 15, r_GfxInfo.y1 - 15, r_GfxInfo.x1 - 15 + len, r_GfxInfo.y1);
}




Output::~Output()
{
	delete pWind;
}
