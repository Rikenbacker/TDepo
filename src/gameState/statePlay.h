#pragma once

#include "gameState.h"
#include "gameStateDefines.h"

class statePlay : public gameState
{
	public:
		statePlay(GraphicSystem *gs, InputSystem *i);
		~statePlay();

		void tick() override;
		GameCondition getState() override;
		void sleep() override;

		void OnMouseWheelScroll(LSDLEvent *evt);
		void OnMouseClick(LSDLEvent *evt);
		void OnKeyPressed(LSDLEvent *evt);

	private:
		void setState(GameCondition cond);
};

