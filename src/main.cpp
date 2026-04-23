#include <unordered_map>
#include <string> 

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
#include "skybox.h"
#include "grid.h" 
#include "entity.h"

void initGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int run(int argc, char* argv[]) {
    LOG(INFO, "=== Startup: ", WINDOW_TITLE, " ", WINDOW_WIDTH, "x", WINDOW_HEIGHT, " FOV=", FOV, " ===");

    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG(ERROR, "Failed to init GLAD"); 
        return -1;
    }
    LOG(INFO, "GLAD initialized");

    initGL();

    std::vector<Entity> scene;

    std::unordered_map<std::string, Model> models; 
    models.emplace("dog", load_model("assets/objects+textures/dog/13463_Australian_Cattle_Dog_v3.obj"));
    //models["ground"] = load_model("assets/objects+textures/ground/ground.obj");

    for (auto &[name, m] : models) {
        if (!m.valid) {
            LOG(ERROR, name +  "Model has no meshes, aborting");
            return -1;
        }
        m.setup();
    }

    Shader default_shader("assets/shaders/default.vert", "assets/shaders/default.frag");
    default_shader.cacheUniforms();

    /* +== delta time =+ */
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    /* +== ========== =+ */
        
    default_shader.use();
    glUniform1i(default_shader.texLoc, 0);
    LOG(INFO, "Default shader bound, diffuseTex sampler set to unit 0");

    Camera camera;
    camera.attach(window.get());

    Skybox skybox; 
    
    Grid grid; 
    
    LOG(INFO, "=== Entering render loop ===");
    while (!glfwWindowShouldClose(window.get())) {         
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame; 
        
        double time = glfwGetTime();
        
        window.processInput(window.get(), &grid);
        camera.processInput(window.get(), deltaTime);

        default_shader.use();
        
        glm::mat4 view_mat = glm::mat4(1.0f);
        view_mat = camera.getViewMatrix();
        glm::mat4 proj_mat;
        proj_mat = glm::perspective(glm::radians(FOV), (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 800.0f);
        
        glm::mat4 dog_mat = glm::mat4(1.0f);
        dog_mat = glm::translate(dog_mat , glm::vec3(0.0f, 0.0f, 0.0f));
        dog_mat = glm::rotate(dog_mat, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 mvp_dog = proj_mat * view_mat * dog_mat;
        glUniformMatrix4fv(default_shader.mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp_dog));
        glUniform1f(default_shader.timeLoc, time);
        models["dog"].draw(default_shader.hasTexLoc, default_shader.diffuseLoc);

        skybox.draw(view_mat, proj_mat);

        if (grid.on) 
            grid.draw(view_mat, proj_mat);

        glfwSwapBuffers(window.get());
        glfwPollEvents();
    }
    LOG(INFO, "=== Exiting render loop, shutting down ===");

    return 0;
}

int main(int argc, char* argv[]) { 
    int result = run(argc, argv);
    
    glfwTerminate();
    LOG(INFO, "GLFW Terminated");
    
    return result;
}













