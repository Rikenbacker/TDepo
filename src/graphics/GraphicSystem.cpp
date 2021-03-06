#include "GraphicSystem.h"
#include "../resources/ResourceLoader.h"

GraphicSystem::GraphicSystem(irr::video::SColor backgroundColour) :
	m_backgroundColour(backgroundColour)
{
}

GraphicSystem::~GraphicSystem()
{
    if (resources)
    {
        delete resources;
        resources = nullptr;
    };

    deinitialize();
}

void GraphicSystem::setConfigPath(std::string configPath)
{
	m_configPath = configPath;
}

void GraphicSystem::setLogPath(std::string logPath)
{
	m_logPath = logPath;
}

void GraphicSystem::setResourcePath(std::wstring resourcePath)
{
	m_resourcePath = resourcePath;
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

	return true;
}

void GraphicSystem::loadResources()
{
    if (resources)
    {
        resources->clear();
        delete resources;
    };

    ResourceLoader loader(m_resourcePath);
    resources = loader.load();
}

void GraphicSystem::setupResources()
{

}

void GraphicSystem::deinitialize()
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

irr::gui::IGUIEnvironment *GraphicSystem::getGuiEnvironment()
{
    return m_guiEnv;
}

ResourcesStorage *GraphicSystem::getResources()
{
    return resources;
}
