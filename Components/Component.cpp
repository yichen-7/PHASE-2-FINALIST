
#include "Component.h"

Component::Component(const GraphicsInfo &r_GfxInfo)
{
	m_GfxInfo = r_GfxInfo;	
	m_Selected = false;  // Initialize selection to false
	m_Label = "";        // Initialize label to empty
}

Component::Component()
{
	m_Selected = false;
	m_Label = "";
}

Component::~Component()
{
}