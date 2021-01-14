#include "Action.h"

#include "..\GUI\UI_Info.h"

bool Action::if_valid_Area(int cx, int cy)
{
	if (cy > (UI.ToolBarHeight + 0.5 * UI_Info::Gate_Height) && cy < (UI_Info::height - (1.5* UI_Info::Gate_Height + UI.StatusBarHeight)) && cx > UI_Info::Gate_Width && cx < (UI_Info::width - (UI.ToolBarHeight + 15 + UI_Info::Gate_Width)))
	{
		return true;
	}
	return false;
}

bool Action::if_valid_Area_led(int cx, int cy)
{
	if (cy > (UI.ToolBarHeight + .5 * UI_Info::Gate_Height) && cy < (UI_Info::height - (1.5 * UI_Info::Gate_Height + UI.StatusBarHeight)) && cx > UI_Info::Gate_Width && cx < (UI_Info::width - (UI.ToolBarHeight + 15 + .5 * UI_Info::Gate_Width)))
	{
		return true;
	}
	return false;
}

bool Action::if_valid_Area_switch(int cx, int cy)
{
	if (cy > (UI.ToolBarHeight + .5 * UI_Info::Gate_Height) && cy < (UI_Info::height - (1.5 * UI_Info::Gate_Height + UI.StatusBarHeight)) && cx > 0.5 * UI_Info::Gate_Width && cx < (UI_Info::width - (UI.ToolBarHeight + 15 + UI_Info::Gate_Width)))
	{
		return true;
	}
	return false;
}