cmake_minimum_required(VERSION 3.8)
project(TrainDepo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")

add_definitions(-DUNICODE -D_WIN64 -DWIN64)

include_directories(${PROJECT_SOURCE_DIR}/dependences/irrlicht-1.8.4/include)
include_directories(${PROJECT_SOURCE_DIR}/dependences/tinyxml-2.6.2)

add_subdirectory(dependences)
add_subdirectory(src)

add_executable(TrainDepo src/TDepo.cpp)

target_link_libraries(TrainDepo tinyxml)
target_link_libraries(TrainDepo irrlicht)
target_link_libraries(TrainDepo TrainDepo_library)