#ifndef CAMERA_H
#define CAMERA_H

#include <glm/vec3.hpp> 
#include <glm/vec2.hpp> 
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public: 
    bool mouseCaptured = true; // Delete later, use for now 

    Camera();

    glm::mat4 getViewMatrix();

    void processInput(GLFWwindow* window, float deltaTime);

    void attach(GLFWwindow* window);

private: 
    bool isMoving = false;

    glm::vec3 position = {20.0f, 50.0f, 50.0f};
    glm::vec3 front    = {0.0f, 0.0f, -1.0f};
    glm::vec3 up       = {0.0f, 1.0f, 0.0f};

    float yaw          = -90.0f;
    float pitch        =  0.0f; 
    float sensitivity  =  0.075f;
    float speed        =  300.0f;

    float lastX = 640, lastY = 360;
    bool firstMouse = true;

    void handleMouse(double xpos, double ypos);

    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
};

#endif 