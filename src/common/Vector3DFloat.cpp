#include "Vector3DFloat.h"


TDC::Vector3DFloat::Vector3DFloat()
	:Vector3D<float>()
{
}


TDC::Vector3DFloat::~Vector3DFloat()
{
}

TDC::Vector3DFloat::Vector3DFloat(float _x, float _y, float _z) 
	: Vector3D<float>(_x, _y, _z)
{
}

irr::core::vector3df TDC::Vector3DFloat::getIrr3df()
{
	return irr::core::vector3df(x, y, z);
}