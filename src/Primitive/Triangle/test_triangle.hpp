#ifndef __TRIANGLEE_H__
#define __TRIANGLEE_H__
#include "glad/glad.h"
namespace Test_TriangleNamespace{
    class Triangle{
        private:
            GLuint VBO[2], VAO, EBO;
            float vertices[12] = {
                                0.5f,  0.5f, 0.0f,  // top right
                                0.5f, -0.5f, 0.0f,  // bottom right
                                -0.5f, -0.5f, 0.0f,  // bottom left
                                -0.5f,  0.5f, 0.0f   // top left 
                                };
            uint32_t indices[6] = {  // note that we start from 0!
                                        0, 1, 3,   // first triangle
                                        1, 2, 3    // second triangle
                                    };
            
            float c[12];
        public:
            void CreateTriangle();
            float colors[12] = {
                                1.0f, 0.0f, 0.0f,  // top right
                                0.0f, 1.0f, 0.0f,  // bottom right
                                0.0f, 0.0f, 1.0f,  // bottom left 
                                1.0f, 0.0f, 0.0f   // top left 
                                };
            void Draw();
            void Test();
    };
}
#endif