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
    circuit.clear();
}

void ProceduralProfile::addTriangle(unsigned short a, unsigned short b, unsigned short c)
{
    triangles.push_back(a);
    triangles.push_back(b);
    triangles.push_back(c);
}

unsigned short ProceduralProfile::addPoint(TDC::Vector2DFloat point)
{
    points.push_back(point);
    return (unsigned short)points.size() - 1;
}

const std::vector<unsigned short> *ProceduralProfile::getTriangles()
{
    return &triangles;
}

const std::vector<TDC::Vector2DFloat *> *ProceduralProfile::getCircuit()
{
    return &circuit;
}

void ProceduralProfile::addCircuitPoint(int positionPoint)
{
    circuit.push_back(&points[positionPoint]);
}

const TDC::Vector2DFloat *ProceduralProfile::getPointsArray()
{
    return &points[0];
}

const std::vector<TDC::Vector2DFloat> *ProceduralProfile::getPoints()
{
    return &points;
}

const unsigned short *ProceduralProfile::getTrianglesArray()
{
    return &triangles[0];
}

unsigned long ProceduralProfile::getTrianglesCount()
{
    return triangles.size();
}


