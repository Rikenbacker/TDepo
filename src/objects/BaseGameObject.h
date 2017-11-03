#pragma once

#include <irrlicht.h>
#include "..\graphics\GraphicSystem.h"

class BaseGameObject
{
	public:
		BaseGameObject();
		virtual ~BaseGameObject();

		void move(TDC::Vector3DFloat);
		void moveTo(TDC::Vector3DFloat);

    protected:
		irr::scene::ISceneNode* sceneNode = nullptr;
        TDC::Vector3DFloat position;
};

