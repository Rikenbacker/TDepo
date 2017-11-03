//
// Created by dkuleshov3 on 02.11.2017.
//
#include "SimpleCube.h"

SimpleCube::SimpleCube(GraphicSystem *graphicSystem)
        : BaseGameObject()
{
    if (!graphicSystem || !graphicSystem->getSceneManager())
        return;

    sceneNode = graphicSystem->getSceneManager()->addCubeSceneNode(20);
    sceneNode->setPosition(position.getIrr3df());
    sceneNode->render();
}

SimpleCube::~SimpleCube()
{

}
