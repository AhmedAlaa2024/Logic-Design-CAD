#include "Output.h"

Output::Output()
{
	//Initialize user interface parameters

	UI.AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	UI.DrawColor = BLACK;
	UI.SelectColor = BLUE;
	UI.ConnColor = RED;
	UI.on_ConnColor = GREEN;
	UI.selected_connColor = BLUE;

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
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, UI.height-UI.StatusBarHeight, UI.width, UI.height-UI.StatusBarHeight);
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
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
	
}
void Output::ClearWindow() const
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0,0, UI.width, UI.height);

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
	MenuItemImages[ORGANIZE_SCREEN] = "images\\DesignMenu\\organize.jpg";
	MenuItemImages[CLEAR] = "images\\DesignMenu\\clear.jpg";
	MenuItemImages[LOAD_ICON] = "images\\DesignMenu\\load.jpg";
	MenuItemImages[SAVE_ICON] = "images\\DesignMenu\\save.jpg";
	MenuItemImages[ITM_EXIT] = "images\\DesignMenu\\exit.jpg";

	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i < ITM_DSN_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);


	string DesignTools[GATES_CNT];
	DesignTools[AND_2IN] = "images\\Gates\\AND2.jpg";
	DesignTools[OR_2IN] = "images\\Gates\\OR2.jpg";
	DesignTools[BUF] = "images\\Gates\\BUFFER.jpg";
	DesignTools[NOT] = "images\\Gates\\NOT2.jpg";
	DesignTools[NAND_2IN] = "images\\Gates\\NAND2.jpg";
	DesignTools[NOR_2IN] = "images\\Gates\\NOR2.jpg";
	DesignTools[XOR_2IN] = "images\\Gates\\XOR2.jpg";
	DesignTools[XNOR_2IN] = "images\\Gates\\XNOR2.jpg";
	DesignTools[AND_3IN] = "images\\Gates\\AND2.jpg";
	DesignTools[OR_3IN] = "images\\Gates\\OR2.jpg";
	DesignTools[NAND_3IN] = "images\\Gates\\NAND2.jpg";
	DesignTools[NOR_3IN] = "images\\Gates\\NOR2.jpg";
	DesignTools[XOR_3IN] = "images\\Gates\\XOR2.jpg";
	DesignTools[XNOR_3IN] = "images\\Gates\\XNOR2.jpg";
	DesignTools[LED] = "images\\Gates\\LED.jpg";
	DesignTools[SWITCH] = "images\\Gates\\SWITCH.jpg";

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
	MenuItemImages[Add_Label] = "images\\SimulationMenu\\text.jpg";
	MenuItemImages[Edit_label] = "images\\SimulationMenu\\edit.jpg";
	MenuItemImages[ITM_CHANGE_SWITCH] = "images\\SimulationMenu\\closed_switch.jpg";
	MenuItemImages[ITM_UNDO] = "images\\SimulationMenu\\undo.jpg";
	MenuItemImages[ITM_REDO] = "images\\SimulationMenu\\redo.jpg";
	MenuItemImages[ITM_LOAD] = "images\\SimulationMenu\\load.jpg";
	MenuItemImages[ITM_SAVE] = "images\\SimulationMenu\\save.jpg";
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
		GateImage = "Images\\Gates\\Gate_INV.jpeg";

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

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	//
	//TODO: I need to change those heights and widths
	//
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
}
void Output::DrawOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_OR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_OR3.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	//
	//TODO: I need to change those heights and widths
	//
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
}
void Output::DrawNAND2(GraphicsInfo r_GfxInfo, bool selected) const //done
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NAND2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NAND2.jpg";

	//Draw NAND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by NAND2 Image Parameter in UI_Info
	//
	//TODO: I need to change those heights and widths
	//
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
}

void Output::DrawNOR2(GraphicsInfo r_GfxInfo, bool selected) const //done
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOR2.jpg";

	//Draw NOR2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by NOR2 Image Parameter in UI_Info
	//
	//TODO: I need to change those heights and widths
	//
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
}

void Output::DrawXOR2(GraphicsInfo r_GfxInfo, bool selected) const //done
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XOR_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR.jpg";

	//Draw XOR Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by XOR Image Parameter in UI_Info
	//
	//TODO: I need to change those heights and widths
	//
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
	//
	//TODO: I need to change those heights and widths
	//
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
	//
	//TODO: I need to change those heights and widths
	//
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
}

void Output::DrawNOR3(GraphicsInfo r_GfxInfo, bool selected) const//done
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOR3.jpg";

	//Draw NOR3 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by NOR3 Image Parameter in UI_Info
	//
	//TODO: I need to change those heights and widths
	//
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width +40, UI.Gate_Height);
}

void Output::DrawXOR3(GraphicsInfo r_GfxInfo, bool selected) const //done
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XOR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR3.jpg";

	//Draw XOR3 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by XOR3 Image Parameter in UI_Info
	//
	//TODO: I need to change those heights and widths
	//
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width + 40, UI.Gate_Height);
}

void Output::DrawLED(GraphicsInfo r_GfxInfo, bool is_high, bool selected) const //done
{
	//TODO: to change the images of them
	//TODO: it doesnt accept png
	string GateImage;

	if (UI.AppMode == SIMULATION)
	{
		if (is_high)
		{
			GateImage = "Images\\Gates\\on_LED.jpeg";

		}else
		{
			GateImage = "Images\\Gates\\off_LED.jpeg";

		}
	}
	else {
		if (selected)	//use image in the highlighted case
			GateImage = "Images\\Gates\\LEDH.jpeg";
		else
			GateImage = "Images\\Gates\\LEDH.jpeg";
	}
	//Draw LED at Gfx_Info (1st corner)
	//Set the Image Width & Height by LED Image Parameter in UI_Info
	//
	//TODO: I need to change those heights and widths
	//
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
}

void Output::DrawSWITCH(GraphicsInfo r_GfxInfo, bool is_on, bool selected) const //DONE
{
	string GateImage;
	//NOTE: i will manipulate is_on variable in phase 2 ISA
	
	if (UI.AppMode == SIMULATION)
	{
		if(is_on)
		{
			GateImage = "Images\\Gates\\on_switch.jpeg";

		}else
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
	
	//Draw SWITCH Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by SWITCH Image Parameter in UI_Info
	//
	//TODO: I need to change those heights and widths
	//
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.Gate_Width, UI.Gate_Height);
}
MODE Output::getAppMode()
{
	return UI.AppMode;
}


void Output::DrawConnection(GraphicsInfo r_GfxInfo, bool selected,bool is_high) const
{
	//TODO: Add code to draw connection
	//TODO --> add validation to the coordinates passed
	//
	if(UI.AppMode == SIMULATION)
	{
		if(is_high)
			pWind->SetPen(UI.on_ConnColor, UI.Conn_width);
		else
			pWind->SetPen(UI.ConnColor, UI.Conn_width);
	}else
	{
		pWind->SetPen(UI.selected_connColor, UI.Conn_width);

	}


	int const x1_ = r_GfxInfo.x1 + 20;
	
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, x1_, r_GfxInfo.y1);
	pWind->DrawLine(x1_, r_GfxInfo.y1, x1_, r_GfxInfo.y2);
	pWind->DrawLine(x1_, r_GfxInfo.y2, r_GfxInfo.x2, r_GfxInfo.y2);



}

//------Ahmed Ata edited-----//






Output::~Output()
{
	delete pWind;
}
