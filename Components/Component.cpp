#include "Component.h"

Component::Component(const GraphicsInfo &r_GfxInfo)
{
	m_GfxInfo = r_GfxInfo;	
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

Component::Component()
{}

Component::~Component()
{}

