cmake_minimum_required(VERSION 3.20)
project(untitled3)

set(CMAKE_CXX_STANDARD 14)

set(GLFW_INCLUDE_DIR dependeces/glfw/include/)
set(GLFW_LIB_DIR dependeces/glfw/lib-vc2022)

set(GLEW_INCLUDE_DIR dependeces/glew/include)
set(GLEW_LIB_DIR dependeces/glew/lib/Release/x64)



add_subdirectory(dependeces/glm/)


include_directories(${GLFW_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} )
link_directories(${GLFW_LIB_DIR} ${GLEW_LIB_DIR})
find_package(OpenGL REQUIRED)

add_executable(untitled3 main.cpp
        dependeces/Common/Initialize.h
        dependeces/Common/Initialize.cpp
        dependeces/Common/controls.hpp
        dependeces/Common/controls.cpp
        dependeces/Common/stb_image.c
        dependeces/Common/stb_image.h
        dependeces/Common/objloader.hpp
        dependeces/Common/objloader.cpp
        dependeces/Common/RenderableObject.cpp
        dependeces/Common/RenderableObject.h
        dependeces/Common/shader.cpp
        dependeces/Common/shader.hpp
        src/Clouds.h src/ParticlesSystem.h src/Particle.h src/Particle.cpp resource/Squere.h)

target_link_libraries(${PROJECT_NAME} glew32s glew32 OpenGL32 glfw3 glm)
