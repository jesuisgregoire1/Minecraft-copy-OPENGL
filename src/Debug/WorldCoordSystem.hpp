#ifndef __WORLD_COORD_SYSTEM__
#define __WORLD_COORD_SYSTEM__
#include "glad/glad.h"
#include "CoordSystem.hpp"
#include "../Camera/camera.hpp"
#include "../Shaders/shaders.hpp"
namespace WorldCoordSystem{
    class WorldCoordSystem{
        private:
            glm::vec3 point = glm::vec3(0.0f, 0.0f, 0.0f);
            glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
            glm::vec3 scaleFactor = glm::vec3(5.0f, 5.0f, 5.0f);
            float angle = 0.0f;
            CoordSystem::CoordSystem* coordSystem;
        public:
            WorldCoordSystem();
            void SetWorldCoordSystem(CameraNamespace::Camera camera, ShaderNamespace::Shader shader);
    };
}
#endif