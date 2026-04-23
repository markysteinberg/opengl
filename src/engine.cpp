#include <unordered_map>

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp> 
#include <glm/vec2.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "log.h"
#include "defines.h"
#include "window.h" 
#include "shader.h"
#include "camera.h" 
#include "mesh.h" 
#include "texture.h" 
#include "model.h"
#include "engine.h"

int Engine::init() {
    window = Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG(ERROR, "Failed to init GLAD"); 
        return -1;
    }  
    LOG(INFO, "GLAD initialized");

    renderer.init();

    return 0;
}

void Engine::run() {
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    
    while (!glfwWindowShouldClose(window.get())) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame; 
            
        double time = glfwGetTime();
    }

}