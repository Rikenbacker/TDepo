cmake_minimum_required(VERSION 3.8)
project(TrainDepo_library)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexec-charset=windows-1251")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finput-charset=windows-1251")

set(SOURCE_FILES
        common/MouseButtons.h
        common/Ray3D.cpp
        common/Ray3D.h
        common/Vector2D.h
        common/Vector3D.h
        common/Vector3DFloat.cpp
        common/Vector3DFloat.h
        exceptions/FileSystemException.cpp
        exceptions/FileSystemException.h
        exceptions/TDepoException.cpp
        exceptions/TDepoException.h
        exceptions/XMLException.cpp
        exceptions/XMLException.h
        exceptions/ConvertException.cpp
        exceptions/ConvertException.h
        gameState/gameState.cpp
        gameState/gameState.h
        gameState/gameStateDefines.h
        gameState/saveGame.cpp
        gameState/saveGame.h
        gameState/statePlay.cpp
        gameState/statePlay.h
        graphics/GraphicSystem.cpp
        graphics/GraphicSystem.h
        graphics/InputListeners.cpp
        graphics/InputListeners.h
        graphics/InputSystem.cpp
        graphics/InputSystem.h
        graphics/WorldCamera.cpp
        graphics/WorldCamera.h
        graphics/WorldTimer.cpp
        graphics/WorldTimer.h
        objects/BaseGameObject.cpp
        objects/BaseGameObject.h
        objects/RailConnector.cpp
        objects/RailConnector.h
        objects/Rails.cpp
        objects/Rails.h
        objects/RailSystem.cpp
        objects/RailSystem.h
        objects/RailWay.cpp
        objects/RailWay.h
        objects/SaveGameLinkers/ConnectorPair.cpp
        objects/SaveGameLinkers/ConnectorPair.h
        objects/SaveGameLinkers/ConnectorPairLinker.cpp
        objects/SaveGameLinkers/ConnectorPairLinker.h
        common/StringConvertors.h
        common/StringConvertors.cpp
        objects/SimpleCube.cpp
        objects/SimpleCube.h
        objects/RailMesh.cpp
        objects/RailMesh.h
        resources/resourcesStorage.cpp
        resources/resourcesStorage.h
        resources/ProceduralProfile.cpp
        resources/ProceduralProfile.h
        resources/ResourceLoader.cpp
        resources/ResourceLoader.h
        common/FileSystem.cpp
        common/FileSystem.h
        common/Vector2DFloat.cpp
        common/Vector2DFloat.h
        exceptions/ResourcesException.cpp
        exceptions/ResourcesException.h
        common/GraphicMath.cpp
        common/GraphicMath.h exceptions/ArrayException.cpp exceptions/ArrayException.h)

add_library(TrainDepo_library STATIC ${SOURCE_FILES})