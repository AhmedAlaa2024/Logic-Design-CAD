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

Component::Component()
{}

Component::~Component()
{}

