#include "WorldCamera.h"

#include <math.h> 

WorldCamera::WorldCamera(irr::scene::ICameraSceneNode* camera)
{
	m_camera = camera;
}


WorldCamera::~WorldCamera()
{
}

CameraState WorldCamera::getState(void)
{
	return m_state;
}

void WorldCamera::setState(CameraState state)
{
	m_state = state;
}

void WorldCamera::rotateCamera(TDC::Vector3DFloat delta)
{
	delta.add(direction);

	rotateCameraTo(delta);
	/*
	irr::core::vector3df rot = m_camera->getTarget();
	rot.X += deltaX;
	rot.Y += deltaY;
	rot.Z += deltaZ;
	m_camera->setTarget(rot);
	*/
/*
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
	*/
}

void WorldCamera::rotateCameraTo(TDC::Vector3DFloat angle)
{
	switch (m_state)
	{
		case CameraState::Free:
			{
				direction = angle;
				float dx = range * cos(direction.x);
				float dy = range * cos(direction.y);
				float dz = range * cos(direction.z);
				TDC::Vector3DFloat target(position.x + dx, position.y + dy, position.z + dz);
				m_camera->setTarget(target.getIrr3df());
			};
			break;
		case CameraState::Follow:
			break;
		default:
			break;
	};
}

void WorldCamera::moveCamera(const TDC::Vector3DFloat delta)
{
	/*
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
	};*/
}

void WorldCamera::moveCameraTo(const TDC::Vector3DFloat newPos)
{
	m_camera->setPosition(irr::core::vector3df(newPos.x, newPos.y, newPos.z));
}

void WorldCamera::rotateCameraFree(const int &deltaX, const int &deltaY, const unsigned long &ticks)
{
	if (deltaX != 0)
	{
		float tsx = (float)deltaX / (float)ticks;
//		m_camera->rotate(Ogre::Vector3(0, 1, 0), (Ogre::Radian)tsx);
	};

	if (deltaY != 0)
	{
		float tsy = (float)-deltaY / (float)ticks;
//		m_camera->rotate(Ogre::Vector3(1, 0, 0), (Ogre::Radian)tsy);
	};
}

void WorldCamera::rotateCameraFollow(const int &deltaX, const int &deltaY, const unsigned long &ticks)
{

}

void WorldCamera::moveCameraFree(const TDC::Vector3DFloat &delta, const unsigned long &ticks)
{
//	m_camera->moveRelative(delta.toOgreVector());
}

void WorldCamera::moveCameraFollow(const TDC::Vector3DFloat &delta, const unsigned long &ticks)
{
}

void WorldCamera::setDirection(TDC::Vector3DFloat direction)
{
	this->direction = direction;
	rotateCamera(TDC::Vector3DFloat(0.0, 0.0, 0.0));
}

void WorldCamera::setPosition(TDC::Vector3DFloat position)
{
	this->position = position;
	moveCamera(TDC::Vector3DFloat(0.0, 0.0, 0.0));
}
