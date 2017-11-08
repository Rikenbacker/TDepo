#pragma once

#include <irrlicht.h>
#include "..\graphics\GraphicSystem.h"

class BaseGameObject
{
	public:
		BaseGameObject() = default;
		virtual ~BaseGameObject();

		void move(TDC::Vector3DFloat);
		void moveTo(TDC::Vector3DFloat);
        TDC::Vector3DFloat *const getPosition();

    protected:
		irr::scene::ISceneNode* sceneNode = nullptr;
        TDC::Vector3DFloat position;
};