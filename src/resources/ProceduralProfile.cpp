//
// Created by dkuleshov3 on 03.11.2017.
//
#include "ProceduralProfile.h"

ProceduralProfile::ProceduralProfile()
{

}

ProceduralProfile::~ProceduralProfile()
{
    points.clear();
    triangles.clear();
}

void ProceduralProfile::addTriangle(TDC::Vector2DFloat a, TDC::Vector2DFloat b, TDC::Vector2DFloat c)
{
    triangles.push_back(a);
    triangles.push_back(b);
    triangles.push_back(c);
}

void ProceduralProfile::addPoint(TDC::Vector2DFloat point)
{
    points.push_back(point);
}

const std::vector<TDC::Vector2DFloat> ProceduralProfile::getTriangles()
{
    return triangles;
}
