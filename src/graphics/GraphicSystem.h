#pragma once

#include "Ogre.h"
#include "Overlay\OgreOverlayPrerequisites.h"

#include <string>
#include <SDL2\SDL.h>

class GraphicSystem
{
	public:
		GraphicSystem(Ogre::ColourValue backgroundColour = Ogre::ColourValue(0.2f, 0.4f, 0.6f));
		~GraphicSystem();

		bool initialize(const std::string &windowTitle);
		void deinitialize();

		void setConfigPath(std::string);
		void setLogPath(std::string);
		void setResourcePath(std::string);

		Ogre::RenderWindow* getRenderWindow(void) const { return m_renderWindow; }
		void GraphicSystem::update(float);

		Ogre::SceneManager *getSceneManager() const { return m_sceneManager; }

	private:
		Ogre::Root *m_root = nullptr;

		std::string m_configPath = "";
		std::string m_logPath = "";
		std::string m_resourcePath = "";

		SDL_Window *m_sdlWindow = nullptr;
		Ogre::RenderWindow *m_renderWindow = nullptr;
		Ogre::v1::OverlaySystem *m_overlaySystem = nullptr;
		Ogre::SceneManager *m_sceneManager = nullptr;
		Ogre::Camera *m_camera = nullptr;
		Ogre::CompositorWorkspace *m_workspace = nullptr;

		Ogre::ColourValue m_backgroundColour;

		void chooseSceneManager();
		void createCamera();
		void setupResources();
		Ogre::CompositorWorkspace* setupCompositor();
		void loadResources();
		void registerHlms();
		static void addResourceLocation(const Ogre::String &archName, const Ogre::String &typeName, const Ogre::String &secName);
};

