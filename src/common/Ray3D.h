#pragma once

#include "Vector3DFloat.h"

class Ray3D
{
	public:
		Ray3D();
		~Ray3D();

	private:
		TDC::Vector3DFloat m_position;
		TDC::Vector3DFloat m_direction;
};

