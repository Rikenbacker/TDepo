#include "WorldCamera.h"



WorldCamera::WorldCamera(Ogre::Camera *camera)
{
	m_camera = camera;
}


WorldCamera::~WorldCamera()
{
}

WorldCamera::CameraState WorldCamera::getState(void)
{
	return m_state;
}

void WorldCamera::setState(WorldCamera::CameraState state)
{
	m_state = state;
}

void WorldCamera::rotateCamera(const int deltaX, const int deltaY, const unsigned long ticks)
{
	switch (m_state)
	{
		case CameraState::Follow:
			rotateCameraFollow(deltaX, deltaY, ticks);
			break;
		case CameraState::Free:
			rotateCameraFree(deltaX, deltaY, ticks);
			break;
		default:
			break;
	};
}

void WorldCamera::moveCamera(const TDC::Vector3DFloat delta, const unsigned long ticks)
{
	switch (m_state)
	{
	case CameraState::Follow:
		moveCameraFollow(delta, ticks);
		break;
	case CameraState::Free:
		moveCameraFree(delta, ticks);
		break;
	default:
		break;
	};
}

void WorldCamera::rotateCameraFree(const int &deltaX, const int &deltaY, const unsigned long &ticks)
{
	if (deltaX != 0)
	{
		float tsx = (float)deltaX / (float)ticks;
		m_camera->rotate(Ogre::Vector3(0, 1, 0), (Ogre::Radian)tsx);
	};

	if (deltaY != 0)
	{
		float tsy = (float)-deltaY / (float)ticks;
		m_camera->rotate(Ogre::Vector3(1, 0, 0), (Ogre::Radian)tsy);
	};
}

void WorldCamera::rotateCameraFollow(const int &deltaX, const int &deltaY, const unsigned long &ticks)
{

}

void WorldCamera::moveCameraFree(const TDC::Vector3DFloat &delta, const unsigned long &ticks)
{
}

void WorldCamera::moveCameraFollow(const TDC::Vector3DFloat &delta, const unsigned long &ticks)
{
}
