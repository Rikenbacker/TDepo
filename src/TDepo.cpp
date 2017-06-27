#include <Windows.h>
#include <string>

#include "graphics\GraphicSystem.h"
#include "gameState\gameState.h"
#include "gameState\statePlay.h"

#include "OgreLogManager.h"

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

	Ogre::Timer timer;
	unsigned long startTime = timer.getMicroseconds();

	double timeSinceLast = 1.0 / 60.0;

	gameState *game = new statePlay(myGraphic);

	while (game->getState() != GAME_STATE_EXIT)
	{
		game->tick();

//		graphicsSystem.beginFrameParallel();
		myGraphic->update(static_cast<float>(timeSinceLast));
//		graphicsSystem.finishFrameParallel();
//		graphicsSystem.finishFrame();

		game->getState();

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
