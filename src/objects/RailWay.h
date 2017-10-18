#pragma once

#include "RailConnector.h"
#include "Rails.h"

#include <string>

class RailWay : public Rails
{
	public:
		RailWay(std::wstring name, RailConnector *connectorA, RailConnector *connectorB);
		~RailWay();

	private:
		std::wstring m_name = L"";
		RailConnector *m_connectorA = nullptr;
		RailConnector *m_connectorB = nullptr;
};
