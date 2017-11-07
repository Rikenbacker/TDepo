//
// Created by dkuleshov3 on 02.11.2017.
//

#include "RailMesh.h"

RailMesh::RailMesh(GraphicSystem *graphicSystem)
    :BaseGameObject()
{
    irr::scene::SMeshBuffer *buf = 0;
    irr::scene::SMesh* Mesh;

    irr::scene::SMesh *m = new irr::scene::SMesh();
    irr::scene::SMeshBuffer *meshbuf = new irr::scene::SMeshBuffer();
    irr::scene::IMeshSceneNode *node;
/*
    irr::video::S3DVertex ver2[] = {irr::video::S3DVertex(0,0,0, 1,0,0, irr::video::SColor(255,0,255,255), 0, 1)
            , irr::video::S3DVertex(0,20,-20, 1,0,0, irr::video::SColor(255,255,255,0), 1, 0)
            , irr::video::S3DVertex(0,0,-20, 1,0,0, irr::video::SColor(255,0,255,0), 0, 0)
            , irr::video::S3DVertex(0,20,0, 1,0,0, irr::video::SColor(255,0,255,255), 0, 1)
            , irr::video::S3DVertex(0,20,-20, 1,0,0, irr::video::SColor(255,255,255,0), 1, 0)
            , irr::video::S3DVertex(0,0,0, 1,0,0, irr::video::SColor(255,0,255,0), 0, 0)};

    irr::u16 indices[] = { 0,1,2, 3, 4, 5};
    m->addMeshBuffer(meshbuf);
    meshbuf->drop();

    meshbuf->append((const void*)&ver2, 6, (irr::u16*)&indices, 6);
    meshbuf->Vertices.reallocate(6);
    meshbuf->Vertices.set_used(6);
    meshbuf->Indices.set_used(6);
    meshbuf->recalculateBoundingBox();
*/
    ProceduralProfile *railProfile = graphicSystem->getResources()->getProceduralProfile(L"RP65_Rail");

    int verticlesCount = railProfile->getTriangles().size();

    irr::video::S3DVertex *ver2 = new irr::video::S3DVertex[verticlesCount]();
    irr::u16 *indices = new irr::u16[verticlesCount]();

    int i = 0;
    for(TDC::Vector2DFloat point : railProfile->getTriangles())
    {
        ver2[i] = irr::video::S3DVertex(0, point.x, point.y, 1, 0,0, irr::video::SColor(255,0,255,255), 0, 1);
        indices[i] = i;
        i++;
    };

    m->addMeshBuffer(meshbuf);
    meshbuf->drop();

    meshbuf->append((const void*)ver2, verticlesCount, (irr::u16*)indices, verticlesCount);
    meshbuf->Vertices.reallocate(verticlesCount);
    meshbuf->Vertices.set_used(verticlesCount);
    meshbuf->Indices.set_used(verticlesCount);
    meshbuf->recalculateBoundingBox();

    delete[] ver2;
    delete[] indices;



    sceneNode = graphicSystem->getSceneManager()->addMeshSceneNode(m);


    //sceneNode->setPosition(position.getIrr3df());
    sceneNode->render();
}

RailMesh::~RailMesh()
{

}
