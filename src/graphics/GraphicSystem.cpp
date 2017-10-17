#include "GraphicSystem.h"


#include "EDriverTypes.h"
#include "irrTypes.h"
#include "IrrlichtDevice.h"
#include "IGUIEnvironment.h"
#include <irrlicht.h>

GraphicSystem::GraphicSystem(irr::video::SColor backgroundColour) :
	m_backgroundColour(backgroundColour)
{
}

GraphicSystem::~GraphicSystem()
{
}

void GraphicSystem::setConfigPath(std::string configPath)
{
	m_configPath = configPath;
}

void GraphicSystem::setLogPath(std::string logPath)
{
	m_logPath = logPath;
}

void GraphicSystem::setResourcePath(std::string pluginPath)
{
	m_resourcePath = pluginPath;
}

bool GraphicSystem::initialize(const std::wstring &windowTitle, InputSystem *inputSystem, bool fullScreen)
{
	m_device = irr::createDevice(irr::video::E_DRIVER_TYPE::EDT_DIRECT3D9, irr::core::dimension2d<irr::u32>(800, 600), 16, fullScreen, false, false, inputSystem);

	if (m_device == nullptr)
		return false; // could not create selected driver.

	m_device->setWindowCaption(windowTitle.c_str());
	m_driver = m_device->getVideoDriver();
	m_sceneManager = m_device->getSceneManager();
	m_guiEnv = m_device->getGUIEnvironment();
	m_device->getCursorControl()->setActiveIcon(irr::gui::ECI_NORMAL);

	createCamera();

	m_guiEnv->addStaticText(L"Hello World! This is the Irrlicht Software engine!", irr::core::rect<int>(10, 10, 200, 22), true);

//	const irr::scene::IGeometryCreator *geomentryCreator = m_sceneManager->getGeometryCreator();

//	irr::scene::IMesh* plane = geomentryCreator->createPlaneMesh(irr::core::dimension2d<irr::f32>(100, 100), irr::core::dimension2d<irr::u32>(100, 100));
//	irr::scene::ISceneNode* ground = m_sceneManager->addMeshSceneNode(plane);
//	ground->setPosition(irr::core::vector3df(0, 0, 10));
//	plane->setMaterialFlag(irr::video::EMF_LIGHTING, false);    //This is important

//	m_sceneManager->addMeshSceneNode(plane);

	return true;
}

void GraphicSystem::loadResources()
{

}

void GraphicSystem::setupResources(void)
{

}

void GraphicSystem::deinitialize(void)
{
	if (!m_device)
		return;

	m_device->drop();

	m_driver = nullptr;
	m_sceneManager = nullptr;
	m_camera = nullptr;
	m_guiEnv = nullptr;

	m_device = nullptr;
}

void GraphicSystem::update()
{
	if (!m_driver || !m_sceneManager || !m_device)
		return;

	m_driver->beginScene(true, true, m_backgroundColour);

	m_sceneManager->drawAll(); // draw the 3d scene
	m_device->getGUIEnvironment()->drawAll(); // draw the gui environment (the logo)

	m_driver->endScene();

	int fps = m_driver->getFPS();

	if (lastFPS != fps)
	{
		irr::core::stringw tmp(L"�����");
		tmp += m_driver->getName();
		tmp += L"] fps: ";
		tmp += fps;

		m_device->setWindowCaption(tmp.c_str());
		lastFPS = fps;
	}

}

void GraphicSystem::chooseSceneManager()
{

}

void GraphicSystem::createCamera(void)
{
	m_camera = m_sceneManager->addCameraSceneNode();
	m_camera->setPosition(irr::core::vector3df(0, 0, 0));    //This is also important
	m_camera->setTarget(irr::core::vector3df(50, 50, 50));

	m_worldCamera = new WorldCamera(m_camera);

}

bool GraphicSystem::run()
{
	if (m_device)
		return m_device->run();

	return false;
}