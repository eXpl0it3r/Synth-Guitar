cmake_minimum_required(VERSION 3.2)
project(Synth-Guitar)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static")

# set default build type explicitly to Release
if (NOT CMAKE_BUILD_TYPE)
	set (CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build type." FORCE)
endif (NOT CMAKE_BUILD_TYPE)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

# Find SFML
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML REQUIRED COMPONENTS audio graphics window system)

if(NOT SFML_FOUND)
	message(FATAL_ERROR "SFML couldn't be located!")
endif()

# Find Thor
set(THOR_STATIC_LIBRARIES TRUE)
find_package(Thor REQUIRED)

if(NOT THOR_FOUND)
	message(FATAL_ERROR "Thor couldn't be located!")
endif()

include_directories(${SFML_INCLUDE_DIR})
include_directories(${THOR_INCLUDE_DIR})
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

add_executable(Synth-Guitar ${SOURCE_FILES})

target_link_libraries(Synth-Guitar ${THOR_LIBRARY} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

# Install executable
install(TARGETS Synth-Guitar
	RUNTIME DESTINATION .
)

# Install game data
install(DIRECTORY bin/res
	DESTINATION .
)
