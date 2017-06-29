#include "gameState.h"

gameState::gameState(GraphicSystem *gs, InputSystem *is)
{
	m_graphicSystem = gs;
	m_inputSystem = is;

	if (m_graphicSystem)
		m_camera = new WorldCamera(m_graphicSystem->getCamera());

	m_timer = new WorldTimer();
}


gameState::~gameState()
{
	if (m_timer)
		delete m_timer;
}

void gameState::tick()
{

}