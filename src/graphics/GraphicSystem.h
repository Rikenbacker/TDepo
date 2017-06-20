#pragma once

#include "Ogre.h"
#include "Overlay\OgreOverlayPrerequisites.h"

#include <string>
#include <SDL2\SDL.h>

class GraphicSystem
{
	public:
		GraphicSystem();
		~GraphicSystem();

		bool initialize(const std::string &windowTitle);
		void deinitialize();

		void setConfigPath(std::string);
		void setLogPath(std::string);
		void setPluginPath(std::string);

		Ogre::RenderWindow* getRenderWindow(void) const { return m_renderWindow; }

	private:
		Ogre::Root *m_root = nullptr;

		std::string m_configPath = "";
		std::string m_logPath = "";
		std::string m_pluginPath = "";

		SDL_Window *m_sdlWindow = nullptr;
		Ogre::RenderWindow *m_renderWindow = nullptr;
		Ogre::v1::OverlaySystem *m_overlaySystem = nullptr;

};

