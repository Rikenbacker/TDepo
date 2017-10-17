#pragma once

#include <irrlicht.h>
#include "..\graphics\GraphicSystem.h"

class BaseGameObject
{
	public:
		BaseGameObject(GraphicSystem *graphicSystem);
		~BaseGameObject();

		void move(float x, float y, float z);
		void moveTo(float x, float y, float z);

	private:
		irr::scene::ISceneNode* m_body;
};

