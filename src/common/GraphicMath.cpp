/*!
    \author dkuleshov3 
    \date 08.11.2017
*/

#include "GraphicMath.h"
#include "../exceptions/ArrayException.h"

void GraphicMath::calcNormales(irr::video::S3DVertex *vertices, unsigned long numVertices, const irr::u16 *const indices,
                          unsigned long numIndices)
{
    for (int i = 0; i + 3 < numIndices; i += 3)
    {
        if (numVertices <= indices[i] || numVertices <= indices[i + 1] || numVertices <= indices[i + 2])
            throw ArrayException(L"Array irr::video::S3DVertex *vertices out of index.");

        irr::core::vector3df *dotA = &vertices[indices[i]].Pos;
        irr::core::vector3df *dotB = &vertices[indices[i + 1]].Pos;
        irr::core::vector3df *dotC = &vertices[indices[i + 2]].Pos;

        irr::core::vector3df ab = *dotB - *dotA;
        irr::core::vector3df ac = *dotC - *dotA;

        irr::core::vector3df nor = ab.crossProduct(ac);
        nor = nor / nor.getLength();
        vertices[indices[i]].Normal = nor;
        vertices[indices[i + 1]].Normal = nor;
        vertices[indices[i + 2]].Normal = nor;
    }
}
