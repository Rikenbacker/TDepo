//
// Created by dkuleshov3 on 03.11.2017.
//

#include "Vector2DFloat.h"

TDC::Vector2DFloat::Vector2DFloat()
        :Vector2D<float>()
{

}

TDC::Vector2DFloat::Vector2DFloat(irr::core::vector2df vect2df)
        : Vector2D<float>(vect2df.X, vect2df.Y)
{

}

TDC::Vector2DFloat::Vector2DFloat(float _x, float _y)
        : Vector2D<float>(_x, _y)
{

}

irr::core::vector2df TDC::Vector2DFloat::getIrr2df()
{
    return irr::core::vector2df(x, y);
}

TDC::Vector2DFloat::~Vector2DFloat()
{

}
