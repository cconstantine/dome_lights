# Set the name and the supported language of the project
project(candy_pusher)
find_package(OpenGL REQUIRED)

# Set the minimum version of cmake required to build this project
cmake_minimum_required(VERSION 2.8)

add_subdirectory (external)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include(MSVCMultipleProcessCompile) # /MP

include_directories(
	external/AntTweakBar-1.16/include/
	external/glfw-3.1.2/include/GLFW/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	external/assimp-3.0.1270/include/
	external/bullet-2.81-rev2613/src/
	.
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

find_package(PkgConfig REQUIRED)

add_executable(dome_lights main.cpp shader.cpp)

target_link_libraries(dome_lights glfw GLEW_1130 ${OPENGL_LIBRARY} )
