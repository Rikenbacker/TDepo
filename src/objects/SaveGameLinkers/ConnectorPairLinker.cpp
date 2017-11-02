#include "ConnectorPairLinker.h"

#include "..\..\exceptions\XMLException.h"

ConnectorPairLinker::ConnectorPairLinker()
{
}


ConnectorPairLinker::~ConnectorPairLinker()
{
}

void ConnectorPairLinker::clear()
{
	connectorPairs.clear();
}

void ConnectorPairLinker::deleteUnused()
{
	for (ConnectorPair* pair : connectorPairs)
	{
		if (pair->getLeft()->getLinkedRail() == nullptr)
			delete pair->getLeft();
		if (pair->getRight()->getLinkedRail() == nullptr)
			delete pair->getRight();
	};

	clear();
}

void ConnectorPairLinker::createPair(std::wstring name, Ray3D ray)
{
	if (searchConnector(name))
		throw new XMLException(L"Connector " + name + L" already exists.");

	connectorPairs.push_back(new ConnectorPair(name, ray));
}

ConnectorPair* ConnectorPairLinker::searchConnector(std::wstring name)
{
	for (ConnectorPair* pair : connectorPairs)
	{
		if (pair->isEqual(name))
			return pair;
	};
	
	return nullptr;
}

RailConnector *ConnectorPairLinker::getUnlinkedConnector(std::wstring name)
{
	ConnectorPair *pair = searchConnector(name);
	if (!pair)
		return nullptr;

	if (!pair->getLeft()->getLinkedRail())
		return pair->getLeft();

	if (!pair->getRight()->getLinkedRail())
		return pair->getRight();

	return nullptr;
}