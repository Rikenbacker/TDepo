//
// Created by dkuleshov3 on 02.11.2017.
//

#include "RailMesh.h"
#include "../common/GraphicMath.h"

RailMesh::RailMesh(GraphicSystem *graphicSystem)
    :BaseGameObject()
{
    const float len = 10.0f;
    auto *Mesh = new irr::scene::SMesh();
    auto *MeshBuf = new irr::scene::SMeshBuffer();

    ProceduralProfile *railProfile = graphicSystem->getResources()->getProceduralProfile(L"RP65_Rail");

    unsigned long verticesCount = railProfile->getPoints()->size() * 2 + (railProfile->getCircuit()->size() * 4);
    unsigned long pointsCount = railProfile->getPoints()->size();
    unsigned long indexesCount = (railProfile->getTrianglesCount() * 2) + (railProfile->getCircuit()->size() * 6);

    auto *ver2 = new irr::video::S3DVertex[verticesCount]();
    irr::u16 *indices = new irr::u16[indexesCount]();

    //Добавляю передний профиль
    unsigned short iPoint = 0;
    for(TDC::Vector2DFloat point : *railProfile->getPoints())
        ver2[iPoint++] = irr::video::S3DVertex(0, point.x, point.y, 0, 0,0, irr::video::SColor(255,0,255,255), 0, 1);

    unsigned short iIndex = 0;
    for(unsigned short point : *railProfile->getTriangles())
        indices[iIndex++] = point;

    //Добавляю задний профиль
    for(TDC::Vector2DFloat point : *railProfile->getPoints())
        ver2[iPoint++] = irr::video::S3DVertex(len, point.x, point.y, 0, 0,0, irr::video::SColor(255,0,255,255), 0, 1);

    //В заднем профиле порядок построения треугольников должен быть обратным
    for(std::vector<unsigned short>::const_reverse_iterator point = railProfile->getTriangles()->rbegin(); point != railProfile->getTriangles()->rend(); point++ )
        indices[iIndex++] = *point + pointsCount;

    //Добавляю боковые стенки
    for (std::vector<unsigned short>::const_iterator point = railProfile->getCircuit()->begin(); point != railProfile->getCircuit()->end(); point++)
    {
        std::vector<unsigned short>::const_iterator nextPoint = point == railProfile->getCircuit()->end() - 1 ? railProfile->getCircuit()->begin() : point + 1;

        unsigned short newPoints[4];
        for (int i = 0; i < 4; i++)
            newPoints[i] = iPoint++;

        //Копирую уже существующие точки профиля в новые точки, для возможности индивидуальных нормалей
        ver2[newPoints[0]] = ver2[*point];
        ver2[newPoints[1]] = ver2[*point + pointsCount];
        ver2[newPoints[2]] = ver2[*nextPoint];
        ver2[newPoints[3]] = ver2[*nextPoint + pointsCount];

        //И строю треугольники
        indices[iIndex++] = newPoints[0];
        indices[iIndex++] = newPoints[1];
        indices[iIndex++] = newPoints[3];

        indices[iIndex++] = newPoints[0];
        indices[iIndex++] = newPoints[3];
        indices[iIndex++] = newPoints[2];
    }

    GraphicMath::calcNormales(ver2, verticesCount, indices, indexesCount);

    Mesh->addMeshBuffer(MeshBuf);
    MeshBuf->drop();

    MeshBuf->append((const void*)ver2, (irr::u32)verticesCount, indices, (irr::u32)indexesCount);
    MeshBuf->Vertices.reallocate((irr::u32)verticesCount);
    MeshBuf->Vertices.set_used((irr::u32)verticesCount);
    MeshBuf->Indices.set_used((irr::u32)indexesCount);
    MeshBuf->recalculateBoundingBox();

    delete[] ver2;

    sceneNode = graphicSystem->getSceneManager()->addMeshSceneNode(Mesh);

    sceneNode->render();
}

RailMesh::~RailMesh()
{

}
