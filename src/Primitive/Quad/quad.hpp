#ifndef __QUAD_H__
#define __QUAD_H__
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/camera.hpp"
#include "../../Shaders/shaders.hpp"
namespace QuadNamespace{
    class Quad{
        private:
            unsigned int VBO[2], VAO, EBO, second_VBO, second_VAO;
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection = glm::mat4(1.0f);
            glm::vec3 crossVec[4];


            float vertices[12] = {
                                0.5f,  0.5f, 0.0f,  // top right
                                0.5f, -0.5f, 0.0f,  // bottom right
                                -0.5f, -0.5f, 0.0f,  // bottom left
                                -0.5f,  0.5f, 0.0f   // top left 
                                };
            float textures[8] = {
                                    16.0f / 384.0f, 16.0f / 416.0f,  // top right
                                    16.0f / 416.0f, 0.0f / 416.0f,   // bottom right
                                    0.0f / 416.0f, 0.0f / 416.0f,    // bottom left
                                    0.0f / 416.0f, 16.0f / 416.0f    // top left
                                };
            unsigned int indices[6] = {  // note that we start from 0!
                                        0, 1, 3,   // first triangle
                                        1, 2, 3    // second triangle
                                    };
        public:
            Quad();
            void Draw();
            void Rotate(CameraNamespace::Camera, ShaderNamespace::Shader);
            //Just for testing purposes!!!! DELETE IT AFTED NOOB
            void GenerateCrossProduct(CameraNamespace::Camera camera, ShaderNamespace::Shader shader);
            void SecondDraw();
            void Test();
           void CrossTesting(uint8_t ii, uint8_t jj, uint8_t kk, glm::vec3 crossVec[]);

    };
}
#endif