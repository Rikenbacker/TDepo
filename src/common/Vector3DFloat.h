#pragma once

#include <irrlicht.h>

#include "Vector3D.h"

namespace TDC
{
	class Vector3DFloat : public Vector3D<float>
	{
		public:
			Vector3DFloat();
			Vector3DFloat(float _x, float _y, float _z);

			irr::core::vector3df getIrr3df();

			~Vector3DFloat();
	};
}
