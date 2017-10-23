#pragma once

#include <irrlicht.h>
#include "..\common\Vector3DFloat.h"
#include "..\common\CameraState.h"

#include <map>

class WorldCamera
{
	public:
		WorldCamera(irr::scene::ICameraSceneNode* camera);
		~WorldCamera();

		CameraState getState(void);
		void setState(CameraState);

		void rotateCamera(TDC::Vector3DFloat);
		void moveCamera(TDC::Vector3DFloat);

		void rotateCameraTo(TDC::Vector3DFloat);
		void moveCameraTo(TDC::Vector3DFloat);
		void setDirection(TDC::Vector3DFloat);
		void setPosition(TDC::Vector3DFloat);

	private:
		irr::scene::ICameraSceneNode* m_camera = nullptr;
		CameraState m_state = CameraState::Free;

		void rotateCameraFree(const int &deltaX, const int &deltaY, const unsigned long &ticks);
		void rotateCameraFollow(const int &deltaX, const int &deltaY, const unsigned long &ticks);

		void moveCameraFree(const TDC::Vector3DFloat &delta, const unsigned long &ticks);
		void moveCameraFollow(const TDC::Vector3DFloat &delta, const unsigned long &ticks);

		//Направление камеры x - угол xy, y - угол yz, z - угол xz
		TDC::Vector3DFloat direction;
		TDC::Vector3DFloat position;

		float range = 50;
};

