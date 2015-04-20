cmake_minimum_required(VERSION 3.2)
project(LD48-32)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static")

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

# Find SFML
set(SFML_ROOT D:/Programming/C++/Contrib/SFML/install)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML REQUIRED COMPONENTS audio graphics window system)

if(NOT SFML_FOUND)
	message(FATAL_ERROR "SFML couldn't be located!")
endif()

# Find Thor
set(THOR_ROOT D:/Programming/C++/Contrib/Thor/install)
set(THOR_STATIC_LIBRARIES TRUE)
find_package(Thor REQUIRED)

if(NOT THOR_FOUND)
	message(FATAL_ERROR "Thor couldn't be located!")
endif()

# Find Box2D
set(BOX2D_ROOT D:/Programming/C++/Contrib/Box2D/install)
set(BOX2D_STATIC_LIBRARIES TRUE)
find_package(Box2D REQUIRED)

if(NOT BOX2D_FOUND)
	message(FATAL_ERROR "Box2D couldn't be located!")
endif()

include_directories(${SFML_INCLUDE_DIR})
include_directories(${THOR_INCLUDE_DIR})
include_directories(${BOX2D_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SOURCE_FILES
	src/main.cpp
	src/Application.cpp
	src/State.cpp
	src/MenuState.cpp
	src/PlayState.cpp
	src/FinalState.cpp
	src/PlayButton.cpp
	src/ExitButton.cpp
	src/Animation.cpp
	src/Synth.cpp
	src/World.cpp
	src/Tile.cpp
	src/Button.cpp
	src/Player.cpp
)

add_executable(LD48-32 ${SOURCE_FILES})

target_link_libraries(LD48-32 ${THOR_LIBRARY} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${BOX2D_LIBRARY})
