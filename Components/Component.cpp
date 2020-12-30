#include "Component.h"
#include <fstream>
#include <iostream>
using namespace std;
Component::Component(const GraphicsInfo &r_GfxInfo)
{
	comp_type = COMP_TYPES::COMP_GENERAL;
	m_GfxInfo = r_GfxInfo;	
	is_selected = 0;
}

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

void Component::save(ofstream* fptr)
{
	switch (comp_type)
	{
	case COMP_TYPES::COMP_SWITCH:
		*fptr << "SWTCH\t";
		break;
	case COMP_TYPES::COMP_LED:
		*fptr << "LED\t";
		break;
	}
	*fptr << m_Id << "\t" << m_Label << "\t" << m_GfxInfo.x1 << "\t" << m_GfxInfo.y1 << endl;
}

void Component::load(ifstream* iptr)
{

}
Component::Component()
{}

Component::~Component()
{}

