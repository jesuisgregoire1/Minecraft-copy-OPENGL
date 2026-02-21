#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Window/window.hpp"
#include "Utils/utils.hpp"
#include "Shaders/shaders.hpp"
#include "Primitive/Triangle/triangle.hpp"
#include "Primitive/Cube/cube.hpp"
#include "Primitive/Quad/quad.hpp"
#include "Texture/texture.hpp"
#include "InputHandler/input_handler.hpp"
#include "Camera/camera.hpp"
#include "Debug/CoordSystem.hpp"

//#include "stb_image.h"
using namespace WindowNamespace;
using namespace Utils;

void rotate_object(ShaderNamespace::Shader, CameraNamespace::Camera);
void transform_object(ShaderNamespace::Shader);
void static_draw(ShaderNamespace::Shader);
void change_color(float[], ShaderNamespace::Shader);

int main(){
    
    init();
    Window window = Window();
    window.initWindowSetup();
    window.createWindow();
    window.setCurrentContext();
    loadingGlad();
    //config
    glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //Callbacks
    glfwSetFramebufferSizeCallback(window.getWindow(), framebuffer_size_callback);
    
    //Utils
    Utils::DeltaTime dt = Utils::DeltaTime();
    //Input Handler
    InputHandlerNamespace::InputHandler inputHandler = InputHandlerNamespace::InputHandler();
    //Camera 
    CameraNamespace::Camera camera = CameraNamespace::Camera();
    glfwSetWindowUserPointer(window.getWindow(), &camera);
    glfwSetCursorPosCallback(window.getWindow(), camera.MouseCallback);  
    //Textures
    Texture::TextureGeneration texture = Texture::TextureGeneration();
    texture.GenerateTexture("/Users/jesuisgregoire/minecraft_copy/textures.png");
    //Shader
    ShaderNamespace::Shader shader = ShaderNamespace::Shader("/Users/jesuisgregoire/minecraft_copy/shaders/shader.vs", "/Users/jesuisgregoire/minecraft_copy/shaders/shader.fs");
    //DEBUG 
    CoordSystem::CoordSystem coordSystem = CoordSystem::CoordSystem();
    //Objects
    TriangleNamespace::Triangle triangle = TriangleNamespace::Triangle();
    CubeNamespace::Cube cube = CubeNamespace::Cube();
    QuadNamespace::Quad quad = QuadNamespace::Quad();
    triangle.CreateTriangle();
    cube.CreateCube();
    
    glEnable(GL_DEPTH_TEST); 
    while(!window.checkWindow()){
        Utils::getDeltatime(&dt);
        closeWindowWithESCButton(window.getWindow());
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();
        float red[] = {1.0f, 0.0f, 0.0f};
        float blue[] = {0.0f, 0.0f, 1.0f};
        // change_color(red, shader);
        // rotate_object(shader, camera);
        inputHandler.ProcessInput(window.getWindow(), camera, dt.deltaTime);
        texture.BindTexture();
        coordSystem.Rotate(camera,shader);
        coordSystem.SetupColors(shader);
        coordSystem.Draw();
        // cube.Rotate(camera, shader);
        // cube.Draw();
        // quad.Rotate(camera, shader);
        // quad.Draw();
        // coordSystem.Draw();
        // change_color(blue, shader);
        // texture.BindTexture();
        // static_draw(shader);
        // triangle.Draw();
        window.swapBuffers();       
        window.pollEvents();
    }
    terminate();
}

void change_color(float color[], ShaderNamespace::Shader shader){
    int colorLoc = glGetUniformLocation(shader.ID, "color_in");
    glUniform3f(colorLoc, color[0], color[1], color[2]);
}

void transform_object(ShaderNamespace::Shader shader){
    glm::mat4 transform = glm::mat4(1.0f);
    // transform = glm::translate(transform, glm::vec3(0.5f, 0.0f, 0.0f));
    // transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 0.0f));
    int transformaLoc = glGetUniformLocation(shader.ID, "transform");
    glUniformMatrix4fv(transformaLoc, 1, GL_FALSE, glm::value_ptr(transform));   
}

void rotate_object(ShaderNamespace::Shader shader, CameraNamespace::Camera camera){
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(50*(float)glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
    // model = glm::rotate(model, glm::radians(10*(float)glfwGetTime()), glm::vec3(1.0f, 1.0f, 0.0f));
    
    glm::mat4 view = camera.ModifyViewMatrix();
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    int viewLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projectionLoc = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void static_draw(ShaderNamespace::Shader shader){
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    int viewLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projectionLoc = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}