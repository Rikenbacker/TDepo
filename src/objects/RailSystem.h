#pragma once

#include "RailWay.h"
#include "RailConnector.h"

class RailSystem
{
	public:
		RailSystem();
		~RailSystem();

		void addRailWay(RailWay *);
		void addConnector(RailConnector *);


};

