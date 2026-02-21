#ifndef __UTILS_H__
#define __UTILS_H__
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Utils{
    struct DeltaTime{
        float deltaTime = 0.0f;
        float lastFrame = 0.0f; 
    };
    void init();
    void terminate();
    void callbackCloseTheWindow(GLFWwindow*, GLFWwindowclosefun);
    void closeWindowWithESCButton(GLFWwindow*);
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void loadingGlad();
    void getDeltatime(DeltaTime*);
}
#endif