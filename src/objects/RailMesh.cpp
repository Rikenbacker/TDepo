//
// Created by dkuleshov3 on 02.11.2017.
//

#include "RailMesh.h"

RailMesh::RailMesh(GraphicSystem *graphicSystem)
    :BaseGameObject()
{
    auto *Mesh = new irr::scene::SMesh();
    auto *MeshBuf = new irr::scene::SMeshBuffer();

    ProceduralProfile *railProfile = graphicSystem->getResources()->getProceduralProfile(L"RP65_Rail");

    unsigned long verticlesCount = railProfile->getPoints()->size();
    unsigned long indexesCount = railProfile->getTrianglesCount();

    auto *ver2 = new irr::video::S3DVertex[verticlesCount]();

    int i = 0;
    for(TDC::Vector2DFloat point : *railProfile->getPoints())
        ver2[i++] = irr::video::S3DVertex(0, point.x, point.y, 1, 0,0, irr::video::SColor(255,0,255,255), 0, 1);

    const irr::u16 *indices = railProfile->getTrianglesArray();

    Mesh->addMeshBuffer(MeshBuf);
    MeshBuf->drop();

    MeshBuf->append((const void*)ver2, (irr::u32)verticlesCount, (irr::u16*)indices, (irr::u32)indexesCount);
    MeshBuf->Vertices.reallocate((irr::u32)verticlesCount);
    MeshBuf->Vertices.set_used((irr::u32)verticlesCount);
    MeshBuf->Indices.set_used((irr::u32)indexesCount);
    MeshBuf->recalculateBoundingBox();

    delete[] ver2;

    sceneNode = graphicSystem->getSceneManager()->addMeshSceneNode(Mesh);

    sceneNode->render();
}

RailMesh::~RailMesh()
{

}
