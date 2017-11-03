//
// Created by dkuleshov3 on 03.11.2017.
//
#pragma once

#include "../common/Vector2DFloat.h"

#include <string>
#include <vector>

class ProceduralProfile
{
    public:
        ProceduralProfile();
        ~ProceduralProfile();

        void addTriangle(TDC::Vector2DFloat, TDC::Vector2DFloat, TDC::Vector2DFloat);
        void addPoint(TDC::Vector2DFloat);

    private:
        //Список внешних точек, для построения объема
        std::vector<TDC::Vector2DFloat> points;

        //Список точек кратный трём, для построения из треугольников профиля.
        std::vector<TDC::Vector2DFloat> triangles;
};