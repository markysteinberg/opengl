#ifndef GRID_H
#define GRID_H 

#include "glad/glad.h"

#include <glm/glm.hpp>

#include "shader.h" 

class Grid {
public: 
    Grid();
    void draw(const glm::mat4& view, const glm::mat4& projection);

    bool on = true;

private: 
    GLuint VBO, VAO;
    Shader shader;
    
    void setup();
};

#endif 