#pragma once

#include "Rails.h"
#include "..\common\Ray3D.h"

class RailConnector
{
	public:
		RailConnector(Ray3D ray);
		RailConnector(RailConnector *parent);
		~RailConnector();

		const Rails *getLinkedRail();
		void setLinkedRail(Rails *);

	private:
		RailConnector *m_parent = nullptr;
		Rails *m_link = nullptr;
		Ray3D m_ray;

		void setParent(RailConnector *);
};