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

			void add(Vector3D _add) { x += _add.x; y += _add.y; z += _add.z; };

			valType x;
			valType y;
			valType z;
	};
}