#include <Windows.h>
#include <string>

#include "graphics\GraphicSystem.h"
#include "graphics\InputSystem.h"
#include "gameState\gameState.h"
#include "gameState\statePlay.h"
#include "gameState\saveGame.h"

void setActiveDir();

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR strCmdLine, INT nCmdShow)
{
	setActiveDir();
	SetDllDirectory(L"bin\\");

	GraphicSystem *graphicSystem = new GraphicSystem();
	
	graphicSystem->setConfigPath("config\\");
	graphicSystem->setLogPath("logs\\");
	graphicSystem->setResourcePath("data\\");
	InputSystem *inputSystem = new InputSystem();

	if (!graphicSystem->initialize(L"Train Depo", inputSystem, false))
	{
		graphicSystem->deinitialize();
		return -1;
	};

	saveGame *gameLoader = new saveGame(graphicSystem, inputSystem);
	gameState *game = gameLoader->load("Test001");

	while (game->getState() != GameCondition::Exit && graphicSystem->run())
	{
		inputSystem->update();

		game->tick();

		graphicSystem->update();

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
