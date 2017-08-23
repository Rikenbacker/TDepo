#pragma once

#include <irrlicht.h>

#include <string>
//#include <SDL2\SDL.h>

class GraphicSystem
{
	public:
		GraphicSystem(irr::video::SColor backgroundColour = irr::video::SColor(255, 0, 255, 0));
		~GraphicSystem();

		bool initialize(const std::string &windowTitle);
		void deinitialize();

		void setConfigPath(std::string);
		void setLogPath(std::string);
		void setResourcePath(std::string);

//		Ogre::RenderWindow* getRenderWindow(void) const { return m_renderWindow; }
		void GraphicSystem::update();

		irr::scene::ISceneManager *getSceneManager() const { return m_sceneManager; }
//		SDL_Window *getSdlWindow() const { return m_sdlWindow; }
//		Ogre::Camera *getCamera() const { return m_camera; }

	private:
//		Ogre::Root *m_root = nullptr;

		std::string m_configPath = "";
		std::string m_logPath = "";
		std::string m_resourcePath = "";

//		SDL_Window *m_sdlWindow = nullptr;
//		Ogre::RenderWindow *m_renderWindow = nullptr;
//		Ogre::v1::OverlaySystem *m_overlaySystem = nullptr;
		irr::scene::ISceneManager *m_sceneManager = nullptr;
//		Ogre::Camera *m_camera = nullptr;
//		Ogre::CompositorWorkspace *m_workspace = nullptr;

		irr::IrrlichtDevice* m_device = nullptr;
		irr::video::IVideoDriver* m_driver = nullptr;
		irr::video::SColor m_backgroundColour;

		void chooseSceneManager();
		void createCamera();
		void setupResources();
//		Ogre::CompositorWorkspace* setupCompositor();
		void loadResources();
		void registerHlms();
};

