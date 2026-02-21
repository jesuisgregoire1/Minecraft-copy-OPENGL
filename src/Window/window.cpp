#include "window.hpp"

GLFWwindow* WindowNamespace::Window::getWindow() const{
    return this->window;
}

void WindowNamespace::Window::initWindowSetup(){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MINOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MAJOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void WindowNamespace::Window::swapBuffers(){
    glfwSwapBuffers(this->window);
}

void WindowNamespace::Window::pollEvents(){
    glfwPollEvents();
}

void WindowNamespace::Window::setCurrentContext(){
    glfwMakeContextCurrent(this->window);
}

void WindowNamespace::Window::createWindow(){
    this->window = glfwCreateWindow(windowWidth, windowHeight, WINDOW_NAME, NULL, NULL);
}

bool WindowNamespace::Window::checkWindow(){
    return glfwWindowShouldClose(this->window);
}

void WindowNamespace::Window::setViewPort(){
    glViewport(x_init, y_init, windowWidth, windowHeight);
}

WindowNamespace::Window::~Window(){
    glfwDestroyWindow(this->window);
}

