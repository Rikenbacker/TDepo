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

TDC::Vector3DFloat::Vector3DFloat(irr::core::vector3df vect3df)
    : Vector3D<float>(vect3df.X, vect3df.Y, vect3df.Z)
{

}
