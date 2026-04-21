#ifndef ENTITY_H
#define ENTITY_H 

#include <glm/vec3.hpp> 

#include "model.h" 

class Entity {
public:
    Model* model = nullptr;

    glm::vec3 position = {0.0f, 0.0f, 0.0f};
    glm::vec3 rotation = {0.0f, 0.0f, 0.0f};
    glm::vec3 scale    = {1.0f, 1.0f, 1.0f}; 

    Entity() = default;
    
    Entity(Model* model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale); 
};

#endif