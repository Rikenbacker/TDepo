cmake_minimum_required(VERSION 3.8)
project(tinyxml)

add_definitions(-DWIN32 -D_LIB)

add_library (tinyxml
        tinystr.cpp
        tinyxml.cpp
        tinyxmlerror.cpp
        tinyxmlparser.cpp
        )

include_directories(${PROJECT_SOURCE_DIR}/include)

set(HEADERS ${PROJECT_SOURCE_DIR}/include/tinystr.h
        ${PROJECT_SOURCE_DIR}/include/tinyxml.h)

install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
install(TARGETS tinyxml DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
