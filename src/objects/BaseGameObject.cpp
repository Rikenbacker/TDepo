#include "BaseGameObject.h"


BaseGameObject::BaseGameObject()
{
}


BaseGameObject::~BaseGameObject()
{
    if (sceneNode)
        sceneNode->drop();

    sceneNode = nullptr;
}

void BaseGameObject::move(TDC::Vector3DFloat delta)
{
    position.add(delta);
    sceneNode->setPosition(position.getIrr3df());
}

void BaseGameObject::moveTo(TDC::Vector3DFloat position)
{
    this->position = position;
    sceneNode->setPosition(position.getIrr3df());
}