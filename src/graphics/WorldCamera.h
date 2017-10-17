#pragma once

#include <irrlicht.h>
#include "..\common\Vector3D.h"

class WorldCamera
{
	public:
		enum class CameraState { Free, Follow };

	public:
		WorldCamera(irr::scene::ICameraSceneNode* camera);
		~WorldCamera();

		CameraState getState(void);
		void setState(CameraState);

		void rotateCamera(const int deltaX, const int deltaY, const unsigned long ticks);
		void moveCamera(const TDC::Vector3DFloat delta, const unsigned long ticks);

	private:
		irr::scene::ICameraSceneNode* m_camera = nullptr;
		CameraState m_state = CameraState::Free;

		void rotateCameraFree(const int &deltaX, const int &deltaY, const unsigned long &ticks);
		void rotateCameraFollow(const int &deltaX, const int &deltaY, const unsigned long &ticks);

		void moveCameraFree(const TDC::Vector3DFloat &delta, const unsigned long &ticks);
		void moveCameraFollow(const TDC::Vector3DFloat &delta, const unsigned long &ticks);
};

