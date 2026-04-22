#include "entity.h" 

Entity::Entity(Model* model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : model(model), position(position), rotation(rotation), scale(scale) {};