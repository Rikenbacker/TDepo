#pragma once

#include "..\RailConnector.h"

#include <string>

class ConnectorPair
{
	public:
		ConnectorPair(std::wstring, Ray3D);
		~ConnectorPair();

		bool isEqual(std::wstring);


		RailConnector *getLeft();
		RailConnector *getRight();

	private:
		std::wstring name;
		RailConnector *left = nullptr;
		RailConnector *right = nullptr;
};

