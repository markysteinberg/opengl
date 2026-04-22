#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include "window.h"
#include "log.h"
#include "camera.h" 
#include "grid.h" 

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    LOG(INFO, "Viewport resized: ", width, "x", height);
}

bool is_key_pressed_once(GLFWwindow* window, int key) {
    static bool last[GLFW_KEY_LAST + 1] = { false };
     
    bool now = glfwGetKey(window, key) == GLFW_PRESS;

    bool pressed = now && !last[key];

    last[key] = now;

    return pressed; 
}

Window::Window(int w, int h, const char* title) {
    if (!glfwInit()) {
        LOG(ERROR, "GLFW init failed");
        throw std::runtime_error("GLFW init failed");
    } 
    LOG(INFO, "GLFW initialized");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(w, h, title, nullptr, nullptr);
    if (!window) {
        LOG(ERROR, "Window creation failed");
        throw std::runtime_error("Window creation failed");
    }
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor()); // gets monitor details 
    glfwSetWindowPos(window, (mode->width - w) / 2, (mode->height - h) / 2);

    LOG(INFO, "Window created");

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Limits fps dont know how tho
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

Window::~Window() {
    if (window) glfwDestroyWindow(window);
}

GLFWwindow* Window::get() const { return window; }

void Window::processInputs(GLFWwindow* window, Grid* grid) {
    Camera* cam = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    
    if (is_key_pressed_once(window, GLFW_KEY_Q)) {
        glfwSetWindowShouldClose(window, true);
    }
    if (is_key_pressed_once(window, GLFW_KEY_C) && cam) {
        cam->mouseCaptured = !cam->mouseCaptured;
        glfwSetInputMode(window, GLFW_CURSOR, cam->mouseCaptured ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }
    if (is_key_pressed_once(window, GLFW_KEY_1) && grid) { 
        grid->on = !grid->on;
    }
}