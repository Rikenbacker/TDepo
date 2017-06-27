#pragma once

#include "gameState.h"

class statePlay : public gameState
{
	public:
		statePlay(GraphicSystem *gs);
		~statePlay();

		void tick() override;
		int getState() override;
		void sleep() override;
};

