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

int Engine::init(Window* window) {
    LOG(INFO, "=== Startup: ", WINDOW_TITLE, " ", WINDOW_WIDTH, "x", WINDOW_HEIGHT, " FOV=", FOV, " ===");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG(ERROR, "Failed to init GLAD"); 
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /* +== MODELS ==+ */ 
    std::unordered_map<std::string, Model> models; 
    models["dog"]    = load_model("assets/objects+textures/13463_Australian_Cattle_Dog_v3.obj");
    models["ground"] = load_model("assets/objects+textures/floor.obj");
    models["girl"]   = load_model("assets/objects+textures/Character_Female_14.fbx");

    for (auto &[name, m] : models) {
        if (!m.valid) {
            LOG(ERROR, name +  "Model has no meshes, aborting");
            return -1;
        }
        m.setup();
    }
    /* +== ====== ==+ */

    /* +== delta time =+ */
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    /* +== ========== =+ */
  
    return 0;
}

void Engine::render() {

}