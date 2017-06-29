#pragma once

#include "Ogre.h"

class WorldCamera
{
	public:
		enum class CameraState { Free, Follow };

	public:
		WorldCamera(Ogre::Camera *camera);
		~WorldCamera();

		CameraState getState(void);
		void setState(CameraState);

		void rotateCamera(const int deltaX, const int deltaY, const unsigned long ticks);

	private:
		Ogre::Camera *m_camera = nullptr;
		CameraState m_state = CameraState::Free;

		void rotateCameraFree(const int deltaX, const int deltaY, const unsigned long &ticks);
		void rotateCameraFollow(const int deltaX, const int deltaY, const unsigned long &ticks);
};

