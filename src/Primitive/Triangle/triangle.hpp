#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__
#include "glad/glad.h"
namespace TriangleNamespace{
    class Triangle{
        private:
            unsigned int VBO[2], VAO, EBO;
            float vertices[12] = {
                                0.5f,  0.5f, 0.0f,  // top right
                                0.5f, -0.5f, 0.0f,  // bottom right
                                -0.5f, -0.5f, 0.0f,  // bottom left
                                -0.5f,  0.5f, 0.0f   // top left 
                                };
            unsigned int indices[6] = {  // note that we start from 0!
                                        0, 1, 3,   // first triangle
                                        1, 2, 3    // second triangle
                                    };
            float colors[12] = {
                                        1.0f, 0.0f, 0.0f,  // top right
                                        0.0f, 1.0f, 0.0f,  // bottom right
                                        0.0f, 0.0f, 1.0f,  // bottom left 
                                        0.0f, 0.0f, 0.0f   // top left 
                                    };
           float textures[8] = {
                                    16.0f / 384.0f, 16.0f / 416.0f,  // top right
                                    16.0f / 416.0f, 0.0f / 416.0f,   // bottom right
                                    0.0f / 416.0f, 0.0f / 416.0f,    // bottom left
                                    0.0f / 416.0f, 16.0f / 416.0f    // top left
                                };
        public:
            void CreateTriangle();
            void Draw();
            void CreatingTextures();
    };
}
#endif