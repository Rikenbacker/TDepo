#include <Windows.h>
#include <string>

#include "graphics\GraphicSystem.h"
#include "graphics\InputSystem.h"
#include "gameState\gameState.h"
#include "gameState\statePlay.h"

void setActiveDir();

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR strCmdLine, INT nCmdShow)
{
	setActiveDir();
	SetDllDirectory(L"bin\\");

	GraphicSystem *graphicSystem = new GraphicSystem();
	
	graphicSystem->setConfigPath("config\\");
	graphicSystem->setLogPath("logs\\");
	graphicSystem->setResourcePath("data\\");
	
	if (!graphicSystem->initialize(L"Train Depo"))
	{
		graphicSystem->deinitialize();
		return -1;
	};

	InputSystem *inputSystem = new InputSystem(graphicSystem);

	gameState *game = new statePlay(graphicSystem, inputSystem);

	while (game->getState() != GameCondition::Exit)
	{
		inputSystem->update();

		game->tick();

//		graphicsSystem.beginFrameParallel();

		graphicSystem->update();
//		graphicsSystem.finishFrameParallel();
//		graphicsSystem.finishFrame();

		game->sleep();
	};


	graphicSystem->deinitialize();
	delete graphicSystem;
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
