#pragma once

namespace TDC
{
	template <typename valType>
	class Vector3D
	{
		public:
			Vector3D(valType _x, valType _y, valType _z) { x = _x; y = _y; z = _z; };
			Vector3D() {};
			~Vector3D() {};

			valType x;
			valType y;
			valType z;
	};
}