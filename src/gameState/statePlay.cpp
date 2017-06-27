#include "statePlay.h"

#include "OgreSceneManager.h"
#include "OgreItem.h"

statePlay::statePlay(GraphicSystem *gs) :
	gameState(gs)
{

	Ogre::Item *item = m_graphicSystem->getSceneManager()->createItem("ogrehead.mesh", Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME, Ogre::SCENE_DYNAMIC);
	Ogre::SceneNode *sceneNode = m_graphicSystem->getSceneManager()->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);
	sceneNode->attachObject(item);
	/*
	Ogre::Light *light = myGraphic->getSceneManager()->createLight();
	Ogre::SceneNode *lightNode = myGraphic->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	lightNode->attachObject(light);
	light->setPowerScale(Ogre::Math::PI); //Since we don't do HDR, counter the PBS' division by PI
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(-1, -1, -1).normalisedCopy());*/

	m_graphicSystem->getSceneManager()->setAmbientLight(Ogre::ColourValue::White, Ogre::ColourValue::White, Ogre::Vector3::UNIT_Y);
}


statePlay::~statePlay()
{
}

void statePlay::tick()
{
}

int statePlay::getState()
{
	return m_state;
}

void statePlay::sleep()
{
	if (!m_graphicSystem->getRenderWindow()->isVisible())
	{
		//Don't burn CPU cycles unnecessary when we're minimized.
		Ogre::Threads::Sleep(500);
	}
}
