#include "BaseGameObject.h"


BaseGameObject::BaseGameObject(GraphicSystem *graphicSystem)
{
	if (!graphicSystem || !graphicSystem->getSceneManager())
		return;

	m_body = graphicSystem->getSceneManager()->addCubeSceneNode(20);
	m_body->setPosition(irr::core::vector3df(50, 50, 50));
	m_body->render();
}


BaseGameObject::~BaseGameObject()
{
	m_body->drop();
}

void BaseGameObject::move(float x, float y, float z)
{
	irr::core::vector3df nodePosition = m_body->getPosition();
	nodePosition.X += x;
	nodePosition.Y += y;
	nodePosition.Z += z;

	m_body->setPosition(nodePosition);
}

void BaseGameObject::moveTo(float x, float y, float z)
{
	m_body->setPosition(irr::core::vector3df(x, y, z));
}