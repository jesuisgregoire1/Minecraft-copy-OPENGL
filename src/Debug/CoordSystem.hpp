#ifndef __COORD_SYSTEM__
#define __COORD_SYSTEM__
#include "glad/glad.h"
#include "../Camera/camera.hpp"
#include "../Shaders/shaders.hpp"
namespace CoordSystem{
    class CoordSystem{
        private:
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 projection = glm::mat4(1.0f);
            int length = 5;
            float *points_x = new float[4];
            float *points_y = new float[4];
            float *points_z = new float[4];
            unsigned int VBO, VAO;
            bool debug[1] = {true};
        public:
            CoordSystem();
            void InitializePoints_X();
            void InitializePoints_Y();
            void InitializePoints_Z();
            void Draw();
            void Rotate(CameraNamespace::Camera, ShaderNamespace::Shader);
            void SetupColors(ShaderNamespace::Shader);
    };
}
#endif