#pragma once

#include <irrlicht.h>

#include <string>
//#include <SDL2\SDL.h>

class GraphicSystem
{
	public:
		GraphicSystem(irr::video::SColor backgroundColour = irr::video::SColor(255, 0, 255, 0));
		~GraphicSystem();

		bool initialize(const std::wstring &windowTitle);
		void deinitialize();

		void setConfigPath(std::string);
		void setLogPath(std::string);
		void setResourcePath(std::string);

		void GraphicSystem::update();

		irr::scene::ISceneManager *getSceneManager() const { return m_sceneManager; }

	private:

		std::string m_configPath = "";
		std::string m_logPath = "";
		std::string m_resourcePath = "";

		irr::scene::ISceneManager *m_sceneManager = nullptr;

		irr::IrrlichtDevice* m_device = nullptr;
		irr::video::IVideoDriver* m_driver = nullptr;
		irr::gui::IGUIEnvironment* m_guiEnv = nullptr;
		irr::video::SColor m_backgroundColour;
		irr::scene::ICameraSceneNode* m_camera = nullptr;

		void chooseSceneManager();
		void createCamera();
		void setupResources();
		void loadResources();
};

