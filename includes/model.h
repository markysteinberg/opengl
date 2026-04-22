#ifndef MODEL_H
#define MODEL_H 

#include <vector>

#include <glm/vec3.hpp> 

#include "mesh.h"

using GLuint = unsigned int;

struct Material {
    glm::vec3 diffuse;
    GLuint diffuseTex = 0;
};

class Model {
public:
    std::vector<Mesh> meshes; 
    std::vector<Material> materials;

    bool valid = false;

    void setup();

    void draw(GLuint hasTexLoc, GLuint diffuseLoc);
};

Model load_model(const char* path);

#endif