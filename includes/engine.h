#ifndef ENGINE_H 
#define ENGINE_H

#include <GLFW/glfw3.h>

#include "renderer.h"

class Engine {
public: 
    Engine();
    ~Engine();

    int init();
    void run();
    void shutdown();

private: 
    Window window;
    Renderer renderer;
};


#endif 