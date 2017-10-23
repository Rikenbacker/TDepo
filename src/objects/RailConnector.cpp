#include "RailConnector.h"

RailConnector::RailConnector(Ray3D ray)
{
	m_ray = ray;
}

RailConnector::RailConnector(RailConnector *parent)
{
	m_ray = parent->m_ray;
	m_parent = parent;
	parent->setParent(this);
}

RailConnector::~RailConnector()
{
	if (m_parent)
		m_parent->setParent(nullptr);
}

void RailConnector::setParent(RailConnector *parent)
{
	m_parent = parent;
}

const Rails *RailConnector::getLinkedRail()
{
	return m_link;
}

void RailConnector::setLinkedRail(Rails *link)
{
	m_link = link;
}