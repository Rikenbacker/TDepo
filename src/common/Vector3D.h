#pragma once

#include "Ogre.h"

namespace TDC
{
	template <typename valType>
	class Vector3D
	{
		public:
			Vector2D(valType _x, valType _y, valType _z) { x = _x; y = _y; z =_z};
			~Vector2D() {};

			valType x;
			valType y;
			valType z;
	};

	class Vector3DFloat : public Vector3D<float>
	{
		public:
			Vector3DFloat(Ogre::Vector3 oV) { x = oV.x; y = oV.y; z = oV.z; };
			Vector3DFloat(float _x, float _y, float _z) { x = _x, y = _y, z = _z; };
			~Vector3DFloat() {};

			Ogre::Vector3 toOgreVector() { return Ogre::Vector3(x, y, z); };
	};
}