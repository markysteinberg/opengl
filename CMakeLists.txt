cmake_minimum_required(VERSION 3.20)
project(GameEngine CXX C)

include(FetchContent) 

#GLFW 
find_package(glfw3 QUIET) 
if(NOT glfw3_FOUND)
	FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3.3.8)
	FetchContent_MakeAvailable(glfw)
	set(GLFW_TARGET glfw)
else() 
	set(GLFW_TARGET glfw) 
endif() 

#GLM
find_package(glm QUIET) 
if(NOT glm_FOUND) 
	FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git GIT_TAG 0.9.9.8) 
	FetchContent_MakeAvailable(glm)
	set(GLM_TARGET glm)
else()
	set(GLM_TARGET glm::glm)
endif() 

#Assimp
find_package(assimp QUIET)
if(NOT assimp_FOUND)
	FetchContent_Declare(assimp GIT_REPOSITORY https://github.com/assimp/assimp.git GIT_TAG v5.3.1)
	FetchContent_MakeAvailable(assimp)
	set(ASSIMP_TARGET assimp)
else() 
	set(ASSIMP_TARGET assimp)
endif()

find_package(OpenGL REQUIRED)

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
    target_link_libraries(enginetest PRIVATE glad ${GLFW_TARGET} ${ASSIMP_TARGET} ${GLM_TARGET} OpenGL::GL dl) 
elseif(WIN32)
	target_link_libraries(enginetest PRIVATE glad ${GLFW_TARGET} ${ASSIMP_TARGET} ${GLM_TARGET} opengl32) 
else() 
    message(FATAL_ERROR "THIS PLATFORM IS UNSUPPORTED")
endif()





