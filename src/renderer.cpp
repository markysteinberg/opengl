#include "glad/glad.h" 

#include "renderer.h"

void Renderer::init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Renderer::render() {
    glClearColor(0.53f, 0.82f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}