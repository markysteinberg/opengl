
#include <GLFW/glfw3.h>

#include "camera.h"
#include "log.h" 

Camera::Camera() {
    LOG(INFO, "Camera created: pos=(", position.x, ", ", position.y, ", ", position.z, ")", " yaw=", yaw, " pitch=", pitch);
};

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, position + front, up);
} 

void Camera::processInput(GLFWwindow* window, float deltaTime) {
    isMoving = false;
    
    float vel = 0.0f;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        vel = speed * 2.5 * deltaTime;
    } else {
        vel = speed * deltaTime;
    }
    
    glm::vec3 front_lock_y = glm::normalize(glm::vec3(front.x, 0.0f, front.z));
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position += front_lock_y * vel;
        isMoving = true;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {  
        position -= front_lock_y * vel;
        isMoving = true;
    }
    glm::vec3 right = glm::normalize(glm::cross(front_lock_y, up));
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position -= right * vel;
        isMoving = true;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { 
        position += right * vel;
        isMoving = true;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) 
        position.y += vel;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) 
        position.y -= vel;
}   

void Camera::attach(GLFWwindow* window) {
    glfwSetWindowUserPointer(window, this);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    LOG(INFO, "Camera attached to window, cursor captured");
}

void Camera::handleMouse(double xpos, double ypos) {
    if (!mouseCaptured) return; // Guard for mouseCaptured 
    
    if (firstMouse) { 
        lastX = xpos; 
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset; 
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    glm::vec3 dir;
    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(dir);
}

void Camera::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    Camera* cam = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (cam) cam->handleMouse(xpos, ypos);
}

