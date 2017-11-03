//
// Created by dkuleshov3 on 03.11.2017.
//
#pragma once

#include "Vector2D.h"


#include <irrlicht.h>

namespace TDC
{
    class Vector2DFloat : public Vector2D<float>
    {
        public:
            Vector2DFloat();
            explicit Vector2DFloat(irr::core::vector2df);
            Vector2DFloat(float _x, float _y);

            irr::core::vector2df getIrr2df();

            ~Vector2DFloat();
    };
}