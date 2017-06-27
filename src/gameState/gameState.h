#pragma once

#include "gameStateDefines.h"

#include "..\graphics\GraphicSystem.h"

class gameState
{
	public:
		gameState(GraphicSystem *gs);
		virtual ~gameState() = 0;

		virtual void tick() = 0;
		virtual int getState() = 0;
		virtual void sleep() = 0;

	protected:
		GraphicSystem *m_graphicSystem = NULL;
		int m_state = GAME_STATE_RUNNING;
};

