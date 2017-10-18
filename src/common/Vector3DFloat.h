#pragma once

#include "Vector3D.h"

namespace TDC
{
	class Vector3DFloat : public Vector3D<float>
	{
		public:
			Vector3DFloat();
			Vector3DFloat(float _x, float _y, float _z);

			~Vector3DFloat();
	};
}
