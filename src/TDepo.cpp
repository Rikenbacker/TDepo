#include <Windows.h>
#include <string>

#include "graphics\GraphicSystem.h"
#include "OgreLogManager.h"
#include "OgreSceneManager.h"
#include "OgreItem.h"

void setActiveDir();

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR strCmdLine, INT nCmdShow)
{
	setActiveDir();
	SetDllDirectory(L"bin\\");

	GraphicSystem *myGraphic = new GraphicSystem();
	
	myGraphic->setConfigPath("config\\");
	myGraphic->setLogPath("logs\\");
	myGraphic->setResourcePath("data\\");
	
	if (!myGraphic->initialize("Train Depo"))
	{
		myGraphic->deinitialize();
		return -1;
	};

	Ogre::RenderWindow *renderWindow = myGraphic->getRenderWindow();

	Ogre::Item *item = myGraphic->getSceneManager()->createItem("ogrehead.mesh", Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME, Ogre::SCENE_DYNAMIC);
	Ogre::SceneNode *sceneNode = myGraphic->getSceneManager()->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);
	sceneNode->attachObject(item);
	/*
	Ogre::Light *light = myGraphic->getSceneManager()->createLight();
	Ogre::SceneNode *lightNode = myGraphic->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	lightNode->attachObject(light);
	light->setPowerScale(Ogre::Math::PI); //Since we don't do HDR, counter the PBS' division by PI
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(-1, -1, -1).normalisedCopy());*/

	myGraphic->getSceneManager()->setAmbientLight(Ogre::ColourValue::White, Ogre::ColourValue::White, Ogre::Vector3::UNIT_Y);


	Ogre::Timer timer;
	unsigned long startTime = timer.getMicroseconds();

	double timeSinceLast = 1.0 / 60.0;

	while (true)
	{
//		graphicsSystem.beginFrameParallel();
		myGraphic->update(static_cast<float>(timeSinceLast));
//		graphicsSystem.finishFrameParallel();
//		graphicsSystem.finishFrame();

		if (!renderWindow->isVisible())
		{
			//Don't burn CPU cycles unnecessary when we're minimized.
			Ogre::Threads::Sleep(500);
		}

		unsigned long endTime = timer.getMicroseconds();
		timeSinceLast = (endTime - startTime) / 1000000.0;
		timeSinceLast = std::min(1.0, timeSinceLast); //Prevent from going haywire.
		startTime = endTime;
	};


	myGraphic->deinitialize();
	delete myGraphic;
	return 0;
}

void setActiveDir()
{
	wchar_t path[MAX_PATH];

	GetModuleFileName(GetModuleHandle(NULL), path, MAX_PATH);
	std::wstring path_in_string = path;
	path_in_string = path_in_string.substr(0, path_in_string.find_last_of(L"\\bin\\") - 4);

	SetCurrentDirectory(path_in_string.c_str());
}
