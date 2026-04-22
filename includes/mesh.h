
#ifndef MESH_H
#define MESH_H

#include <vector> 
#include <cstdint> 

#include <glm/vec3.hpp> 
#include <glm/vec2.hpp> 

using GLuint = unsigned int;

struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoord; 
};

class Mesh { 
public: 
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices; 
    uint32_t materialIndex;

    GLuint VBO = 0; GLuint VAO = 0; GLuint EBO = 0;

    void setup();

    void draw() const;
};

#endif 