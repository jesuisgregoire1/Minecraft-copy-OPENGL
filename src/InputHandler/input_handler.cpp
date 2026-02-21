#include "input_handler.hpp"

void InputHandlerNamespace::InputHandler::ProcessInput(GLFWwindow* window, 
    CameraNamespace::Camera &camera, float dt){
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        camera.MoveForwardCamera(dt);
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        camera.MoveBackwardCamera(dt);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        camera.MoveRightCamera(dt);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        camera.MoveLeftCamera(dt);
    }
}