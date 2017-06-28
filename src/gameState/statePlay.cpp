#include "statePlay.h"

#include <functional>

#include "OgreSceneManager.h"
#include "OgreItem.h"

statePlay::statePlay(GraphicSystem *gs, InputSystem *is) :
	gameState(gs, is)
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

	m_inputSystem->addListener(InputEventsType::KeyPressed, std::bind(&statePlay::OnKeyPressed, this, std::placeholders::_1));
	m_inputSystem->addListener(InputEventsType::MouseWheelScroll, std::bind(&statePlay::OnMouseWheelScroll, this, std::placeholders::_1));

	setState(GameCondition::Running);
}

statePlay::~statePlay()
{
}

void statePlay::tick()
{
	if (m_inputSystem->isQuit())
		setState(GameCondition::Exit);
}

GameCondition statePlay::getState()
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

void statePlay::setState(GameCondition cond)
{
	m_state = cond;
}

void statePlay::OnMouseWheelScroll(LSDLEvent *evt)
{
	setState(GameCondition::NeedChange);

	evt->callNext();
}

void statePlay::OnMouseClick(LSDLEvent * evt)
{
	setState(GameCondition::Exit);

	evt->callNext();
}

void statePlay::OnKeyPressed(LSDLEvent * evt)
{
	SDL_KeyboardEvent key = evt->getSDL_Event()->key;
	switch (key.keysym.scancode)
	{
		case SDL_SCANCODE_D: 
			m_graphicSystem->getCamera()->move(Ogre::Vector3(1.0f, 0.0f, 0.0f));
			break;
		case SDL_SCANCODE_A:
			m_graphicSystem->getCamera()->move(Ogre::Vector3(-1.0f, 0.0f, 0.0f));
			break;
		case SDL_SCANCODE_S:
			m_graphicSystem->getCamera()->move(Ogre::Vector3(0.0f, 0.0f, 1.0f));
			break;
		case SDL_SCANCODE_W:
			m_graphicSystem->getCamera()->move(Ogre::Vector3(0.0f, 0.0f, -1.0f));
			break;
		case SDL_SCANCODE_R:
			m_graphicSystem->getCamera()->move(Ogre::Vector3(0.0f, 1.0f, 0.0f));
			break;
		case SDL_SCANCODE_F:
			m_graphicSystem->getCamera()->move(Ogre::Vector3(0.0f, -1.0f, 0.0f));
			break;
	}
}
