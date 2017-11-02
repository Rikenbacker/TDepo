#pragma once

#include <irrlicht.h>
#include "..\common\Vector3DFloat.h"
#include "..\common\CameraState.h"

#include <map>

class WorldCamera
{
	public:
        explicit WorldCamera(irr::scene::ICameraSceneNode* camera);
		~WorldCamera();

		CameraState getState();
		void setState(CameraState);

		void rotateCamera(TDC::Vector3DFloat);
		void moveCamera(TDC::Vector3DFloat);

		void rotateCameraTo(TDC::Vector3DFloat);
		void moveCameraTo(TDC::Vector3DFloat);
		void setDirection(TDC::Vector3DFloat);
		void setPosition(TDC::Vector3DFloat);

        TDC::Vector3DFloat getPosition();
        TDC::Vector3DFloat getTarget();

    private:
		irr::scene::ICameraSceneNode* m_camera = nullptr;
		CameraState m_state = CameraState::Free;

		void rotateCameraFree(TDC::Vector3DFloat *);
		void rotateCameraFollow(TDC::Vector3DFloat *);

		void moveCameraFree(TDC::Vector3DFloat *);
		void moveCameraFollow(TDC::Vector3DFloat *);

		//Направление камеры x - угол поворота камеры вокруг своей оси, y - в плоскости xz, z - угол в плоскости xy
        //Работает только для вида Free
		TDC::Vector3DFloat direction;
		TDC::Vector3DFloat position;

		float range = 50;
};

