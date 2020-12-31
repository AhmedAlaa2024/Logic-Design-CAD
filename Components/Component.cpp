#include "Component.h"

Component::Component(const GraphicsInfo &r_GfxInfo)
{
	comp_type = COMP_TYPES::COMP_GENERAL;
	m_GfxInfo = r_GfxInfo;	
	is_selected = false;
	m_Label = "";
}

void Component::set_m_Label(string label)
{
	m_Label = label;
}

string Component::get_m_Label()
{
	return m_Label;
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

COMP_TYPES Component::get_comp_type()
{
	return COMP_TYPES::COMP_GENERAL;
}

Component::Component()
{}

Component::~Component()
{}

