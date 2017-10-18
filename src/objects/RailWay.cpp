#include "RailWay.h"


RailWay::RailWay(std::wstring name, RailConnector *connectorA, RailConnector *connectorB)
{
	m_name = name;
	m_connectorA = connectorA;
	m_connectorB = connectorB;
}


RailWay::~RailWay()
{
}
