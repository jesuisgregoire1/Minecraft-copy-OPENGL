#ifndef __LL_CUBE_H__
#define __LL_CUBE_H__
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/camera.hpp"
#include "../../Shaders/shaders.hpp"
namespace ll_CubeNamespace{
    class LL_Cube{
        public:
        GLuint VAO, VBO[2], EBO;
        float posX=0.0f, posY=0.0f, posZ=0.0f;
        bool initialized = true;
        glm::mat4 model, view, projection;
        glm::vec3 points=glm::vec3(0.0f, 1.0f, 0.0f), rotation=glm::vec3(1.0f, 1.0f, 1.0f);
        float angle=0.0f;
        #pragma region cube_vertices_and_indices
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
        -0.5f, 0.5f, 0.5f};
        float colors[72] = {
        // back
        1.0f, 0.56f, 0.0f,
        1.0f, 0.56f, 0.0f,
        1.0f, 0.56f, 0.0f,
        1.0f, 0.56f, 0.0f,

        // front
        1.0f, 0.56f, 0.0f,
        1.0f, 0.56f, 0.0f,
        1.0f, 0.56f, 0.0f,
        1.0f, 0.56f, 0.0f,

        // left
        1.0f, 0.56f, 0.0f,
        1.0f, 0.56f, 0.0f,
        1.0f, 0.56f, 0.0f,
        1.0f, 0.56f, 0.0f,

        // right
        1.0f, 0.56f, 0.0f,
        1.0f, 0.56f, 0.0f,
        1.0f, 0.56f, 0.0f,
        1.0f, 0.56f, 0.0f,

        // bottom
        1.0f, 0.56f, 0.0f,
        1.0f, 0.56f, 0.0f,
        1.0f, 0.56f, 0.0f,
        1.0f, 0.56f, 0.0f,

        // top
        1.0f, 0.56f, 0.0f,
        1.0f, 0.56f, 0.0f,
        1.0f, 0.56f, 0.0f,
        1.0f, 0.56f, 0.0f};
        float aNormal[72] = {
             0.0f,  0.0f, -1.0f,
             0.0f,  0.0f, -1.0f, 
             0.0f,  0.0f, -1.0f, 
             0.0f,  0.0f, -1.0f, 

             0.0f,  0.0f, 1.0f,
             0.0f,  0.0f, 1.0f,
             0.0f,  0.0f, 1.0f,
             0.0f,  0.0f, 1.0f,         
            
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,            
            
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,            
             
             0.0f, -1.0f,  0.0f,
             0.0f, -1.0f,  0.0f,
             0.0f, -1.0f,  0.0f,
             0.0f, -1.0f,  0.0f,            

             0.0f,  1.0f,  0.0f,
             0.0f,  1.0f,  0.0f,
             0.0f,  1.0f,  0.0f,
             0.0f,  1.0f,  0.0f
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
        20,21,22, 22,23,20};
        #pragma endregion
        void CreateCube();
        void Draw();
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void CreatingTextures();
        void MVP(CameraNamespace::Camera camera, ShaderNamespace::Shader shader);
        void SetMVP(CameraNamespace::Camera);
        void SetRotation(float angle, float x_axis, float y_axis, float z_axis);
        void SetPosition(float x, float y, float z);
        void SetCoordSystem(CameraNamespace::Camera, ShaderNamespace::Shader shader);
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void ModelViewProjection(CameraNamespace::Camera, ShaderNamespace::Shader,glm::vec3 scale=glm::vec3(1.0f, 1.0f, 1.0f));
        // LL_Cube(float posY, float posX_first, float posX_second, float posX_third);
        LL_Cube(){
        }
    };
}

#endif