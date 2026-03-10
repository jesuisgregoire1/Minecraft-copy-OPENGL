#ifndef __CUBE_H__
#define __CUBE_H__
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/camera.hpp"
#include "../../Shaders/shaders.hpp"
#include "../../Debug/CoordSystem.hpp"

namespace Transformation{
    struct Point{
        float x=0.0f, y=1.0f, z=0.0f;
    };
    struct Rotation{
        glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);
        float angle = 0.0f;
    };
};
namespace BoundingBox{
    struct BoundingBox{
        bool isColliding = false;
        glm::vec3 max       = glm::vec3(0.5f, 0.5f, 0.5f);
        glm::vec3 min       = glm::vec3(-0.5f,-0.5f,-0.5f);
        glm::vec3 vertices[8], colors[8];
        glm::mat4 model, view, projection;
        unsigned int VAO[1], VBO[2], EBO[1];
        unsigned int indices[24] = {
            0,1, 1,2, 2,3, 3,0,
            4,5, 5,6, 6,7, 7,4,
            0,4, 1,5, 2,6, 3,7
        };
        void Draw();
        void CreateBoundingBoxPoints();
        void CreateBoundingBoxColor();
        void SetMVP(CameraNamespace::Camera camera, 
                    glm::vec3 position,
                    float angle, glm::vec3 rotation, 
                    glm::vec3 scale = glm::vec3(1.01f, 1.01f, 1.01f));
        void MVP(CameraNamespace::Camera camera, ShaderNamespace::Shader shader);
        void ChangeColor();
        BoundingBox();
    };
}

namespace ObjectBoundingBox{
    struct ObjectBoundingBox{
        glm::vec3 center;
        uint8_t X_AxisLength=1, Y_AxisLength=1, Z_AxisLength=1;
        float x_axisLength=1/2, y_axisLength=1/2, z_axisLength=1/2;
        int* L_A             = nullptr;
        int* L_B             = nullptr;
        glm::vec3* cross_A_B = nullptr;
        uint8_t lengthA = 3, lengthB = 3, lengthCrossAB = 9;
        ObjectBoundingBox();
        ~ObjectBoundingBox();
        void SetPointers();
    };
}

namespace CubeNamespace{
    class Cube{
        private:
            CoordSystem::CoordSystem coordSystem;
            Transformation::Point point;
            Transformation::Rotation rotation;;
            ObjectBoundingBox::ObjectBoundingBox obb;
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
            BoundingBox::BoundingBox boundingBox; 
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