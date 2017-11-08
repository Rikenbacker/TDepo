#pragma once

#include "gameState.h"
#include "gameStateDefines.h"
#include "..\objects\RailSystem.h"
#include "..\common\Vector2D.h"
#include "..\objects\BaseGameObject.h"

class statePlay : public gameState
{
	public:
		statePlay(GraphicSystem *gs, InputSystem *i);
		~statePlay();

		void tick() override;
		GameCondition getState() override;
		void sleep() override;

		//—сылка на железнодорожную систему
		RailSystem *getRailSystem();

		//—сылка на камеру
		WorldCamera *getCamera();

//		void OnMouseWheelScroll(LSDLEvent *evt);
//		void OnMouseClick(LSDLEvent *evt);
//		void OnKeyPressed(LSDLEvent *evt);
//		void OnMouseMove(TDC::Vector2D<unsigned int>*, TDC::Vector2D<unsigned int>*, TDC::MouseButtons *);

	private:
		void setState(GameCondition cond);
		RailSystem m_railSystem;

		BaseGameObject *cube;
        irr::gui::IGUIStaticText* txt;
        irr::scene::ILightSceneNode*  pLight;
        float dz = 0.01f;
};

