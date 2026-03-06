#include "utils.hpp"

void Utils::init(){
    glfwInit();
}

void Utils::terminate(){
    glfwTerminate();
}


void Utils::closeWindowWithESCButton(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)   
        glfwSetWindowShouldClose(window, true);
}

void Utils::loadingGlad(){
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std :: cout << "Failed to initialize GLAD" << std :: endl;
    }
}

void Utils::framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void Utils::getDeltatime(DeltaTime* dt){
    float currentFrame = glfwGetTime();
    dt->deltaTime = currentFrame - dt->lastFrame;
    dt->lastFrame = currentFrame;
}