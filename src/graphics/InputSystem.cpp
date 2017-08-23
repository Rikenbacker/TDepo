#include "InputSystem.h"

InputSystem::InputSystem(GraphicSystem *graphicSystem)
{
	/*
	m_graphicSystem = graphicSystem;
	m_sdlWindow = m_graphicSystem->getSdlWindow();

	m_sdlInputHandler = new SdlInputHandler(m_sdlWindow);
	*/
}

InputSystem::~InputSystem()
{
	/*
	if (m_sdlInputHandler)
		delete m_sdlInputHandler;
		*/
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