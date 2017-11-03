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

    irr::video::S3DVertex ver2[] = {irr::video::S3DVertex(0,0,10, 1,1,0, irr::video::SColor(255,0,255,255), 0, 1)
            , irr::video::S3DVertex(10,0,-10, 1,0,0, irr::video::SColor(255,255,0,255), 1, 1)
            , irr::video::S3DVertex(0,20,0, 0,1,1, irr::video::SColor(255,255,255,0), 1, 0)
            , irr::video::S3DVertex(-10,0,-10, 0,0,1, irr::video::SColor(255,0,255,0), 0, 0)};

    irr::u16 indices[] = { 0,2,3, 2,1,3, 1,0,3, 2,0,1 };
    m->addMeshBuffer(meshbuf);
    meshbuf->drop();

    meshbuf->append((const void*)&ver2, 4, (irr::u16*)&indices, 12);
    meshbuf->Vertices.reallocate(4);
    meshbuf->Vertices.set_used(4);
    meshbuf->Indices.set_used(12);
    meshbuf->recalculateBoundingBox();

    sceneNode = graphicSystem->getSceneManager()->addMeshSceneNode(m);
    /*sceneNode->setPosition(position.getIrr3df());
    sceneNode->render();
     */
}

RailMesh::~RailMesh()
{

}
