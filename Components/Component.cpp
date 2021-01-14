#include "Component.h"
#include <fstream>
#include <iostream>
using namespace std;
Component::Component(const GraphicsInfo &r_GfxInfo): Label(nullptr)
{
	m_Id = LastID++;
	last_taken_input_pin_place= 0;
	//ID = id;
	comp_type = COMP_TYPES::COMP_GENERAL;
	m_GfxInfo = r_GfxInfo;	
	is_selected = false;
}
Component::Component()
{

	m_Id = LastID++;
	last_taken_input_pin_place = 0;


}
//=================DOAA==========//
int Component::LastID = 0;
//=================DOAA==========//

int Component::get_place() 
{
	return last_taken_input_pin_place++;
}

// ============================== Ahmed Alaa edited here ==============================
void Component::set_Label(LabelOfComp* Label)
{
	this->Label = Label; // To set the passing pointer (pointer to LabelOfComp) to the private data member <Label>
}

LabelOfComp* Component::get_Label()
{
	return Label; // To get the private data member <Label>
}
// ==================================== Ahmed Alaa ====================================

int Component::get_id() const
{
	return m_Id;
}

void Component::set_id(int id)
{
	m_Id = id;
}

const GraphicsInfo Component::getGraphicsInfo()
{
	return m_GfxInfo;
}

bool Component::get_is_selected()
{
	return is_selected;
}

void Component::set_is_selected(bool test)
{
	is_selected = test;
}

void Component::save(ofstream*& fptr)
{
	*fptr << m_Id << "\t" << Label->get_label() << "\t" << m_GfxInfo.x1 << "\t" << m_GfxInfo.y1 << endl;
}

void Component::load(ifstream*& iptr)
{
	*iptr >> m_Id;
	iptr->ignore();
	getline(*iptr, Label->get_label(), '\t');
	*iptr >> m_GfxInfo.x1 >> m_GfxInfo.y1;
	m_GfxInfo.x2 = m_GfxInfo.x1 + UI.Gate_Width;
	m_GfxInfo.y2 = m_GfxInfo.y1 + UI.Gate_Height;

}
COMP_TYPES Component::get_comp_type() const
{
	return COMP_TYPES::COMP_GENERAL;
}

//////Rufaida
InputPin* Component::GetInpuPin(int i) const
{
	return nullptr;
}

Component::~Component()
{
	delete this->Label;
	this->Label = NULL;
}

void Component::getm_GfxInfo(int &x1, int &y1, int &x2, int &y2)
{
	x1 = m_GfxInfo.x1;
	x2 = m_GfxInfo.x2;
	y1 = m_GfxInfo.y1;
	y2 = m_GfxInfo.y2;

}
