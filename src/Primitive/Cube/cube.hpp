#ifndef __CUBE_H__
#define __CUBE_H__
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/camera.hpp"
#include "../../Shaders/shaders.hpp"
#include "../../Debug/CoordSystem.hpp"

namespace PointNamespace{
    struct Point{
        float x=0.0f, y=1.0f, z=0.0f;
    };
    struct Rotation{
        glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);
        float angle = 0.0f;
    };
};

namespace CubeNamespace{
    class Cube{
        private:
            CoordSystem::CoordSystem* coordSystem;
            PointNamespace::Point point;
            PointNamespace::Rotation rotation;
            unsigned int VBO[2], VAO, EBO;
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection = glm::mat4(1.0f);
            float widthTexture = 384.0f;
            float heightTexture = 416.0f;
            bool initialized = false;
            unsigned short posY=0, posX_first=0, posX_second=0, posX_third=0;
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
            void SetModel();
            void MVP(CameraNamespace::Camera camera, ShaderNamespace::Shader shader);
            void SetMVP(CameraNamespace::Camera);
            void SetRotation(float angle, float x_axis, float y_axis, float z_axis);
            void SetPosition(float x, float y, float z);
            void SetCoordSystem(CameraNamespace::Camera, ShaderNamespace::Shader shader);
            Cube(float posY, float posX_first, float posX_second, float posX_third);
            Cube(){}
    };
}
#endif