#include "InputListeners.h"

void LSDLEvent::callFirst(const SDL_Event& _env)
{
	env = &_env; 
	m_it = m_listeners.end();
	callNext();
}
void LSDLEvent::addListener(SDLEventCallback _listener)
{
	m_listeners.push_back(_listener);
}

void LSDLEvent::callNext()
{
	if (m_it != m_listeners.begin())
	{
		m_it--;
		call();
	};
}

void LSDLEvent::call()
{
	if (m_it != m_listeners.end())
		((SDLEventCallback)*m_it)(this);
};