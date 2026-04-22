#ifndef ENGINE_H 
#define ENGINE_H

#include <GLFW/glfw3.h>

class Engine {
public: 
    int init(Window* window); 
    void update();
    void render();

private: 
    GLFWwindow* window;
};


#endif 