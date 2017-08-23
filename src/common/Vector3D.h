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

	class Vector3DFloat : public Vector3D<float>
	{
		public:
//			Vector3DFloat(Ogre::Vector3 oV) : Vector3D<float>(oV.x, oV.y, oV.z) {};
			Vector3DFloat(float _x, float _y, float _z) : Vector3D<float>(_x, _y, _z) {};
			~Vector3DFloat() {};

//			Ogre::Vector3 toOgreVector() const { return Ogre::Vector3(x, y, z); };
	};
}