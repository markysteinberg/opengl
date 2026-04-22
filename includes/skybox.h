#ifndef SKYBOX_H 
#define SKYBOX_H

#include <vector> 
#include <string> 

#include <glad/glad.h>
#include <glm/glm.hpp> 

#include "shader.h" 

class Skybox { 
public: 
    Skybox();

    void draw(const glm::mat4 view, const glm::mat4 projection);

private: 
    GLuint VBO, VAO;
    GLuint cubeMapTex;

    Shader shader;

    std::vector<std::string> faces;

    void setupCube();
    GLuint loadCubeMap(const std::vector<std::string>& faces);
};

#endif 