cmake_minimum_required(VERSION 3.8)
project(TrainDepo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
set (PROJECTNAME_ARCHITECTURE "x64")

add_definitions(-DUNICODE -D_WIN64 -DWIN64 -DTIXML_USE_STL -D_IRR_STATIC_LIB_ -D_STDCALL_SUPPORTED -D__CYGWIN__ -DIRR_COMPILE_WITH_DX9_DEV_PACK)

include_directories(${PROJECT_SOURCE_DIR}/dependences/irrlicht-1.8.4/include)
include_directories(${PROJECT_SOURCE_DIR}/dependences/tinyxml-2.6.2/include)

add_subdirectory(dependences)
add_subdirectory(src)

# DirectX SDK
find_path (DirectX_ROOT_DIR
        Include/d3d9.h
        PATHS
        "$ENV{DXSDK_DIR}"
        "$ENV{ProgramFiles}/Microsoft DirectX SDK (June 2010)"
        "$ENV{ProgramFiles\(x86\)}/Microsoft DirectX SDK (June 2010)"
        "$ENV{ProgramFiles}/Microsoft DirectX SDK (February 2010)"
        "$ENV{ProgramFiles\(x86\)}/Microsoft DirectX SDK (February 2010)"
        "$ENV{ProgramFiles}/Microsoft DirectX SDK (March 2009)"
        "$ENV{ProgramFiles\(x86\)}/Microsoft DirectX SDK (March 2009)"
        "$ENV{ProgramFiles}/Microsoft DirectX SDK (August 2008)"
        "$ENV{ProgramFiles\(x86\)}/Microsoft DirectX SDK (August 2008)"
        "$ENV{ProgramFiles}/Microsoft DirectX SDK (June 2008)"
        "$ENV{ProgramFiles\(x86\)}/Microsoft DirectX SDK (June 2008)"
        "$ENV{ProgramFiles}/Microsoft DirectX SDK (March 2008)"
        "$ENV{ProgramFiles\(x86\)}/Microsoft DirectX SDK (March 2008)"
        "$ENV{ProgramFiles}/Microsoft DirectX SDK (November 2007)"
        "$ENV{ProgramFiles\(x86\)}/Microsoft DirectX SDK (November 2007)"
        "$ENV{ProgramFiles}/Microsoft DirectX SDK (August 2007)"
        "$ENV{ProgramFiles\(x86\)}/Microsoft DirectX SDK (August 2007)"
        "$ENV{ProgramFiles}/Microsoft DirectX SDK"
        "$ENV{ProgramFiles\(x86\)}/Microsoft DirectX SDK"
        DOC "DirectX SDK root directory"
        )
if (DirectX_ROOT_DIR)
    set (DirectX_INC_SEARCH_PATH "${DirectX_ROOT_DIR}/Include")
    set (DirectX_LIB_SEARCH_PATH "${DirectX_ROOT_DIR}/Lib/${DirectX_ARCHITECTURE}")
    set (DirectX_BIN_SEARCH_PATH "${DirectX_ROOT_DIR}/Utilities/bin/x86")
endif ()

find_library (DirectX_D3D9_LIBRARY d3d9
        PATHS ${DirectX_LIB_SEARCH_PATH}
        DOC "The directory where d3d9 resides")

add_executable(TrainDepo src/TDepo.cpp)

target_link_libraries(TrainDepo TrainDepo_library tinyxml irrlicht)
target_link_libraries(TrainDepo gdi32 user32 winmm d3dx9 ${DirectX_D3D9_LIBRARY})

set (source "${CMAKE_SOURCE_DIR}/data")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/data")
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
        DEPENDS ${destination}
        COMMENT "symbolic link resources folder from ${source} => ${destination}"
)