#include "WorldCamera.h"

WorldCamera::WorldCamera(irr::scene::ICameraSceneNode* camera)
{
	m_camera = camera;
}


WorldCamera::~WorldCamera()
{
}

CameraState WorldCamera::getState()
{
	return m_state;
}

void WorldCamera::setState(CameraState state)
{
	m_state = state;
}

void WorldCamera::rotateCamera(TDC::Vector3DFloat delta)
{
    switch (m_state)
    {
        case CameraState::Free:
            rotateCameraFree(&delta);
            break;
        case CameraState::Follow:
            rotateCameraFollow(&delta);
            break;
        default:
            break;
    };
}

void WorldCamera::rotateCameraTo(TDC::Vector3DFloat angle)
{
    direction = angle;
    float dx = range * cos(direction.y) * sin(direction.z);
    float dy = range * cos(direction.z);
    float dz = range * sin(direction.y);
    TDC::Vector3DFloat target(position.x + dx, position.y + dy, position.z + dz);
    m_camera->setTarget(target.getIrr3df());
}

void WorldCamera::moveCamera(TDC::Vector3DFloat delta)
{
    switch (m_state)
    {
        case CameraState::Free:
            moveCameraFree(&delta);
            break;
        case CameraState::Follow:
            moveCameraFollow(&delta);
            break;
        default:
            break;
    };
}

void WorldCamera::moveCameraTo(const TDC::Vector3DFloat newPos)
{
    position = newPos;
    m_camera->setPosition(position.getIrr3df());
}

void WorldCamera::rotateCameraFree(TDC::Vector3DFloat *delta)
{
    delta->add(direction);

    rotateCameraTo(*delta);
}

void WorldCamera::rotateCameraFollow(TDC::Vector3DFloat *delta)
{

}

void WorldCamera::moveCameraFree(TDC::Vector3DFloat *delta)
{
    delta->add(position);

    moveCameraTo(*delta);
    rotateCameraTo(direction);
}

void WorldCamera::moveCameraFollow(TDC::Vector3DFloat *delta)
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

TDC::Vector3DFloat WorldCamera::getPosition()
{
    return TDC::Vector3DFloat(m_camera->getPosition());
}

TDC::Vector3DFloat WorldCamera::getTarget()
{
    return TDC::Vector3DFloat(m_camera->getTarget());
}
