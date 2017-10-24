#pragma once

#include "RailConnector.h"
#include "Rails.h"

#include <string>

class RailWay : public Rails
{
	public:
		RailWay( RailConnector *connectorA, RailConnector *connectorB);
		~RailWay();

	private:
		RailConnector *m_connectorA = nullptr;
		RailConnector *m_connectorB = nullptr;
};
