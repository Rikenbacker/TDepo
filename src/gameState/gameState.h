#pragma once

#include "gameStateDefines.h"

#include "..\graphics\GraphicSystem.h"
#include "..\graphics\InputSystem.h"

class gameState
{
	public:
		gameState(GraphicSystem *gs, InputSystem *is);
		virtual ~gameState() = 0;

		virtual void tick() = 0;
		virtual GameCondition getState() = 0;
		virtual void sleep() = 0;

	protected:
		GraphicSystem *m_graphicSystem = nullptr;
		InputSystem *m_inputSystem = nullptr;
		GameCondition m_state = GameCondition::Loading;
};

