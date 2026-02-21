#ifndef __SHADER_H__
#define __SHADER_H__
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
namespace ShaderNamespace{
    class Shader
    {
        public:
            unsigned int ID;
            Shader(const char* vertexPath, const char* fragmentPath);
            void use();
    };
}
#endif