#include "WorldCoordSystem.hpp"

WorldCoordSystem::WorldCoordSystem::WorldCoordSystem(){
    coordSystem = new CoordSystem::CoordSystem();
}

void WorldCoordSystem::WorldCoordSystem::SetWorldCoordSystem(CameraNamespace::Camera camera, ShaderNamespace::Shader shader){
    coordSystem->SetModel(5.0f * glm::vec3(1.0f,1.0f,1.0f),
                    glm::vec3(point.x, point.y, point.z), 
                    glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    coordSystem->SetView(camera);
    coordSystem->SetProjection();
    coordSystem->SetMVP(shader);
}
