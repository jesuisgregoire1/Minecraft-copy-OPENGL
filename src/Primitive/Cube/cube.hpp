#ifndef __CUBE_H__
#define __CUBE_H__
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/camera.hpp"
#include "../../Shaders/shaders.hpp"
namespace CubeNamespace{
    class Cube{
        private:
            unsigned int VBO[2], VAO, EBO;
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection = glm::mat4(1.0f);
            float widthTexture = 384.0f;
            float heightTexture = 416.0f;
            float textures[48];
            float vertices[72] = {
    // back
    0.5f, 0.5f,-0.5f,
    0.5f,-0.5f,-0.5f,
    -0.5f,-0.5f,-0.5f,
    -0.5f, 0.5f,-0.5f,

    // front
    0.5f, 0.5f, 0.5f,
    0.5f,-0.5f, 0.5f,
    -0.5f,-0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,

    // left
    -0.5f, 0.5f,-0.5f,
    -0.5f,-0.5f,-0.5f,
    -0.5f,-0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,

    // right
    0.5f, 0.5f,-0.5f,
    0.5f,-0.5f,-0.5f,
    0.5f,-0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,

    // bottom
    0.5f,-0.5f, 0.5f,
    0.5f,-0.5f,-0.5f,
    -0.5f,-0.5f,-0.5f,
    -0.5f,-0.5f, 0.5f,

    // top
    0.5f, 0.5f, 0.5f,
    0.5f, 0.5f,-0.5f,
    -0.5f, 0.5f,-0.5f,
    -0.5f, 0.5f, 0.5f
};
     
            unsigned int indices[36] = {
    // back
    0,1,2,  2,3,0,
    // front
    4,5,6,  6,7,4,
    // left
    8,9,10, 10,11,8,
    // right
    12,13,14, 14,15,12,
    // bottom
    16,17,18, 18,19,16,
    // top
    20,21,22, 22,23,20
};

        public: 
            void CreateCube();
            void CreatingTextures();
            void Draw();
            void Rotate(CameraNamespace::Camera, ShaderNamespace::Shader);
    };
}
#endif