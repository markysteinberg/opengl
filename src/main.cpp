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
#include "skybox.h"
#include "grid.h" 
#include "entity.h"

int run() {
    LOG(INFO, "=== Startup: ", WINDOW_TITLE, " ", WINDOW_WIDTH, "x", WINDOW_HEIGHT, " FOV=", FOV, " ===");

    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG(ERROR, "Failed to init GLAD"); 
        return -1;
    }
    LOG(INFO, "GLAD initialized");

    glEnable(GL_DEPTH_TEST);
    LOG(INFO, "Depth test enabled"); 

    std::vector<Entity> scene;

    /* +== SETUP MODELS ==+ */ 
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
    /*
    Entity dog(&models["dog"], 
        glm::vec3(0.0f, 0.0f, 0.0f), 
        glm::vec3(glm::radians(-90.0f), 0.0f, 0.0f),
        glm::vec3(1.0f)
    );
    */
    Shader default_shader("assets/shaders/default.vert", "assets/shaders/default.frag");

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    GLuint mvpLoc = glGetUniformLocation(default_shader.getID(), "MVP");
    GLuint timeLoc = glGetUniformLocation(default_shader.getID(), "time");
    GLuint hasTexLoc = glGetUniformLocation(default_shader.getID(), "hasTexture");
    GLuint diffuseLoc = glGetUniformLocation(default_shader.getID(), "diffuse");
    GLuint texLoc = glGetUniformLocation(default_shader.getID(), "diffuseTex");
    

    /* +== delta time =+ */
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    /* +== ========== =+ */
        
    default_shader.use();
    glUniform1i(texLoc, 0);
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
        
        window.processInputs(window.get(), &grid);
        camera.processInput(window.get(), deltaTime);

        // glm::vec3 background_color = {sin(time) * 0.5f + 0.5f, sin(time + 1) * 0.5f + 0.5f, sin(time + 2) * 0.5 + 0.5f};
        // background_color = glm::normalize(background_color);
        glClearColor(0.53f, 0.82f, 0.92f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        default_shader.use();
        
        /* +== View and Projection Matrix ==+ */
        glm::mat4 view_mat = glm::mat4(1.0f);
        view_mat = camera.getViewMatrix();
        glm::mat4 proj_mat;
        proj_mat = glm::perspective(glm::radians(FOV), (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 800.0f);
        /* +== ========================== ==+ */

        /*
        glm::mat4 ground_mat = glm::mat4(1.0f);
        glm::mat4 mvp_ground = proj_mat * view_mat * ground_mat;
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp_ground));
        glUniform1f(timeLoc, time);
        models["ground"].draw(hasTexLoc, diffuseLoc);          
        */
 
        glm::mat4 dog_mat = glm::mat4(1.0f);
        dog_mat = glm::translate(dog_mat , glm::vec3(0.0f, 0.0f, 0.0f));
        dog_mat = glm::rotate(dog_mat, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 mvp_dog = proj_mat * view_mat * dog_mat;
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp_dog));
        glUniform1f(timeLoc, time);
        models["dog"].draw(hasTexLoc, diffuseLoc);

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
    int result = run();
    glfwTerminate();
    LOG(INFO, "GLFW Terminated");
    return result;
}













