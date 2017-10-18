#pragma once

#include "..\RailConnector.h"

#include <string>

class ConnectorPair
{
	public:
		ConnectorPair();
		~ConnectorPair();

	private:
		std::wstring name;
		RailConnector *left = nullptr;
		RailConnector *right = nullptr;
};

