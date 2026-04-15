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
#include "Debug/WorldCoordSystem.hpp"
#include "Primitive/Triangle/test_triangle.hpp" //DELETE IT AFTER
#include "Primitive/Cube/ll_cube.hpp"
#define LIGHTSCENE 1
#define TESTING 0
#define DEBUG
//#include "stb_image.h"
using namespace WindowNamespace;
using namespace Utils;

// void rotate_object(ShaderNamespace::Shader, CameraNamespace::Camera);
// void transform_object(ShaderNamespace::Shader);
// void static_draw(ShaderNamespace::Shader);
// void change_color(float[], ShaderNamespace::Shader);
bool check_intersection(CubeNamespace::Cube&, CubeNamespace::Cube&);
bool check_intersection_obb(CubeNamespace::Cube&, CubeNamespace::Cube&);
float counter = 0.0f;
float speed = 1.0f;
float speed_rot1 = 50.0f;
float speed_rot2 = 60.0f;
float rot;

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


#if LIGHTSCENE == 1
    Utils::DeltaTime dt = Utils::DeltaTime();
    InputHandlerNamespace::InputHandler inputHandler = InputHandlerNamespace::InputHandler();
    CameraNamespace::Camera camera = CameraNamespace::Camera();
    glfwSetWindowUserPointer(window.getWindow(), &camera);
    glfwSetCursorPosCallback(window.getWindow(), camera.MouseCallback);  
    Texture::TextureGeneration t_wood = Texture::TextureGeneration();
    t_wood.GenerateTexture("../resources/container2.png");
#ifdef DEBUG
    std :: cout << "Texture height : " << t_wood.GetTextureHeigth() << std :: endl;
    std :: cout << "Texture width  : " << t_wood.GetTextureWidth() << std :: endl;
#endif
    Texture::TextureGeneration t_wood_specular = Texture::TextureGeneration();
    t_wood_specular.GenerateTexture("../resources/container2_specular.png");
#ifdef DEBUG
    std :: cout << "Texture height : " << t_wood_specular.GetTextureHeigth() << std :: endl;
    std :: cout << "Texture width  : " << t_wood_specular.GetTextureWidth() << std :: endl;
#endif

#if TESTING == 0   
    ll_CubeNamespace::LL_Cube cube = ll_CubeNamespace::LL_Cube();
    cube.SetPosition(0.0f, 2.5f, -2.0f);
    cube.SetRotation(0.0f, 0.0f, 1.0f, 0.0f);
    cube.CreateCube();
    ShaderNamespace::Shader shader = ShaderNamespace::Shader("/Users/jesuisgregoire/minecraft_copy/shaders/l_test_shader.vs", "/Users/jesuisgregoire/minecraft_copy/shaders/l_test_shader.fs");
    ll_CubeNamespace::LL_Cube lightSource = ll_CubeNamespace::LL_Cube();
    lightSource.CreateCube();
    ShaderNamespace::Shader lightSourceShader = ShaderNamespace::Shader("/Users/jesuisgregoire/minecraft_copy/shaders/l_test_shader.vs", "/Users/jesuisgregoire/minecraft_copy/shaders/light_source.fs");
    
    shader.use();
    int lightPos = glGetUniformLocation(shader.ID, "light.position");
    glUniform3fv(lightPos, 1, glm::value_ptr(lightSource.points));


#elif TESTING == 1
    QuadNamespace::Quad quad = QuadNamespace::Quad();
    ShaderNamespace::Shader shader = ShaderNamespace::Shader("/Users/jesuisgregoire/minecraft_copy/shaders/l_test_shader.vs", "/Users/jesuisgregoire/minecraft_copy/shaders/l_test_shader.fs");
    quad.Test();
#endif
    float time = glfwGetTime();
    glEnable(GL_DEPTH_TEST); 
    while(!window.checkWindow()){
        Utils::getDeltatime(&dt);
        closeWindowWithESCButton(window.getWindow());
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        inputHandler.ProcessInput(window.getWindow(), camera, dt.deltaTime);
#if TESTING == 1
        quad.Rotate(camera, shader);
        quad.Draw();
        quad.GenerateCrossProduct(camera, shader);
        quad.SecondDraw();
#elif TESTING == 0
        glActiveTexture(GL_TEXTURE0);
        t_wood.BindTexture();
        glActiveTexture(GL_TEXTURE1);
        t_wood_specular.BindTexture();  
        cube.ModelViewProjection(camera, shader);
        cube.Draw();
        lightSourceShader.use();
        shader.use();
        int lightPos = glGetUniformLocation(shader.ID, "light.position");
        glUniform3fv(lightPos, 1, glm::value_ptr(lightSource.points));
        int viewPos = glGetUniformLocation(shader.ID, "viewPos");
        glUniform3fv(viewPos, 1, glm::value_ptr(camera.GetcameraPos()));
        lightSource.ModelViewProjection(camera, lightSourceShader, glm::vec3(0.5f, 0.5f, 0.5f));
        lightSource.Draw();
#endif
        window.swapBuffers();       
        window.pollEvents();
    }
    terminate();
#endif


#pragma region commmented for lighting scene
#if LIGHTSCENE == 0
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
    ShaderNamespace::Shader d_coordSystemShader = ShaderNamespace::Shader("/Users/jesuisgregoire/minecraft_copy/shaders/cs_shader.vs", "/Users/jesuisgregoire/minecraft_copy/shaders/cs_shader.fs");
    //DEBUG 
    CoordSystem::CoordSystem coordSystem = CoordSystem::CoordSystem();
    WorldCoordSystem::WorldCoordSystem worldCoordinateSystem = WorldCoordSystem::WorldCoordSystem();    
    //Objects
    TriangleNamespace::Triangle triangle = TriangleNamespace::Triangle();
    CubeNamespace::Cube* cubes = new CubeNamespace::Cube[2];
    
    cubes[0] = CubeNamespace::Cube(368.0f, 80.0f, 96.0f, 112.0f);
    cubes[1] = CubeNamespace::Cube(368.0f, 80.0f, 48.0f, 64.0f);
    
    
    QuadNamespace::Quad quad = QuadNamespace::Quad();
    triangle.CreateTriangle();
    cubes[0].CreateCube();
    cubes[1].CreateCube();
    bool test1=false;
    glEnable(GL_DEPTH_TEST); 
    while(!window.checkWindow()){
        Utils::getDeltatime(&dt);
        closeWindowWithESCButton(window.getWindow());
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        float red[] = {1.0f, 0.0f, 0.0f};
        float blue[] = {0.0f, 0.0f, 1.0f};
        // change_color(red, shader);
        // rotate_object(shader, camera);
        inputHandler.ProcessInput(window.getWindow(), camera, dt.deltaTime);
        shader.use();
        texture.BindTexture();     
        // coordSystem.SetupColors(d_coordSystemShader);
        ////////////////////////////////////////////////////////////////////////////////////////////////
        cubes[1].SetPosition(counter, 1.0f, 0.0f);
        counter -= dt.deltaTime * speed;
        cubes[1].SetRotation(speed_rot1, 0.0f, 1.0f, 0.0f);
        cubes[1].SetMVP(camera);
        cubes[1].MVP(camera, shader);
        cubes[1].Draw();
        cubes[1].SetCoordSystem(camera,d_coordSystemShader);
        coordSystem.Draw();
        cubes[1].boundingBox.MVP(camera, d_coordSystemShader);
        cubes[1].boundingBox.ChangeColor();
        cubes[1].boundingBox.Draw();
        ////////////////////////////////////////////////////////////////////////////////////////////////
        shader.use();
        cubes[0].SetPosition(-5.0f, 1.0f, 0.0f);
        cubes[0].SetRotation(speed_rot2, 0.0f, 0.0f, 1.0f);
        cubes[0].SetMVP(camera);
        cubes[0].MVP(camera, shader);
        cubes[0].Draw();
        cubes[0].SetCoordSystem(camera,d_coordSystemShader);
        cubes[0].boundingBox.MVP(camera, d_coordSystemShader);
        cubes[0].boundingBox.ChangeColor();
        cubes[0].boundingBox.Draw();
        coordSystem.Draw();
        ////////////////////////////////////////////////////////////////////////////////////////////////
        // WORLD COORDINATE SYSTEM
        test1 = check_intersection_obb(cubes[0], cubes[1]);
        if(test1){speed = 0.0f;}
        if(speed != 0.0f)
            rot = float(glfwGetTime());
        else
            rot = 1.0f;
        worldCoordinateSystem.SetWorldCoordSystem(camera, d_coordSystemShader);
        coordSystem.Draw();
        ////////////////////////////////////////////////////////////////////////////////////////////////
        shader.use();
        quad.Rotate(camera, shader);
        quad.Draw();
        
        
        // std :: cout << "cubes[1].boundingBox=" << cubes[1].boundingBox.isColliding << 
        // " cubes[2].boundingBox=" << cubes[2].boundingBox.isColliding << std :: endl;
        // change_color(blue, shader);
        // texture.BindTexture();
        // static_draw(shader);
        // triangle.Draw();
        window.swapBuffers();       
        window.pollEvents();
    }
    terminate();
    // freeMemory(cubes);
    delete[] cubes;
#endif
#pragma endregion
}

bool check_intersection(CubeNamespace::Cube &cube1, CubeNamespace::Cube &cube2){
    // std :: cout << "x1=" << cube1.boundingBox.max.x << "||" << "y1=" << cube1.boundingBox.max.y << "||" << "z1=" << cube1.boundingBox.max.z << std :: endl;
    // std :: cout << "x2=" << cube2.boundingBox.max.x << "||" << "y2=" << cube2.boundingBox.max.y << "||" << "z2=" << cube2.boundingBox.max.z << std :: endl;
    if((cube1.boundingBox.max.x >= cube2.boundingBox.min.x && cube1.boundingBox.min.x <= cube2.boundingBox.max.x) &&
    (cube1.boundingBox.max.y >= cube2.boundingBox.min.y && cube1.boundingBox.min.y <= cube2.boundingBox.max.y)   &&
    (cube1.boundingBox.max.z >= cube2.boundingBox.min.z && cube1.boundingBox.min.z <= cube2.boundingBox.max.z))
        {
            std :: cout << "YES" << std :: endl;
            cube1.boundingBox.isColliding = true;
            cube2.boundingBox.isColliding = true;
            speed = 0.0f;
            return true;
        }
        cube1.boundingBox.isColliding = false;
        cube2.boundingBox.isColliding = false;
        // std :: cout << "NO" << std :: endl;
        return false;
        
}

bool check_intersection_obb(CubeNamespace::Cube &cube1, CubeNamespace::Cube &cube2){
    glm::vec3 L[15];
    uint8_t counter = 0;
    for(uint8_t i=0; i<3; ++i){
        L[counter++] = cube1.obb.axis[i];
    }
    for(uint8_t i=0; i<3; ++i){
        L[counter++] = cube2.obb.axis[i];
    }
    for(uint8_t i=0; i<3; ++i){
        for(uint8_t j=0; j<3; j++){
            L[counter++] = glm::cross(cube1.obb.axis[i], cube2.obb.axis[j]);
        }
    }
    float R=0.0f;
    glm::vec3 R0=glm::vec3(0.0f); 
    for(uint8_t i=0; i<counter; ++i){
        // if(glm::length(L[i]) < 1e-6f)
        //     continue;
        R = abs(glm::dot(L[i], cube2.obb.center - cube1.obb.center));
        float sum = 0.0f;
        for(uint8_t j=0; j<3; ++j){
            sum += 0.5f*glm::sign(glm::dot(L[i], cube1.obb.axis[j])) * glm::dot(L[i] , cube1.obb.axis[j]);
        }
        for(uint8_t j=0; j<3; ++j){
            sum += 0.5f*glm::sign(glm::dot(L[i], cube2.obb.axis[j])) * glm::dot(L[i] , cube2.obb.axis[j]);
        }
        if(R>sum){
            cube1.boundingBox.isColliding = false;
            cube2.boundingBox.isColliding = false;
            return false;
        }
    }
    cube1.boundingBox.isColliding = true;
    cube2.boundingBox.isColliding = true;
    // speed = 0.0f;
    return true;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//DONT NEED THIS 
// void change_color(float color[], ShaderNamespace::Shader shader){
//     int colorLoc = glGetUniformLocation(shader.ID, "color_in");
//     glUniform3f(colorLoc, color[0], color[1], color[2]);
// }

// void transform_object(ShaderNamespace::Shader shader){
//     glm::mat4 transform = glm::mat4(1.0f);
//     // transform = glm::translate(transform, glm::vec3(0.5f, 0.0f, 0.0f));
//     // transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 0.0f));
//     int transformaLoc = glGetUniformLocation(shader.ID, "transform");
//     glUniformMatrix4fv(transformaLoc, 1, GL_FALSE, glm::value_ptr(transform));   
// }

// void rotate_object(ShaderNamespace::Shader shader, CameraNamespace::Camera camera){
//     glm::mat4 model = glm::mat4(1.0f);
//     model = glm::rotate(model, glm::radians(50*(float)glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
//     // model = glm::rotate(model, glm::radians(10*(float)glfwGetTime()), glm::vec3(1.0f, 1.0f, 0.0f));
    
//     glm::mat4 view = camera.ModifyViewMatrix();
//     glm::mat4 projection;
//     projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

//     int modelLoc = glGetUniformLocation(shader.ID, "model");
//     glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//     int viewLoc = glGetUniformLocation(shader.ID, "view");
//     glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//     int projectionLoc = glGetUniformLocation(shader.ID, "projection");
//     glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
// }

// void static_draw(ShaderNamespace::Shader shader){
//     glm::mat4 model = glm::mat4(1.0f);
//     model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//     glm::mat4 view = glm::mat4(1.0f);
//     view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//     glm::mat4 projection;
//     projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

//     int modelLoc = glGetUniformLocation(shader.ID, "model");
//     glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//     int viewLoc = glGetUniformLocation(shader.ID, "view");
//     glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//     int projectionLoc = glGetUniformLocation(shader.ID, "projection");
//     glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////