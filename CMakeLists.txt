cmake_minimum_required(VERSION 3.10)

project(GameEngine CXX C)

set(CPP_SOURCES 
    src/main.cpp 
    src/camera.cpp 
    src/mesh.cpp 
	src/model.cpp 
	src/shader.cpp 
	src/texture.cpp 
	src/window.cpp 
	src/skybox.cpp 
	src/grid.cpp
    src/entity.cpp
)

add_library(glad STATIC src/glad.c)
target_include_directories(glad PUBLIC includes)

add_executable(enginetest ${CPP_SOURCES})

target_compile_options(enginetest PRIVATE -Werror -Wall -Wpedantic -O0 -g)

target_compile_features(enginetest PRIVATE cxx_std_20)

target_include_directories(enginetest PRIVATE includes)

if(UNIX)
    target_link_libraries(enginetest PRIVATE glad glfw GL assimp dl) 
elseif(WIN32)
	target_link_libraries(enginetest PRIVATE glad glfw opengl32 assimp) 
else() 
    message(FATAL_ERROR "No compatibility with system")
endif()





