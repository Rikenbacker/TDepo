#include "gameState.h"

gameState::gameState(GraphicSystem *gs, InputSystem *is)
{
	m_graphicSystem = gs;
	m_inputSystem = is;
}


gameState::~gameState()
{
}

void gameState::tick()
{

}