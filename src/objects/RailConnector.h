#pragma once

#include "Rails.h"
#include "..\common\Ray3D.h"

class RailConnector
{
	public:
		RailConnector();
		~RailConnector();

	private:
		RailConnector *m_parent = nullptr;
		Rails *m_link = nullptr;
		Ray3D m_ray;
};