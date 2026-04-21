#ifndef WINDOW_H
#define WINDOW_H 

#include <GLFW/glfw3.h> 

#include "grid.h" 

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

bool is_key_pressed_once(GLFWwindow* window, int key);

class Window {
public: 
    Window(int w, int h, const char* title);

    ~Window();

    GLFWwindow* get() const;

    void processInputs(GLFWwindow* window, Grid* grid);

private: 
    GLFWwindow* window = nullptr;
};

#endif 