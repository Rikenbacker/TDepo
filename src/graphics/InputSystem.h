#pragma once

#include "SdlInputHandler.h"
#include "GraphicSystem.h"

class InputSystem
{
	public:
		InputSystem(GraphicSystem *graphicSystem);
		~InputSystem();

		void update();
		bool isQuit() { return m_quit; }

		void removeListener(/*event, listener*/);

		void addListener(InputEventsType type, SDLEventCallback funct);

	private:
		SdlInputHandler *m_sdlInputHandler = nullptr;
		GraphicSystem *m_graphicSystem = nullptr;
		SDL_Window *m_sdlWindow = nullptr;
		bool m_quit = false;

		void handleWindowEvent(const SDL_Event& evt);
};

