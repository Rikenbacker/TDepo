#include "ConnectorPair.h"


ConnectorPair::ConnectorPair(std::wstring name, Ray3D ray)
{
	this->name = name;
	left = new RailConnector(ray);
	right = new RailConnector(left);
}


ConnectorPair::~ConnectorPair()
{
}

bool ConnectorPair::isEqual(std::wstring name)
{
	return (this->name.compare(name) == 0);
}

RailConnector *ConnectorPair::getLeft()
{
	return left;
}
RailConnector *ConnectorPair::getRight()
{
	return right;
}