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

void MouseMoveEvent::callFirst(TDC::Vector2D<unsigned int> *position, TDC::Vector2D<unsigned int> *relation, TDC::MouseButtons *btns)
{
	m_position = position;
	m_relation = relation;
	m_btns = btns;

	m_it = m_listeners.end();
	callNext();
}

void MouseMoveEvent::callNext()
{
	if (m_it != m_listeners.begin())
	{
		m_it--;
		call();
	};
}

void MouseMoveEvent::addListener(MouseMoveEventCallback _listener)
{
	m_listeners.push_back(_listener);
}

void MouseMoveEvent::call()
{
	if (m_it != m_listeners.end())
		((MouseMoveEventCallback)*m_it)(m_position, m_relation, m_btns);
}
