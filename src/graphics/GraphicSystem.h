#pragma once

#include <irrlicht.h>

#include <string>
#include "InputSystem.h"
#include "WorldCamera.h"
#include "../resources/resourcesStorage.h"

class GraphicSystem
{
	public:
		GraphicSystem(irr::video::SColor backgroundColour = irr::video::SColor(255, 0, 255, 0));
		~GraphicSystem();

		bool initialize(const std::wstring &windowTitle, InputSystem *inputSystem, bool fullScreen = false);
		void deinitialize();

		void setConfigPath(std::string);
		void setLogPath(std::string);
		void setResourcePath(std::wstring);

		void update();
		bool run();

		irr::scene::ISceneManager *getSceneManager() const { return m_sceneManager; }
        irr::gui::IGUIEnvironment* getGuiEnvironment();
        WorldCamera *getCamera() const { return m_worldCamera; }

        //Загрузка внешних ресурсов игры
        void loadResources();

        ResourcesStorage *getResources();

	private:

		std::string m_configPath = "";
		std::string m_logPath = "";
		std::wstring m_resourcePath = L"";

		irr::scene::ISceneManager *m_sceneManager = nullptr;

		irr::IrrlichtDevice* m_device = nullptr;
		irr::video::IVideoDriver* m_driver = nullptr;
		irr::gui::IGUIEnvironment* m_guiEnv = nullptr;
		irr::video::SColor m_backgroundColour;
		irr::scene::ICameraSceneNode* m_camera = nullptr;
		WorldCamera *m_worldCamera = nullptr;

		void chooseSceneManager();
		void createCamera();
		void setupResources();

		int lastFPS = 0;
        ResourcesStorage *resources = nullptr;
};

