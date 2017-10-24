#include "RailWay.h"

RailWay::RailWay(RailConnector *connectorA, RailConnector *connectorB)
{
	m_connectorA = connectorA;
	m_connectorB = connectorB;

	m_connectorA->setLinkedRail(this);
	m_connectorB->setLinkedRail(this);
}

RailWay::~RailWay()
{
	if (m_connectorA)
		delete m_connectorA;

	if (m_connectorB)
		delete m_connectorB;

}
