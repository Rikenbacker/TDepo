#ifndef CAMERASTATE_H
#define CAMERASTATE_H

#include <map>
#include <string>

enum class CameraState { Free, Follow };
typedef std::map<const std::wstring, CameraState> CameraStateMap_t;
static CameraStateMap_t CameraStateMap =
{
	{ L"Free", CameraState::Free},
	{ L"Follow", CameraState::Follow }
};

#endif