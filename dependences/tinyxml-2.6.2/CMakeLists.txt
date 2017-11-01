cmake_minimum_required(VERSION 3.8)
project(tinyxml)

add_definitions(-DTIXML_USE_STL)

#include_directories(include)

set(HEADERS include/tinystr.h include/tinyxml.h)

add_library (tinyxml
        STATIC
        ${HEADERS}
        tinystr.cpp
        tinyxml.cpp
        tinyxmlerror.cpp
        tinyxmlparser.cpp
        )

#set_property(TARGET tinyxml PROPERTY POSITION_INDEPENDENT_CODE ON)

#set(HEADERS ${PROJECT_SOURCE_DIR}/include/tinystr.h ${PROJECT_SOURCE_DIR}/include/tinyxml.h)

#install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
#install(TARGETS tinyxml DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
