#include "Ray3D.h"


Ray3D::Ray3D()
{
}

Ray3D::Ray3D(TDC::Vector3DFloat position, TDC::Vector3DFloat direction)
{
	m_position = position;
	m_direction = direction;
}

Ray3D::~Ray3D()
{
}
