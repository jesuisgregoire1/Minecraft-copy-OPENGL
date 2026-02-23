#ifndef __COORD_SYSTEM__
#define __COORD_SYSTEM__
#include "glad/glad.h"
#include "../Camera/camera.hpp"
#include "../Shaders/shaders.hpp"
namespace CoordSystem{
    class CoordSystem{
        private:
            glm::mat4 model = glm::mat4(0.0f);
            glm::mat4 projection = glm::mat4(0.0f);
            glm::mat4 view = glm::mat4(0.0f);
            float points[18];
            float colors[18];
            unsigned int VBO[2], VAO;
            bool debug[1] = {true};
        public:
            CoordSystem();
            void InitializePoints();
            void InitializeColors();
            void Draw();
            
            // void SetupColors(ShaderNamespace::Shader); We don't need this shit
            void SetMVP(ShaderNamespace::Shader);
            void SetModel(glm::vec3 scale, glm::vec3 translation, 
                float angle, glm::vec3 axis);
            void SetView(CameraNamespace::Camera camera);
            void SetProjection();
    };
}
#endif