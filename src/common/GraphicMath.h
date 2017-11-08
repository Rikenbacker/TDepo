/*!
    \author dkuleshov3 
    \date 08.11.2017
*/

#pragma once

#include "irrlicht.h"

class GraphicMath
{
    public:
        static void calcNormales(irr::video::S3DVertex* vertices, unsigned long numVertices, const irr::u16* const indices, unsigned long numIndices);
};



