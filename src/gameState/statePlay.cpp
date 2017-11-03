#include "statePlay.h"
#include "../objects/SimpleCube.h"
#include "../objects/RailMesh.h"

#include <functional>

statePlay::statePlay(GraphicSystem *gs, InputSystem *is) :
	gameState(gs, is)
{
	m_camera = gs->getCamera();

	cube = new SimpleCube(gs);
    cube->moveTo(TDC::Vector3DFloat(50.0f, 50.0f, 50.0f));

    cube = new RailMesh(gs);
    cube->moveTo(TDC::Vector3DFloat(20.0f, 20.0f, 20.0f));

    txt = gs->getGuiEnvironment()->addStaticText(L"Hello World! This is the Irrlicht Software engine!", irr::core::rect<int>(10, 10, 400, 22), true);
    txt->setText(L"HUI");
	/*
	Ogre::Item *item = m_graphicSystem->getSceneManager()->createItem("ogrehead.mesh", Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME, Ogre::SCENE_DYNAMIC);
	Ogre::SceneNode *sceneNode = m_graphicSystem->getSceneManager()->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);
	*/
//	sceneNode->attachObject(item);

	/*
	Ogre::Light *light = myGraphic->getSceneManager()->createLight();
	Ogre::SceneNode *lightNode = myGraphic->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	lightNode->attachObject(light);
	light->setPowerScale(Ogre::Math::PI); //Since we don't do HDR, counter the PBS' division by PI
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(-1, -1, -1).normalisedCopy());

	m_graphicSystem->getSceneManager()->setAmbientLight(Ogre::ColourValue::White, Ogre::ColourValue::White, Ogre::Vector3::UNIT_Y);

	Ogre::ManualObject *manualObject = m_graphicSystem->getSceneManager()->createManualObject();
	
	manualObject->begin("Ogre/Skin", Ogre::OT_LINE_LIST);
	manualObject->position(0, 0, 0);
	manualObject->position(100, 0, 100);
	manualObject->line(0, 1);
	manualObject->end();
	sceneNode->attachObject(manualObject);

	Ogre::MaterialPtr matptr = Ogre::MaterialManager::getSingleton().create("TestTestTest", "General");
	matptr->setReceiveShadows(false);
	//matptr->getTechnique(0)->setLightingEnabled(true);
	matptr->getTechnique(0)->getPass(0)->setDiffuse(Ogre::ColourValue(1, 1, 1, .75));
	matptr->getTechnique(0)->getPass(0)->setAmbient(Ogre::ColourValue(1, 1, 1, .75));
	matptr->getTechnique(0)->getPass(0)->setSelfIllumination(Ogre::ColourValue(1, 1, 1, .75));
	//matptr->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
	//matptr->getTechnique(0)->getPass(0)->setLightingEnabled(false);
	matptr->getTechnique(0)->getPass(0)->setVertexColourTracking(Ogre::TVC_DIFFUSE);
	//matptr->load();
	

	manualObject->begin("BaseWhite", Ogre::OT_LINE_LIST);

	// Back
	manualObject->position(0.0f, 0.0f, 0.0f);
	manualObject->position(0.0f, 1.0f, 0.0f);
	manualObject->line(0, 1);

	manualObject->position(0.0f, 1.0f, 0.0f);
	manualObject->position(1.0f, 1.0f, 0.0f);
	manualObject->line(2, 3);

	manualObject->position(1.0f, 1.0f, 0.0f);
	manualObject->position(1.0f, 0.0f, 0.0f);
	manualObject->line(4, 5);

	manualObject->position(1.0f, 0.0f, 0.0f);
	manualObject->position(0.0f, 0.0f, 0.0f);
	manualObject->line(6, 7);

	// Front
	manualObject->position(0.0f, 0.0f, 1.0f);
	manualObject->position(0.0f, 1.0f, 1.0f);
	manualObject->line(8, 9);

	manualObject->position(0.0f, 1.0f, 1.0f);
	manualObject->position(1.0f, 1.0f, 1.0f);
	manualObject->line(10, 11);

	manualObject->position(1.0f, 1.0f, 1.0f);
	manualObject->position(1.0f, 0.0f, 1.0f);
	manualObject->line(12, 13);

	manualObject->position(1.0f, 0.0f, 1.0f);
	manualObject->position(0.0f, 0.0f, 1.0f);
	manualObject->line(14, 15);

	// Sides
	manualObject->position(0.0f, 0.0f, 0.0f);
	manualObject->position(0.0f, 0.0f, 1.0f);
	manualObject->line(16, 17);

	manualObject->position(0.0f, 1.0f, 0.0f);
	manualObject->position(0.0f, 1.0f, 1.0f);
	manualObject->line(18, 19);

	manualObject->position(1.0f, 0.0f, 0.0f);
	manualObject->position(1.0f, 0.0f, 1.0f);
	manualObject->line(20, 21);

	manualObject->position(1.0f, 1.0f, 0.0f);
	manualObject->position(1.0f, 1.0f, 1.0f);
	manualObject->line(22, 23);

	manualObject->end();

	Ogre::SceneNode *sceneNodeLines = m_graphicSystem->getSceneManager()->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);
	sceneNodeLines->attachObject(manualObject);
	*/
//	m_inputSystem->addListener(InputEventsType::KeyPressed, SDL_EVENT_CALLBACK(statePlay::OnKeyPressed));
//	m_inputSystem->addListener(InputEventsType::MouseMove, MOUSE_MOVE_CALLBACK(statePlay::OnMouseMove));
//	m_inputSystem->addListener(InputEventsType::MouseWheelScroll, SDL_EVENT_CALLBACK(statePlay::OnMouseWheelScroll));

	setState(GameCondition::Running);
}

statePlay::~statePlay()
{
    if (cube)
        delete cube;
}

void statePlay::tick()
{
//	m_timer->tick();

    if (m_inputSystem->IsKeyDown(irr::KEY_KEY_R))
        m_camera->moveCamera(TDC::Vector3DFloat(0.01, 0, 0));
    if (m_inputSystem->IsKeyDown(irr::KEY_KEY_F))
        m_camera->moveCamera(TDC::Vector3DFloat(-0.01f, 0, 0));
	if (m_inputSystem->IsKeyDown(irr::KEY_KEY_W))
		m_camera->rotateCamera(TDC::Vector3DFloat(0, 0, 0.001));
	if (m_inputSystem->IsKeyDown(irr::KEY_KEY_S))
		m_camera->rotateCamera(TDC::Vector3DFloat(0, 0, -0.001f));
	if (m_inputSystem->IsKeyDown(irr::KEY_KEY_A))
		m_camera->rotateCamera(TDC::Vector3DFloat(0, 0.001, 0));
    if (m_inputSystem->IsKeyDown(irr::KEY_KEY_D))
	    m_camera->rotateCamera(TDC::Vector3DFloat(0, -0.001f, 0));
    if (m_inputSystem->IsKeyDown(irr::KEY_UP))
        m_camera->moveCamera(TDC::Vector3DFloat(0, 0.01, 0));
    if (m_inputSystem->IsKeyDown(irr::KEY_DOWN))
        m_camera->moveCamera(TDC::Vector3DFloat(0, -0.01f, 0));
    if (m_inputSystem->IsKeyDown(irr::KEY_LEFT))
        m_camera->moveCamera(TDC::Vector3DFloat(0, 0, 0.01));
    if (m_inputSystem->IsKeyDown(irr::KEY_RIGHT))
        m_camera->moveCamera(TDC::Vector3DFloat(0, 0, -0.01f));

/*
	if (m_inputSystem->IsKeyDown(irr::KEY_KEY_W))
		m_camera->rotateCamera(TDC::Vector3DFloat(0, 0.001, 0));
	else if (m_inputSystem->IsKeyDown(irr::KEY_KEY_S))
		m_camera->rotateCamera(TDC::Vector3DFloat(0, -0.001, 0));
	if (m_inputSystem->IsKeyDown(irr::KEY_KEY_A))
		m_camera->rotateCamera(TDC::Vector3DFloat(0.001, 0, 0));
	else if (m_inputSystem->IsKeyDown(irr::KEY_KEY_D))
		m_camera->rotateCamera(TDC::Vector3DFloat(-0.001, 0, 0));
*/
/*	if (m_inputSystem->isQuit())
		setState(GameCondition::Exit);
*/
    TDC::Vector3DFloat position = m_camera->getPosition();
    TDC::Vector3DFloat target = m_camera->getTarget();
    std::wstring text = L"Pos ";
    text += std::to_wstring(position.x);
    text += L",";
    text += std::to_wstring(position.y);
    text += L",";
    text += std::to_wstring(position.z);
    text += L", Trgt ";
    text += std::to_wstring(target.x);
    text += L",";
    text += std::to_wstring(target.y);
    text += L",";
    text += std::to_wstring(target.z);
    txt->setText(text.c_str());
}

GameCondition statePlay::getState()
{
	return m_state;
}

void statePlay::sleep()
{
	/*
	if (!m_graphicSystem->getRenderWindow()->isVisible())
		Ogre::Threads::Sleep(10);
		*/
}

void statePlay::setState(GameCondition cond)
{
	m_state = cond;
}
/*
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

void statePlay::OnMouseMove(TDC::Vector2D<unsigned int> *position, TDC::Vector2D<unsigned int> *relation, TDC::MouseButtons *btns)
{
	if (btns->ButtonRight)
		m_camera->rotateCamera(relation->x, relation->y, m_timer->getLastTicks());
}

void statePlay::OnKeyPressed(LSDLEvent * evt)
{
	SDL_KeyboardEvent key = evt->getSDL_Event()->key;
	switch (key.keysym.scancode)
	{
		case SDL_SCANCODE_A:
			m_camera->moveCamera(TDC::Vector3DFloat(-1.0f, 0.0f, 0.0f), m_timer->getLastTicks());
			break;
		case SDL_SCANCODE_D: 
			m_camera->moveCamera(TDC::Vector3DFloat(1.0f, 0.0f, 0.0f), m_timer->getLastTicks());
			break;
		case SDL_SCANCODE_S:
			m_camera->moveCamera(TDC::Vector3DFloat(0.0f, 0.0f, 1.0f), m_timer->getLastTicks());
			break;
		case SDL_SCANCODE_W:
			m_camera->moveCamera(TDC::Vector3DFloat(0.0f, 0.0f, -1.0f), m_timer->getLastTicks());
			break;
		case SDL_SCANCODE_R:
			m_camera->moveCamera(TDC::Vector3DFloat(0.0f, 1.0f, 0.0f), m_timer->getLastTicks());
			break;
		case SDL_SCANCODE_F:
			m_camera->moveCamera(TDC::Vector3DFloat(0.0f, -1.0f, 0.0f), m_timer->getLastTicks());
			break;
	}
}
*/

RailSystem *statePlay::getRailSystem()
{
	return &m_railSystem;
}

WorldCamera *statePlay::getCamera()
{
	return m_camera;
}