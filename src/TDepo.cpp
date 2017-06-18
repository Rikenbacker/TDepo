#include<Windows.h>

#include "graphics\GraphicSystem.h"

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR strCmdLine, INT nCmdShow)
{
	GraphicSystem *myGraphic = new GraphicSystem();


	delete myGraphic;
	return 0;
}