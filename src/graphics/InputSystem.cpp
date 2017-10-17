#include "InputSystem.h"

InputSystem::InputSystem()
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
}

InputSystem::~InputSystem()
{
}

bool InputSystem::OnEvent(const irr::SEvent& event)
{
	// Remember whether each key is down or up
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

	return false;
}

bool InputSystem::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}

void InputSystem::update()
{/*
	SDL_Event evt;
	while (SDL_PollEvent(&evt))
	{
		switch (evt.type)
		{
			case SDL_WINDOWEVENT:
				handleWindowEvent(evt);
				break;

			case SDL_QUIT:
				m_quit = true;
				break;

			default:
				break;
		};

		m_sdlInputHandler->_handleSdlEvents(evt);
	}

	//SDL_SetWindowPosition( mSdlWindow, 0, 0 );
	*/
}
/*
void InputSystem::handleWindowEvent(const SDL_Event& evt)
{
	
	switch (evt.window.event)
	{
		case SDL_WINDOWEVENT_MAXIMIZED:
			//SDL_SetWindowBordered( m_sdlWindow, SDL_FALSE );
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
		case SDL_WINDOWEVENT_RESTORED:
			//SDL_SetWindowBordered( m_sdlWindow, SDL_TRUE );
			break;
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			int w, h;
			SDL_GetWindowSize(m_sdlWindow, &w, &h);
//			m_graphicSystem->getRenderWindow()->windowMovedOrResized();
			break;
		case SDL_WINDOWEVENT_RESIZED:
//			m_graphicSystem->getRenderWindow()->windowMovedOrResized();
			break;
		case SDL_WINDOWEVENT_CLOSE:
			break;
		case SDL_WINDOWEVENT_SHOWN:
//			m_graphicSystem->getRenderWindow()->setVisible(true);
			break;
		case SDL_WINDOWEVENT_HIDDEN:
//			m_graphicSystem->getRenderWindow()->setVisible(false);
			break;
	}
	
}

void InputSystem::addListener(InputEventsType type, SDLEventCallback funct)
{
	m_sdlInputHandler->addListener(type, funct);
}
void InputSystem::addListener(InputEventsType type, MouseMoveEventCallback funct)
{
	m_sdlInputHandler->addListener(type, funct);
}

void InputSystem::removeListener(event, listener)
{

}*/